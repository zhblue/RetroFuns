#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <dir.h>
#include <conio.h>
int main(int argn,char ** argv){
    char dir[1024]=".";
    char cmd[1024];
    char todo[1024]="sbvgm -x -noscan -opl2lpt378";
    int tp=0,i=0;
    struct ffblk vgms;
    int next=0;
    if (argn>=2){
	printf("[%s]\n",argv[1]);
	sscanf(argv[1],"%s",dir);

	if (argn>2){
	    if(strstr(dir,"*")==NULL)
		sprintf(dir+strlen(dir),"\\*.*");
	    tp=0;
	    for(i=2;i<argn;i++){
		sprintf(todo+tp," %s",argv[i]);
		tp+=strlen(argv[i]+1);
	    }
	    printf("TODO:%s\n",todo);
	}else{
	    sprintf(dir+strlen(dir),"\\*.vgz");
	}
        printf("scan files : %s\n",dir);

	next=findfirst(dir,&vgms,0);
	if(next){
	    sscanf(argv[1],"%s",dir);
	    sprintf(dir+strlen(dir),"\\*.vgm");
	    printf("scan files : %s\n",dir);
	    next=findfirst(dir,&vgms,0);
	}

	while(!next){
	    printf("find %s ... \n",vgms.ff_name);
	    printf("play %s ...\n",vgms.ff_name);
	    sprintf(cmd,"%s %s\\%s",todo,argv[1],vgms.ff_name);
	    system(cmd);
	    sleep(1);
	    if(kbhit()){
	       if(getch()==27){
		   printf("Double Esc pressed ... Exit !\n");
		   break;
	       }
	    }
	    next=findnext(&vgms);
	}
    }else{
	printf("Usage: foreach [DIR] [what to do]\n\n");
    }
    printf("Thank you for using foreach tools !\n");
    printf("      https://github.com/zhblue/RetroFuns\n");
    sleep(1);
    return 0;
}
