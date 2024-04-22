#include<stdio.h>
#include"mouse.h"
#include<graphics.h>
struct row{
  long date;
  long open;
  long close;
  long low;
  long high;
  long vol;
};
struct row data[1280];
long total=0;
long max=0;
long min=100000;
long vmax=0;

float xstep=1;
float ystep=1;
float vstep=1;
int bot0,bot1;
int restart=0;
int load(char * code,int newTotal){
  int i;
  int mark;
  char filename[1024];
  FILE * f;
  sprintf(filename,"htget -quiet -o %s.txt http://192.168.2.36/stock.php?code=%s&t=%d",code,code,newTotal);
  system(filename);
  /* system("cls");  */
  sprintf(filename,"%s.txt",code);
  f=fopen(filename,"r");
  setcolor(YELLOW);
  	if(f!=NULL){
		  min=1000000;max=0;vmax=0;
		  fscanf(f,"%d",&total);
		  for(i=total-1;i>=0;i--){
			fscanf(f,"%ld%ld%ld%ld%ld%ld"
						,&data[i].date
						,&data[i].open
						,&data[i].close
						,&data[i].low
						,&data[i].high
						,&data[i].vol

			);
			if(min>data[i].low) min=data[i].low;
			if(max<data[i].high) max=data[i].high;
			if(vmax<data[i].vol) vmax=data[i].vol;
		  }
		  data[total].date=0;
		  fclose(f);
		  bot1=getmaxy();
		  bot0=bot1*0.7;
		  xstep=getmaxx()-40;
		  ystep=bot0;
		  if(total>0) xstep/=(total+2);

		  if(max>min) ystep/=(max-min);
		  vstep=getmaxy()*0.28;
		  if(vmax>0) vstep/=vmax;
			  /*  sprintf(filename,"xstep:%f ystep%f\n",xstep,ystep);    */
		cleardevice();
		 outtextxy(xstep,ystep,filename);

		for(i=0;i<10;i++){
			mark=i*bot0/10;
			setcolor(DARKGRAY);
			setlinestyle(i%4+1,i,1);
			line(0,mark,getmaxx(),mark);
			setcolor(WHITE);
			sprintf(filename,"%.2f",((bot0-mark)/ystep+min)/100);
			outtextxy(getmaxx()-40,mark,filename);


		}
		for(i=0;i<5;i++){
			mark=i*(getmaxx()-40)/5+xstep/2;
			setcolor(DARKGRAY);
			setlinestyle(i%4+1,i,1);
			line(mark,0,mark,bot0);
			setcolor(WHITE);
			sprintf(filename,"%ld",data[mark/xstep].date );
			outtextxy(mark-32,bot0,filename);
		}
		
		  return 1;
	}else{
		  outtextxy(xstep,ystep,"data loading error! ");
		  return 0;
	}
}
int kline(){
	int i=0;
	int color=RED;
	int x0,y0,x1,y1,x2,y2,y3;
 	for(i=restart;i<total;i++){
		if(data[i].open>data[i].close) color=GREEN;
		else color=RED;
		x0=xstep*(i+1);
		x1=x0-xstep/2;
		x2=x0+xstep/2;
		y0=bot0-(data[i].high-min)*ystep;
		y3=bot0-(data[i].low-min)*ystep;
		y1=bot0-(data[i].open-min)*ystep;
		y2=bot0-(data[i].close-min)*ystep;
		if (x2-x1>1) x1++;
		if (x2-x1>1) x1++;
		setcolor(color);
		setfillstyle(SOLID_FILL,color);
		line(x0,y0,x0,y3);
		bar(x1,y1,x2,y2);
	/*	outtextxy(x0,y2,"*");
		setfillstyle(SOLID_FILL,LIGHTGRAY);   */
		bar(x1,bot1,x2,bot1-data[i].vol*vstep);
	}
	return 0;
}
int mline(int T,int color){
	int i=0;
	int x0,y0,x1,y1,x2,y2,y3;
	double sum=0;
	if(restart){
		for(i=restart-T;i<restart;i++){
			sum+=data[i].close;
		}
		y1=bot0-(sum/T-min)*ystep;
		x1=xstep*restart;
		setcolor(getbkcolor());
		moveto(x1,y1);
		setcolor(color);
		setlinestyle(0,0,1);
	}else{
		
		for(i=0;i<T;i++){
			sum+=data[i].close;
		}
		y1=bot0-(sum/T-min)*ystep;
		x1=xstep*T;
		setcolor(getbkcolor());
		moveto(x1,y1);
		setcolor(color);
		setlinestyle(0,0,1);
	}

	if(restart) i=restart;else i=T;
	for(;i<total;i++){
		x0=xstep*(i+1);
		sum-=data[i-T].close;
		sum+=data[i].close;
		y0=bot0-ystep*(sum/T-min);
		lineto(x0,y0);
		x1=x0;y1=y0;
	/*	outtextxy(x0,y2,"*");   */
	}
	return 0;
}
int redraw(){
 	if(mouse_present) ms_hide_cursor();
       mline(1,WHITE);
       mline(5,GREEN);
       mline(20,RED);
       mline(60,YELLOW);
       kline();
       if(mouse_present) ms_show_cursor();
}
int display(int x,int y,char* msg){
/*	setfillstyle(SOLID_FILL,getbkcolor());
	bar(x,y,x+strlen(msg)*8 ,y+8);
*/	setcolor(WHITE);
	outtextxy(x,y,msg);
}
int loadOne(char * code){
  int i,x1,x2;
  int mark;
  char filename[1024];
  FILE * f;
  sprintf(filename,"htget -quiet -o %s.now http://192.168.2.36/stock.php?code=%s&t=1",code,code);
  system(filename);
  /* system("cls");  */
  sprintf(filename,"%s.now",code); 
   f=fopen(filename,"r");
   if(f!=NULL){
	   i=total;
	   fscanf(f,"%ld%ld%ld%ld%ld"
							,&data[i].date
							,&data[i].open
							,&data[i].close
							,&data[i].low
							,&data[i].high

			);
	   fclose(f);
	   total++;
	   	   
	   x1=xstep*(total)-xstep/2;
	   x2=x1+xstep;
	   setfillstyle(SOLID_FILL,getbkcolor());
	   bar(x1,0,x2,getmaxy());
	   restart=total-1;
	   redraw();
	   restart=0;
	   total--;
   }

}
int main (){
	int key=0;
	char code[10];
	int clen=0;
	 int gdriver=DETECT,gmode;
	 int tlen=30;
	 int color=1;
	 int i=0;
	 int mousetype;
	 int mouseX,mouseY,mousex=0,mousey=0,mouseDay=0,button=0,press_count,column,row;
	 char mousePos[64];
	 long ticks=40000;
       registerbgidriver(EGAVGA_driver);
       initgraph(&gdriver, &gmode,".");
       sprintf(code,"600309");
       load(code,30);
       redraw();
       mouse_present=ms_reset(&mousetype);
       if(mouse_present) ms_show_cursor();
       
    	while( 1 ){
    		if(kbhit()){
    			if((key=getch())==27) break;
	   		if(key<= '9' && key>='0' ){
	   			if(clen<6){
	   				code[clen]=key;
	   				clen++;
	   				code[clen]='\0';
	   				setfillstyle(SOLID_FILL,getbkcolor());
	   				bar(0,0,getmaxx(),8);
	   				setcolor(WHITE);
	   				display(xstep,ystep,code);
	   			}
	   		}
		   	if(key==8){
		   			clen--;
	   				code[clen]='\0';
	   				setfillstyle(SOLID_FILL,getbkcolor());
	   				bar(0,0,getmaxx(),8);
	   				setcolor(WHITE);
	   				display(xstep,ystep,code);
		   	}
	   		if(key==13){
	   			if(clen==6){
	   				if(load(code,90)){
	   					redraw(); 
	   				}
	   			}else{
	   				sscanf(code,"%d",&tlen);
	   				if(tlen>10 && tlen<total){
	   					 mline(tlen,(++color % 15) +1);
	   					if(tlen==66){
	   						for(i=2;i<66;i++){
	   							 mline(i,(++color % 15) +1);
	   						}
	   						 kline();
	   					}
	   				}
	   			}
	   			clen=0;
	   		}
	   		if(key==45 && total <getmaxx() ){
	   				if(load(code,total*2)){
		   				
		   				redraw(); 
	   				}
	   		}
	  		if((key==43||key==61) && total >20 ){
	   				if(load(code,total/2)){
						
						redraw(); 
	   				}
	   		}
	   		if(key==32){   /*  空格，加载当日 */
	   			loadOne(code);
	   		}
		
		}
		
	   	if(mouse_present){
	   		ms_get_mouse_pos(&mouseX,&mouseY);
	   		if(mousex!=mouseX||mousey!=mouseY){
	   			mouseDay=(mouseX-xstep/2)/xstep;
	   			if (mouseDay>=total||mouseDay<0) mouseDay=total-1;
		   		sprintf(mousePos,"%ld O:%.2f C:%.2f H:%.2f L:%.2f        [%.2f]",
		   				data[mouseDay].date,data[mouseDay].open/100.0,data[mouseDay].close/100.0,
		   				data[mouseDay].high/100.0,data[mouseDay].low/100.0
		   				,((bot0-mouseY)/ystep+min)/100.0        /* mouse price */
		   				);
		   		setfillstyle(SOLID_FILL,getbkcolor());
		   		bar(0,bot0+8,getmaxx(),bot0+16);
		   		setcolor(WHITE);
	   			display(0,bot0+8,mousePos);
	   			mousex=mouseX;
	   			mousey=mouseY;
	   		}
	   		button=ms_button_press_status(0,&press_count,&column,&row);
	   		if(button==1){
	   			sprintf(mousePos,"%.2f",((bot0-mouseY)/ystep+min)/100.0);      /* mouse price */
	   			ms_hide_cursor();
	   			display(mousex,mousey,mousePos);
	   			ms_show_cursor();
	   		}
	   		if(button==2){
	   			ms_hide_cursor();
	   			if(mouseDay>0 && mouseDay < total )mline(mouseDay,(++color % 15) +1);
	   			ms_show_cursor();
	   		}
	   		
	   	}
		if(ticks++>25000){
			if( data[total].date >0 ){
				loadOne(code);
			}
			ticks=0;
		}
       }
       
       closegraph();
}
