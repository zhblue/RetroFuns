#include <dos.h>
#include <time.h>
#include <stdio.h>
#define BUFFER_SIZE 1024
void get(char * name,char * target, unsigned int * val,char * to ){
	if(strcmp(name,target)==0){
 			printf(" %s[%u]",target,val);
 			*to = val;
 	}
}
void getx(char * name,char * target, unsigned int * val,unsigned int * to ){
	if(strcmp(name,target)==0){
 			printf(" %s[%u]",target,val);
 			*to = val;
 	}
}
int callBIOS(char * cmd){
    union REGS regs;
    int num;
    char name[8];
    unsigned int val;
    int call;
    int pos=3;
    regs.h.ah=regs.h.al=regs.h.bh=regs.h.bl=regs.h.ch=regs.h.cl=regs.h.dh=regs.h.dl=regs.h.ax=regs.h.bx=regs.h.cx=regs.h.dx=0;
    num=sscanf(cmd,"%x",&call);
    if(num==1){
    	printf("call BIOS %x:\n",call);
       while(num=sscanf(cmd+pos,"%s %x",name,&val)==2){
 /*   		printf("%s %d",name,val);     */
 		get(name,"ah",val,&regs.h.ah);
 		get(name,"al",val,&regs.h.al);
 		get(name,"bh",val,&regs.h.bh);
 		get(name,"bl",val,&regs.h.bl);
 		get(name,"ch",val,&regs.h.ch);
 		get(name,"cl",val,&regs.h.cl);
 		get(name,"dh",val,&regs.h.dh);
 		get(name,"dl",val,&regs.h.dl);
 		getx(name,"ax",val,&regs.x.ax);
 		getx(name,"bx",val,&regs.x.bx);
 		getx(name,"cx",val,&regs.x.cx);
 		getx(name,"dx",val,&regs.x.dx);
		getx(name,"si",val,&regs.x.si);
		getx(name,"di",val,&regs.x.di);
		

    		pos+=6;

       }
       int86(call , &regs, &regs);
       printf("\nresult:\n\tah[%u] al[%u] bh[%u] bl[%u] \n\tch[%u] cl[%u] dh[%u] dl[%u] \n\tax[%u] bx[%u] cx[%u] dx[%u] \n",
       		regs.h.ah,regs.h.al,regs.h.bh,regs.h.bl,regs.h.ch,regs.h.cl,regs.h.dh,regs.h.dl,regs.h.ax,regs.h.bx,regs.h.cx,regs.h.dx);
    	printf("\n");
    }else{
	printf("%s\n",cmd);
   }
 /*     regs.h.ah = ah;
    regs.h.al = al;
    */

    return 0;
}


int main(int argn ,char ** argv){
   char key=0;
   unsigned int i,j;
   char line[BUFFER_SIZE];
   char script[BUFFER_SIZE]="bios.txt";
   FILE * fp;
   if (argn>=2){
		printf("open [%s]\n",argv[1]);
		sscanf(argv[1],"%s",script);
   }
   fp = fopen(script, "r");
    if (fp != NULL){
		while (fgets(line, BUFFER_SIZE - 1, fp))
		{
			if(line[0]=='#'){
				printf("%s\n",line);
			}else if(line[0]=='S'){
				delay(500);
			}else{
				callBIOS(line);
			}
		 }
	}else{
		printf("put your test case in file bios.txt £¬for example : \n");
		printf("#init parallel port 1\n");
		printf("17 ah 01 dx 00\n");
		printf("#light up LED1\n");
		printf("17 ah 00 al 01 dx 00\n");
	}
   
   return 0;
}




