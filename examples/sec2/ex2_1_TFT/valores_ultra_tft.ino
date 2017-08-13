#include <Time.h>
//#include <TimeLib.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>  
#include <Ultrasonic.h>
//Pins for the screen
#define DC            9     
#define RST           8     
#define CS           10 
//Pins for the sensor
#define trigger 4
#define echo 5

static Adafruit_ST7735 TFT = Adafruit_ST7735(CS, DC, RST);
Ultrasonic ultrasonic(trigger, echo);

float average = 0;
float maximum = 0;
float minimum = 100;
float data[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int indice = 0;
float sum = 0;

void printDigits(int digits)
{
  TFT.print(":");
  if(digits < 10)
    TFT.print('0');
  TFT.print(digits);
}

void setup() 
{
  Serial.begin(9600);
  TFT.initR(INITR_BLACKTAB);
    
}

void loop() 
{
  time_t t = now();
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  data[indice] = cmMsec;
  sum += data[indice];
  
  if(cmMsec < minimum)
    minimum = cmMsec;
  if(cmMsec > maximum)
    maximum = cmMsec;
    
  TFT.fillScreen(ST7735_WHITE);
  TFT.setTextColor(ST7735_BLACK);
  TFT.setTextSize(1);
  TFT.setCursor(0, 10);
  TFT.print("Distance:");
  TFT.print(cmMsec);
  TFT.print(" cm");
  
  TFT.setCursor(0, 25);
  TFT.print("Time:");
  TFT.print(hour());
  printDigits(minute(t));
  printDigits(second(t));
  
  TFT.setCursor(0, 40);
  TFT.print("Minimum:");
  TFT.println(minimum);
  TFT.print("Maximum:");
  TFT.println(maximum);
  TFT.print("average:");
  average = (sum/indice);
  TFT.println(average);
  if(indice == 9)
  {
    indice = 0;    
    sum = 0;
  }
  indice++;
  
  delay(500);
  
}
