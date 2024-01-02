#include<time.h>
#include<math.h>
#define EVENT PB_1
#define P0 PB_2
#define P1 PB_0
#define P2 PA_7
#define P3 PA_4
#define P4 PA_3
#define P5 PA_2
#define P6 PA_1
#define P7 PA_0
#define V0 PA_5
#define V1 PA_6
const int DISP[8]={P0,P1,P2,P3,P4,P5,P6,P7}; 
const int DISPB[8]={P0,P1,P2,P3,P4,P5,P6,P7}; 
int mode=0;
char POINT=0;
void setup() {
  //Serial.begin(115200);
  pinMode(V0, INPUT);
  pinMode(V1, INPUT_PULLDOWN);

  analogReadResolution(12);
 // put your setup code here, to run once:
  for(int i=0;i<8;i++)
      pinMode(DISP[i], OUTPUT);
 // Serial.begin(115200);
 // Serial.printf("Hello, Air001. \n");
  pinMode(EVENT, INPUT);
  mode=digitalRead(EVENT);  //开机时水银开关状态决定工作模式
  if(mode){
    if(digitalRead(V0)==HIGH){
        mode=2;
    }else{
        pinMode(V0, INPUT_PULLDOWN);
    }
  }
  srand(analogReadMillivolts(V0));
}
char font[12]={126,72,61,109,75,103,119,76,127,111,47,90};
int count=0;
void disp(char data){
  
  for(int i=0;i<7;i++){
      if(data & (1<<i)){
        digitalWrite(DISP[i], HIGH);
      }else{
        digitalWrite(DISP[i], LOW);
      }
  }
  if(POINT) digitalWrite(DISP[7], HIGH);
  else digitalWrite(DISP[7], LOW);
}
void display(int msg){
      //digitalWrite(PB_1, HIGH);
    disp(font[msg % 12]);
     
}
int iabs(int a){
  if (a>0) return a;
  else -a;
}
int vref=0;
void loop() {
  /*
  int diff=abs(analogReadMillivolts(PA0),analogReadMillivolts(PA1));
  Serial.printf("Voltage is %d mv \r\n", diff);
  Serial.printf("Chip temp is %d C \r\n", analogReadTempSensor());
  Serial.printf("Vref is %d mv \r\n", analogReadVref());
  */
  if(mode==HIGH){
    // 随机数骰子模式
      POINT=0;
      for(int i=0;i<12;i++){
        display(i);
        delay(100);
      }
      POINT=1;
      display(rand()%12);
      while(digitalRead(EVENT)==LOW) ;
     
  }else if (mode==2){
     //电压表模式
      vref=iabs(analogReadMillivolts(V0))+5;
      POINT=1;
      display(vref/1000);
      delay(800);
      POINT=0;
      display((vref/100)%10);
      delay(500);
      display((vref/1000)%10);
      delay(1200);
     
  }else{
       //温度计模式
      vref=analogReadTempSensor();
      POINT=0;
      display(vref/10);
      delay(500);
      POINT=1;
      display(vref%10);
      delay(1200);
  }
}