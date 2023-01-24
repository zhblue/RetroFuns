#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
/*
  本文件的功能是给非整数次幂的nes文件补齐，以刷入kazzo烧录卡


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
CHRROM 1: 19000-38FFF
CHRROM 2: 39000-58FFF
MENU CHR: 59000-59FFF
MENU CHR: 5A000-5AFFF
PRGROM 1: B5000-D4FFF
PRGROM 2: D5000-F4FFF

mapper0：
    game1 chr：19400-393FF prg:B4800-D47FF,
    game2 chr: 39400-593FF prg:D4800-F47FF
my:
    game2 chr:39400h-D87FFh   prg:EC800h - E87FFh
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

#define BASE_IMA "008.ima"

#define PRG1_START 0x29c00    //米老鼠 32k+32k mapper3               menu2
#define PRG1_END 0x31bff      //
#define CHR1_START 0x59c00    
#define CHR1_END 0x61bff


#define PRG2_START 0x39C00   //唐老鸭128k+0k  mapper2                 menu1
#define PRG2_END 0x59BFF   
#define CHR2_START 0x00
#define CHR2_END 0x00

#define PRG3_START 0x35c00  // 有两处一样的   //雷鸟号16k+8k  mapper0   35c00-39bff    6dc00-71bff     menu3
#define PRG3_END 0x39bff                            //                  39bff
#define CHR3_START 0x69c10          //0x69c10    0x31c10 
#define CHR3_END 0x6bbff		     //0x6bbff    0x33bff


#define IMA_LEN 737280
//#define NES_LEN (40976)

#define NES_HEADER_LEN 16

#define PRGSIZE (16<<10)
#define CHRSIZE (8<<10)
void fix(char * file1){
	
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
	fclose(f1);
	
	int PRGNUM1=nes1[4];
	int CHRNUM1=nes1[5];
	int mapper1=nes1[7]>>4;
	
	printf("PRGNUM:%d\tCHRNUM:%d\n",PRGNUM1,CHRNUM1);	
	int upPRG=PRGNUM1;
	int upCHR=CHRNUM1;
	for(int i=1;i<10;i++){
		if(1<<i >= PRGNUM1){
			upPRG=1<<i;
			break;
		} 
	}
	if(CHRNUM1>0){
		for(int i=1;i<10;i++){
			if(1<<i >= CHRNUM1){
				upCHR=1<<i;
				break;
			} 
		}
	}
	
	printf("upPRG:%d\tupCHR:%d\n",upPRG,upCHR);	
	
	
	printf("%s:\n",file1);
	printf("16k  ROM num :%d\t",PRGNUM1);
	printf(" 8k VROM num :%d\t",CHRNUM1);
	printf("  mapper num :%d\t",mapper1);
	printf("nes1len:%d\n",nes1len);
	char outfile[64];
	int newNESLEN=nes1len+(upPRG-PRGNUM1)*PRGSIZE+(upCHR-CHRNUM1)*CHRSIZE;
	
	if(upPRG==PRGNUM1 && upCHR==CHRNUM1) {
		printf("PRG-CHR-ROM无需修复!\n");
		//gets(outfile);
		return;
	}else{
		f1=fopen(file1,"rb");
		nes1=(unsigned char * )malloc(newNESLEN);
		fread(nes1,1,nes1len,f1);
		fclose(f1);	
	}
	
	sprintf(outfile,"%s-fixed.nes",file1);
	printf("processing ... %s\n",outfile);
	
	// |header 16 bytes|PRG PRGNUM1*PRGSIZE| CHR CHRNUM1*CHRSIZE |
	// |header 16 bytes|PRG PRGNUM1*PRGSIZE| REPEAT-PRG PRGSIZE*(upPRG-PRGNUM1) | CHR CHRNUM1*CHRSIZE| REPEAT-CHR CHRSIZE*(upCHR-CHRNUM1)
	
	//int CHRREPEAT_START=nes1len-CHRSIZE*(upCHR-CHRNUM1);
	int CHRREPEAT_LENGTH=CHRSIZE*(upCHR-CHRNUM1);
	//REPEAT-CHR
	for(int i=newNESLEN-1;i>newNESLEN-CHRREPEAT_LENGTH;i--){
		nes1[i]=nes1[nes1len-(newNESLEN-i)];
	}
	//oldchr
	int old_char_start=newNESLEN-CHRREPEAT_LENGTH-CHRNUM1*CHRSIZE;
	for(int i=newNESLEN-CHRREPEAT_LENGTH;i>old_char_start;i--){
		nes1[i]=nes1[nes1len-(newNESLEN-CHRREPEAT_LENGTH-i)];
	}
	//REPEAT-PRG
	int repeat_prg_start=old_char_start-PRGSIZE*(upPRG-PRGNUM1);
	for(int i=old_char_start;i>repeat_prg_start;i--){
		nes1[i]=nes1[nes1len-CHRNUM1*CHRSIZE-(old_char_start-i)];
	}
	
	FILE * fp=fopen(outfile,"wb");
	
	nes1[4]=upPRG;
	nes1[5]=upCHR;
	
	fwrite(nes1,1,newNESLEN,fp);
	
	fclose(fp);

}
int isNESFile(const char fname[])
{
	int l = strlen(fname);
	if (l <= 4 || stricmp(fname + l - 4, ".nes") != 0)
		return 0;
	else
		return l - 3;
}

void all(){
	char vgmfile[1024]=".";	
	
	DIR *pdir;
	struct dirent *pent;
	if(strlen(vgmfile)==0){
			strcpy(vgmfile,".");
		}
	pdir=opendir(vgmfile); //opendir for playlist
	if (!pdir){
		printf ("opendir() failure; terminating");
		exit(1);
	}
	
	while ((pent=readdir(pdir))){
		
		if(isNESFile(pent->d_name)){
			char filepath[1024];
			sprintf(filepath,"%s\\%s",vgmfile,pent->d_name);
			fix(filepath);
		}
	}
	if (errno){
		printf ("readdir() failure; terminating");
		exit(1);
	}
	closedir(pdir);

	
	
}


int main(int argc,char* args[])
{

    char file1[60];
    strcpy (file1, "double.nes");
    
	
	if(argc==1){

        printf("sigle file Usage: %s rom1.nes \n",args[0]);
        all();
        return(0);

    }else if (argc>=2){
		
		for(int k=1;k<argc;k++){
			strcpy(file1,args[k]);
			fix(file1);
			
		}
		
	}

    return 0;
}
