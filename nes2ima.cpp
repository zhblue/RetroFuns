#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*
.NES文件为模拟用来储存NES卡带的映像。下面是一个.NES文件的结构。
偏移  字节数  内容
0－3  4       字符串“NES^Z”用来识别.NES文件
4     1       16kB    ROM的数目
5     1       8kB VROM的数目
6     1  D0：1＝垂直镜像，0＝水平镜像
　  　  D1：1＝有电池记忆，SRAM地址$6000-$7FFF
　  　  D2：1＝在$7000-$71FF有一个512字节的trainer
　  　  D3：1＝4屏幕VRAM布局
　  　  D4－D7：ROM Mapper的低4位
7  1  D0－D3：保留，必须是0（准备作为副Mapper号^_^）
　  　  D4－D7：ROM Mapper的高4位
8－F  8  保留，必须是0
16-  16KxM  ROM段升序排列，如果存在trainer，它的512字节摆在ROM段之前
-EOF  8KxN  VROM段, 升序排列

SB2000 YX027游戏盘游戏存放地址
MENU PRG: 0C800-06CF
B4800-
GAME EXT: 0F600-0F9F1 载入内存$6900
CHRROM 1: 19000-38FFF
CHRROM 2: 39000-58FFF
MENU CHR: 59000-59FFF
MENU CHR: 5A000-5AFFF
PRGROM 1: B5000-D4FFF
PRGROM 2: D5000-F4FFF

游戏选择界面主程序存放地址
0F600-105FF 既有代码也有图像数据，代码范围
0F600-0F9F1
这段程序载入主机$6900开始运行

4040-4047端口用作分割扩展内存用的，4KB一个BANK。详见SH6578手册。

FFEA: 4C B3 EC  JMP ECB3
FFED: 4C EE EC  JMP ECEE
FFF0: 4C 8E FD  JMP FD8E
FFF3: 4C 61 EC  JMP EC61
FFF6: 4C 8A EC  JMP EC8A
FFF9:       00  BRK
FFFA:    84 C0  STY $C0
FFFC:       00  BRK
FFFD:    C0 2B  CPY #$2B
FFFF:    C1 FF  CMP ($FF,x)

*/


// mapper4 based

#define BASE_IMA "mapper4.ima"

#define CHR1_START 0x19000
#define CHR1_END 0x38FFF

#define CHR2_START 0x39000
#define CHR2_END 0x58fff

#define PRG1_START 0xB5000
#define PRG1_END 0xD4fFF

#define PRG2_START 0xD5000
#define PRG2_END 0xF4fFF




#define IMA_LEN 1474560
#define NES_LEN (40976)

#define NES_HEADER_LEN 16

#define PRGSIZE (16<<10)
#define CHRSIZE (8<<10)

int main(int argc,char* args[])
{

    char file0[60];
    strcpy(file0,BASE_IMA);
    char file1[60];
    strcpy (file1, "15hustoj.nes");
    char file2[60];
    strcpy(file2, "balloon.nes");
    if (argc>=2) strcpy(file1,args[1]);
    if (argc==3) strcpy(file2,args[2]);
    if(argc==1){

        printf("Usage: nes2ima rom1.nes rom2.nes\n");
        printf("remember to prepare mapper4.ima\n");
        printf("download from http://95.hustoj.com/sb2000/mapper4.ima \n");
        return(0);

    }
    struct stat s1,s2;
    int fd;
    fd = open(file1, 1);
    fstat(fd,&s1);
    int nes1len=s1.st_size;
    //printf("nes1len:%d\n",nes1len);
    close(fd);
    fd = open(file2, 1);
    fstat(fd,&s2);
    int nes2len=s2.st_size;
    close(fd);
    FILE * f0=fopen(file0,"rb");
    FILE * f1=fopen(file1,"rb");
    FILE * f2=fopen(file2,"rb");

    unsigned char data[IMA_LEN];
    unsigned char nes1[nes1len];
    unsigned char nes2[nes2len];

    fread(data,1,IMA_LEN,f0);
    int tmp=nes1len;
    fread(nes1,1,tmp,f1);
    tmp=nes2len;
    fread(nes2,1,tmp,f2);

    printf("\n%c%c%c\n",data[0x36],data[0x37],data[0x38]);
    printf("\n%c%c%c\n",nes1[0],nes1[1],nes1[2]);

    int PRGNUM1=nes1[4];
    int CHRNUM1=nes1[5];
    int mapper1=nes1[7]>>4;

    int PRGNUM2=nes2[4];
    int CHRNUM2=nes2[5];
    int mapper2=nes2[7]>>4;
    printf("%s:\n",file1);
    printf("16k  ROM num :%d\n",PRGNUM1);
    printf(" 8k VROM num :%d\n",CHRNUM1);
    printf("  mapper num :%d\n",mapper1);

   printf("nes1len:%d\n",nes1len);


    printf("%s:\n",file2);
    printf("16k  ROM num :%d\n",PRGNUM2);
    printf(" 8k VROM num :%d\n",CHRNUM2);
    printf("  mapper num :%d\n",mapper2);
    printf("nes2len:%d\n",nes2len);


//    for (int i=0;i<4;i++){
//        printf("%.2X ",nes2[NES_HEADER_LEN+PRGSIZE+i]);
//    }
//    printf("\n");

    printf("PRG1:\n");
    for(int i=PRG1_START;i<=PRG1_END;i++){
//        printf("%.6x\n",((i-PRG1_START)%(PRGSIZE*PRGNUM1))+NES_HEADER_LEN);
        data[i]=nes1[((i-PRG1_START)%(PRGSIZE*PRGNUM1))+NES_HEADER_LEN];
    }
    //printf("nes1len:%d\n",nes1len);


    int nes1chrbase=(PRGSIZE*PRGNUM1)+NES_HEADER_LEN;

    printf("nes1chrbase:%d\nnes1len:%d \n CHR1:\n",nes1chrbase,nes1len);
    if (CHRNUM1>0){
        for(int i=CHR1_START;i<=CHR1_END;i++){
           // printf("%.6x\n",(i-CHR1_START)%(CHRSIZE*CHRNUM1)+nes1chrbase);
            data[i]=nes1[(i-CHR1_START)%(CHRSIZE*CHRNUM1)+nes1chrbase];
        }
    }

    if (argc==3){
        for(int i=PRG2_START;i<=PRG2_END;i++){
            data[i]=nes2[((i-PRG2_START)%(PRGSIZE*PRGNUM2))+NES_HEADER_LEN];
        }

        int nes2chrbase=(PRGSIZE*PRGNUM2)+NES_HEADER_LEN;
        if(CHRNUM2>0){
            for(int i=CHR2_START;i<=CHR2_END;i++){
                data[i]=nes2[(i-CHR2_START)%(CHRSIZE*CHRNUM2)+nes2chrbase];
            }
        }
    }else{
        strcpy(file2,"music.nes");

    }

    fclose(f2);
    fclose(f1);
    fclose(f0);
    int n=strlen(file1);
    char outfile[64];
    sprintf(outfile,"%s",file1);
    sprintf(outfile+n-4,"-%s",file2);
    n+=strlen(file2);
    sprintf(outfile+n-7,".ima");

    printf("%s\n",outfile);
    FILE * fp=fopen(outfile,"wb");
    fwrite(data,1,IMA_LEN,fp);
    fclose(fp);

    return 0;
}
