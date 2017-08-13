#include <SPI.h>
#include <TFT.h>
#include <Time.h>
#include <Ultrasonic.h>

#define cs   10
#define dc   9
#define rst  8  
TFT TFTscreen = TFT(cs, dc, rst);

#define trigger 4
#define echo 5
Ultrasonic ultrasonic(trigger, echo);

int xPos = 0;


void setup(){
  TFTscreen.begin();
  TFTscreen.background(0,0,0); 
}

void loop(){
  long microsec = ultrasonic.timing();
  int sensor = ultrasonic.convert(microsec, Ultrasonic::CM);
  int graphHeight = map(sensor,0,90,0, TFTscreen.height());
  TFTscreen.stroke(255,255,255);
  TFTscreen.line(xPos, TFTscreen.height() - graphHeight, xPos, TFTscreen.height());
  if (xPos >= 160) 
  {
    xPos = 0;
    TFTscreen.background(0,0,0); 
  }
  else
    xPos++;
  delay(100);
}
