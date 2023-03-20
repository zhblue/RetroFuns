#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <dir.h>
#include <conio.h>
int index=0;
char game[512][64];

char * basename(char * x){
   int l=strlen(x)-1;
   while(l>0){
	if(x[l]=='\\') break;
	l--;
   }

   return &x[l+1];
}

int scandir(char * target){


	char cmd[1024];
	char path[1024];
	char dir[1024];
	char prob[5][64];

	struct ffblk vgms;
	int next=0;
	int ret=0;
	int err=0;

	if(index>1024) return 0;

	sprintf(dir,"%s\\*",target);

	sprintf(prob[0],"play.bat");
	sprintf(prob[1],"play.exe");
	sprintf(prob[2],"%s.bat",basename(target));
	sprintf(prob[3],"%s.com",basename(target));
	sprintf(prob[4],"%s.exe",basename(target));

	for(int i=0;i<5;i++){
	       //	printf("%s\\%s\n",target,prob[i]);
		sprintf(cmd,"%s\\%s",target,prob[i]);
		err=access(cmd,0);
		if(err==0){
			//printf("find one game: cd %s - %s\n",target,prob[i]);
			sprintf(game[index],"%s\\%s",target,prob[i]);
			index++;
			return index;
		}else{
			//try next

		}
	}





	next=findfirst(dir,&vgms,16);
	while(!next){

		if(strcmp(vgms.ff_name,".")==0||strcmp(vgms.ff_name,"..")==0 ){
			 next=findnext(&vgms);
			 continue;
		}
		//printf("looking up %s ... \n",vgms.ff_name);
		sprintf(path,"%s\\%s",target,vgms.ff_name);
		if(vgms.ff_attrib & 16){
		   //  printf("%s ... is a sub dir \n",vgms.ff_name);
			sprintf(cmd,"scan %s",path);
		   //	printf("todo:%s\n",cmd);
			scandir(path);
		}
//		sleep(1);
		if(kbhit()){
			if(getch()==27){
				printf("Double Esc pressed ... Exit !\n");
				break;
			}
		}
		next=findnext(&vgms);
		ret++;
	}




	return ret;

}
char * getpath(char * target,char * dir){

   sprintf(dir,"%s",target);
   dir[basename(target)-target-1]='\0';

   return dir;
}
char home[128];

void play(char * game){
	    char dir[128];
	    char cmd[128];
	    sprintf(cmd,"cd %s",getpath(game,dir));
	      system(cmd);

	    system(basename(game));

	    sprintf(cmd,"cd \\%s",home);
	       system(cmd);


}

int main(int argn,char ** argv){
	char dir[1024]=".";

	getcurdir(0,home);
	if (argn>=2){
		printf("[%s]\n",argv[1]);
		sscanf(argv[1],"%s",dir);
	}

	printf("scan files : %s\n",dir);
	scandir(dir);

	printf("Total: %d DOS Games found \n\n",index);


	int row=0;
	int choose=-1;
	char input[64];
	for(int i=0;i<index;i++){
	  printf("%d:%s",i+1,basename(getpath(game[i],dir)));

	  if((i+1)%5==0) {
		printf("\n");
		row++;
	  }else {
		printf("\t");
	  }

	  if(row>20 || i == index-1){
	     printf("Choose a number to play (Enter for Page Down):");

	     gets(input);
	     choose=atoi(input);
	     if( choose>0 && choose <= index ){
		play(game[choose-1]);
	     }

	     row=0;

	  }
	}


	printf("Thank you for using Game Menu Player !\n");
	printf("      https://github.com/zhblue/RetroFuns\n");
	sleep(1);
	return 0;
}
