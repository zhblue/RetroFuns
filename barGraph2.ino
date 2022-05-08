/*
  LED bar graph

  Turns on a series of LEDs based on the value of an analog sensor.
  This is a simple way to make a bar graph display. Though this graph uses 10
  LEDs, you can use any number by changing the LED count and the pins in the
  array.

  This method can be used to control any series of digital outputs that depends
  on an analog input.

  The circuit:
  - LEDs from pins 2 through 11 to ground

  created 4 Sep 2010
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/BarGraph
*/

// these constants won't change:
const int analogPinA = A0;   // the pin that the potentiometer is attached to
const int analogPinB = A1;   // the pin that the potentiometer is attached to
const int ledCount = 10;    // the number of LEDs in the bar graph
int MINA=1024;
int MAXA=0;
int MINB=1024;
int MAXB=0;
int loopTimes=0;
int ledPinsA[] = {
  2,3,4,5,6,7,8,9,10,11
};   // an array of pin numbers to which LEDs are attached
int ledPinsB[] = {
  12,11,10,9,8,7,6,5,4,3
};   // an array of pin numbers to which LEDs are attached


void setup() {
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPinsA[thisLed], OUTPUT);
    pinMode(ledPinsB[thisLed], OUTPUT);
  }
  while(true) loop();
}

void loop() {
  // read the potentiometer:
  loopTimes++;
  int sensorReadingA = analogRead(analogPinA);
  int sensorReadingB = analogRead(analogPinB);
  if (sensorReadingA>MAXA) MAXA=sensorReadingA;else if(loopTimes%500==0) MAXA--;
  if (sensorReadingA<MINA) MINA=sensorReadingA;//else MINA++;
  if (sensorReadingB>MAXB) MAXB=sensorReadingB;else if(loopTimes%500==0) MAXB--;
  if (sensorReadingB<MINB) MINB=sensorReadingB;//else MINB++;
  // map the result to a range from 0 to the number of LEDs:
  int ledLevelA = map(sensorReadingA, MINA, MAXA, 0, ledCount);
  int ledLevelB = map(sensorReadingB, MINB, MAXB, 0, ledCount);
 // ledLevelB=ledLevelA;
  
  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevelA) {
      digitalWrite(ledPinsA[thisLed], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else if(thisLed||loopTimes%15000==0){
      digitalWrite(ledPinsA[thisLed], LOW);
    }
  }
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevelB) {
      digitalWrite(ledPinsB[thisLed], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else if(thisLed||loopTimes%15000==0){
      digitalWrite(ledPinsB[thisLed], LOW);
    }
  }
}
