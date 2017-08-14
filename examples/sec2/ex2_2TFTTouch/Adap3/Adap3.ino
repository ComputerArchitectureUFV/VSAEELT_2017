//Bibliotecas
#include <Adafruit_GFX.h>    // Biblioteca grafica
#include <Adafruit_TFTLCD.h> // Biblioteca especifica para o hardware
#include <TouchScreen.h>     // Biblioteca para a parte touch screen  
#include "Clock.h"           // Classe relogio   
#include "LibLeit.h"         // Classe relogio   
#include "Bitmap.h"          // Imagem em um arquivo

#define YP A3 // Y+ is on Analog1
#define XM A2 // X- is on Analog2
#define YM 9  // Y- is on Digital7
#define XP 8  // X+ is on Digital6

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// Posição da leitura
#define LEITX 10
#define LEITY 50

// Posição do maximo
#define MAXX 10
#define MAXY 90

// Posição do minimo
#define MINX 10
#define MINY 130

// Posição da media
#define MEDX 10
#define MEDY 170

// Posições para o gráfico
#define GRAXM 315
#define GRAYM 195

#define GRAXm 160
#define GRAYm 55

//Inicializacao de pinos utilizados pela parte de touchscreen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);
Sensor sens("DHT");
unsigned long int rate;

//Definicao de cores
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Inicializacao de pinos analogicos utilizados pelo controle do hardware
//Adafruit_TFTLCD tft(Chip Select, Command/Data, LCD Write, LCD Read, LCD Reset)
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

//desenha a hora, minuto e segundo na tela de segundo a segundo
void drawTime(Clock &clock)
{
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  Time t = clock.getTime();

  clock.update();
  
  if (!(t == clock.getTime())) {
    // Apaga valor antigo
    tft.println(t.toString());
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    // Desenha valor novo
    tft.println((clock.getTime()).toString());
  }
}

void drawSomething() {
  sens.SensorRead();
  
  tft.fillRect(10, 30, 120, 170, WHITE);

  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  
  tft.setCursor(LEITX, LEITY - 20);
  tft.println("Leitura: ");
  tft.setCursor(LEITX, LEITY);
  tft.println(sens.getLeit());

  tft.setCursor(MAXX, MAXY - 20);
  tft.println("Max: ");
  tft.setCursor(MAXX, MAXY);
  tft.println(sens.getMax());

  tft.setCursor(MINX, MINY - 20);
  tft.println("Min: ");
  tft.setCursor(MINX, MINY);
  tft.println(sens.getMin());

  tft.setCursor(MEDX, MEDY - 20);
  tft.println("Med: ");
  tft.setCursor(MEDX, MEDY);
  tft.println(sens.getMed());
}

void grafico() {
  int j = 0;
  tft.fillRect(GRAXm, GRAYm, GRAXM - GRAXm, GRAYM - GRAYm, WHITE);
  tft.drawFastHLine(GRAXm, GRAYM, GRAXM - GRAXm, BLACK);
  tft.drawFastVLine(GRAXm, GRAYm, GRAYM - GRAYm, BLACK);

  for (int i = sens.getLV() - 6; i < sens.getLV(); i++) {
    if (i >= 0) {
      j++;
      int a = sens.getVet(i);
      tft.fillRect(GRAXm + 20 * j, GRAYM - a, 10, a, RED);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.setCursor((int)((GRAXm + 20 * j)), GRAYM + 5);
      tft.println(j);
      tft.setCursor((int)((GRAXm + 20 * j)), GRAYm + 5);
      tft.println(a);
    }
  }
}

void setup()
{
  Serial.begin(9600);         // Inicializa o serial

  tft.reset();                // Inicializacao da parte grafica
  tft.begin(0x9341);
  tft.fillScreen(WHITE);      // Preenche a tela com preto
  tft.setRotation(3);         // Rotacao do tela
  
  rate = millis() / 1000;
}

void loop()
{
  //pinMode(XM, OUTPUT);
  //digitalWrite(XM, LOW);
  //pinMode(YP, OUTPUT);
  //digitalWrite(YP, HIGH);
  //pinMode(YM, OUTPUT);
  //digitalWrite(YM, LOW);
  //pinMode(XP, OUTPUT);
  //digitalWrite(XP, HIGH);

  static Clock clock = Clock();  // Faz a leitura de tempo atual

  tft.drawRGBBitmap(160, 10, myBitmap, 75, 42);
  drawTime(clock);     // Desenha o novo horario na tela
  if ((millis() / 1000) - rate >= sens.rateget()) {
    drawSomething();
    grafico();
    rate = millis() / 1000;
  }
}
