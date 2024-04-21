#include<stdio.h>
#include<graphics.h>
struct row{
  long date;
  long open;
  long close;
  long low;
  long high;
  long vol;
};
struct row data[365];
long total=0;
long max=0;
long min=100000;
long vmax=0;

float xstep=1;
float ystep=1;
float vstep=1;
int bot0,bot1;
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
 	for(i=0;i<total;i++){ 
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
	for(i=0;i<T;i++){
		sum+=data[i].close;
	}
	y1=bot0-(sum/T-min)*ystep;
	x1=xstep*T;
	setcolor(getbkcolor());   
	moveto(x1,y1);	
	setcolor(color);
	setlinestyle(0,0,1);
	for(i=T;i<total;i++){ 
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
	
       mline(1,WHITE);
       mline(5,GREEN);	
       mline(20,RED);	
       mline(60,YELLOW);	       
       kline();
}
int main (){
	int key=0;
	char code[10];
	int clen=0;
	 int gdriver=DETECT,gmode;
       registerbgidriver(EGAVGA_driver);
       initgraph(&gdriver, &gmode,".");
       sprintf(code,"600309");
       load(code,30);
       redraw();
    	while( (key=getch()) !=27 ){
   		if(key<= '9' && key>='0' ){
   			if(clen<6){
   				code[clen]=key;
   				clen++;
   				code[clen]='\0';
   				setfillstyle(SOLID_FILL,getbkcolor());
   				bar(0,0,getmaxx(),8);
   				setcolor(WHITE);
   				outtextxy(xstep,ystep,code);
   			}
   		}
	   	if(key==8){
	   			clen--;
   				code[clen]='\0';
   				setfillstyle(SOLID_FILL,getbkcolor());
   				bar(0,0,getmaxx(),8);
   				setcolor(WHITE);
   				outtextxy(xstep,ystep,code);
	   	}
   		if(key==13){
   			if(clen==6){
   				if(load(code,90)){
   					
   					redraw(); 
   				}
   				clen=0;
   				
   			}
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
       }
       
       closegraph();
}
