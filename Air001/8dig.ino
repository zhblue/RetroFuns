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
const int DISP[8]={P0,P1,P2,P3,P4,P5,P6,P7}; 
const int DISPB[8]={P0,P1,P2,P3,P4,P5,P6,P7}; 
int sync=0;
char POINT=0;
void setup() {
  // put your setup code here, to run once:
 for(int i=0;i<8;i++)
      pinMode(DISP[i], OUTPUT);
 // Serial.begin(115200);
 // Serial.printf("Hello, Air001. \n");
  pinMode(EVENT, INPUT);
  sync=digitalRead(EVENT);
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
    disp(font[msg]);
     
}
void loop() {
  // put your main code here, to run repeatedly:
  POINT=0;
  for(int i=0;i<12;i++){
    display(i);
    delay(100);
  }
  POINT=1;
  display(rand()%12);
  while(digitalRead(EVENT)==LOW) nop();
}
