#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*
这个程序修复由于CHR-ROM不是2的整数次幂而导致无法用kazzo烧写的问题。




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


*/
// mapper0.ima
/*
#define BASE_IMA "mapper0.ima"

#define CHR1_START 0x19400
#define CHR1_END 0x393FF

#define CHR2_START 0x39400
#define CHR2_END 0x593FF

#define PRG1_START 0xB4800
#define PRG1_END 0xD47FF

#define PRG2_START 0xD4800
#define PRG2_END 0xF47FF

*/


// mapper4 based


#define NES_HEADER_LEN 16

#define PRGSIZE (16<<10)
#define CHRSIZE (8<<10)

int main(int argc,char* args[])
{

    char file1[60];
    strcpy (file1, "double.nes");
    
	if (argc>=2) strcpy(file1,args[1]);
    
	if(argc==1){

        printf("Usage: %s rom1.nes \n",args[0]);
        gets(file1);
        return(0);

    }
    struct stat s1;
    int fd;
    fd = open(file1, 1);
    fstat(fd,&s1);
    int nes1len=s1.st_size;
    //printf("nes1len:%d\n",nes1len);
    close(fd);
   
	FILE * f1=fopen(file1,"rb");
  
 
    unsigned char * nes1=(unsigned char * )malloc(nes1len);
    
    fread(nes1,1,nes1len,f1);
    
    int PRGNUM1=nes1[4];
    int CHRNUM1=nes1[5];
    int mapper1=nes1[7]>>4;
  
    printf("PRGNUM:%d\tCHRNUM:%d\n",PRGNUM1,CHRNUM1);	
	int uplen=CHRNUM1;
	for(int i=1;i<10;i++){
		if(1<<i >= CHRNUM1){
			uplen=1<<i;
			break;
		} 
	}

	printf("UPLEN:%d\n",uplen);	

	
    printf("%s:\n",file1);
    printf("16k  ROM num :%d\t",PRGNUM1);
    printf(" 8k VROM num :%d\t",CHRNUM1);
    printf("  mapper num :%d\t",mapper1);
    printf("nes1len:%d\n",nes1len);
	int REPEAT_START=nes1len-CHRSIZE*(uplen-CHRNUM1);
	int REPEAT_LENGTH=CHRSIZE*(uplen-CHRNUM1);
	char outfile[64];
	
    if(uplen==CHRNUM1) {
		printf("CHR-ROM无需修复!\n");
		gets(outfile);
		return 1;
	}

    sprintf(outfile,"%s-fixed.nes",file1);
    printf("processing ... %s\n",outfile);
    FILE * fp=fopen(outfile,"wb");
	
	nes1[5]=uplen;
    fwrite(nes1,1,nes1len,fp);
	
	fwrite(&nes1[REPEAT_START],1,REPEAT_LENGTH,fp);
	
    fclose(fp);

    return 0;
}
