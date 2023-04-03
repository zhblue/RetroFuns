/* 
   written by zhblue in Turbo C 2.0  
   licensed by GPL v2  
   2023.3.20
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <dir.h>
#include <conio.h>
#define F_BLACK 0
#define F_BLUE 1
#define F_GREEN 2
#define F_RED 4
#define F_INTENSE 8
#define F_WHITE 15
#define B_BLACK 0
#define B_BLUE 16
#define B_GREEN 32
#define B_RED 64
#define B_INTENSE 128
#define B_WHITE 240
int index=0;
char* game[128];

char * basename(char * x){
   int l=strlen(x)-1;
   while(l>0){
	if(x[l]=='\\') break;
	l--;
   }

   if(x[l]=='\\')return &x[l+1];
   else return &x[l];
}

int level=0;
int scandir(char * target){


	char cmd[1024];
	char path[1024];
	char dir[1024];
	char prob[5][64];

	struct ffblk vgms;
	int next=0;
	int ret=0;
	int err=0;
	int i=0;
	level++;
	if(index>=512||level>7) return level--;

	sprintf(dir,"%s\\*",target);

	sprintf(prob[0],"play.bat");
	sprintf(prob[1],"play.exe");
	sprintf(prob[2],"%s.bat",basename(target));
	sprintf(prob[3],"%s.com",basename(target));
	sprintf(prob[4],"%s.exe",basename(target));

	for( i=0;i<5;i++){
	       /*	printf("%s\\%s\n",target,prob[i]);    */
		sprintf(cmd,"%s\\%s",target,prob[i]);
		err=access(cmd,0);
		if(err==0){
			  /* printf("find one game: cd %s - %s\n",target,prob[i]);  */
			sprintf(game[index],"%s\\%s",target,prob[i]);
			index++;
			if(strcmp(basename(target),"SBVGM")==0){
			    printf("SBVGM...\n");
			    continue;
			}else{
			    level--;
			    return index;
			}

		}else{
			  /* try next */

		}
	}





	next=findfirst(dir,&vgms,16);
	while(!next){


		if(strlen(vgms.ff_name)==0||strcmp(vgms.ff_name,".")==0||strcmp(vgms.ff_name,"..")==0 ){
			 next=findnext(&vgms);
			 continue;
		}
		  /*printf("looking up %s ...%d \n",vgms.ff_name,level); */
		printf(".");
		sprintf(path,"%s\\%s",target,vgms.ff_name);
		if((vgms.ff_attrib & 16 ) && strlen(vgms.ff_name)>0 ){
		   /*  printf("%s ... is a sub dir \n",vgms.ff_name);*/
			sprintf(cmd,"scan %s\%s",target,vgms.ff_name);
			  /*printf("todo:%s\n",basename(target));*/
			if(strcmp(basename(target),"SBVGM")==0){

			    printf("found music dir in SBVGM ...%s\n",vgms.ff_name);

			    sprintf(game[index],"%s\\play %s",target,vgms.ff_name);

			    index++;
			}else{
			    scandir(path);
			}
		}
/*		sleep(1);*/
		if(kbhit()){
			if(getch()==27){
				printf("Double Esc pressed ... Exit !\n");
				break;
			}
		}
		next=findnext(&vgms);
		ret++;
	}



	level--;
	return ret;

}
char * getpath(char * target,char * dir){

   sprintf(dir,"%s",target);
   dir[basename(target)-target-1]='\0';

   return dir;
}
char home[256];
char myhome[64];
void play(char * game){
	    char dir[128];
	    char cmd[128];
	    sprintf(cmd,"\\%s",home);
	    chdir(cmd);
	    sprintf(cmd,"cd %s",getpath(game,dir));
	      system(cmd);

	    system(basename(game));

	    sprintf(cmd,"cd \\%s",home);
	       system(cmd);


}
void printn(int n){

   int i=0;
   for(i=0;i<n;i++)
      printf(" ");
}

#define COLWIDTH (17)
int main(int argn,char ** argv){
	char dir[1024]=".";
	int row=0;
	int i=0;

	int choose=-1;
	char input[64];
	char cmd[32];
	for(i=0;i<128;i++)
	game[i]=(char *)malloc(128);

	getcurdir(0,home);

	printf("home:%s\n",home);

	sprintf(myhome,"\\%s",home);

	if (argn>=2){
		printf("[%s]\n",argv[1]);
		sscanf(argv[1],"%s",dir);
	}

	printf("scan files : %s\n",dir);
	scandir(dir);

	printf("Total: %d DOS Games / FM-Musics found \n\n",index);



     while(stricmp(input,"Q")!=0){
	system("mode 80");
	for( i=0;i<index;i++){
	  textcolor(F_RED);
	  printf("%d:",i+1);
	  textcolor(F_WHITE);
	  if(strcmp(basename(getpath(game[i],dir)),"SBVGM")==0){
		sprintf(cmd,"%s",basename(game[i]));
	  }else{
		sprintf(cmd,"%s",basename(getpath(game[i],dir)));
	  }
	  printf("%s",cmd);
	  if(i<9) printf(" ");
/*	  if(cmd[4]!=' ') printn(4);      */
	  if((i+1)%4==0) {
		printf("\n");
		row++;
	  }else {
		if(strlen(cmd)<COLWIDTH)
			printn(COLWIDTH - strlen(cmd));
		/* printf("\t"); */
	  }

	  if(row>20 || i == index-1){
	     printf("\nChoose a number to play (Q for quit):");
	     input[0]='\0';
	     gets(input);

	     choose=0;
	     choose=atoi(input);

	     if( choose>0 && choose <= index ){
		play(game[choose-1]);
	     }
	     if(stricmp(input,"Q")==0) break;
	     row=0;

	  }
	}
     }


	printf("Thank you for using Game Menu Player !\n");
	printf("      https://github.com/zhblue/RetroFuns\n");
	sleep(1);

	printf("goback:%s\n",myhome);


	chdir(myhome);

	sprintf(dir,"cd %s",myhome);
	system(dir);
	return 0;
}
