//Bibliotecas
#include <Adafruit_GFX.h>    // Biblioteca grafica
#include <Adafruit_TFTLCD.h> // Biblioteca especifica para o hardware
#include <TouchScreen.h>     // Biblioteca para a parte touch screen  
#include "Clock.h"           // Classe relogio   

#define YP A3 // Y+ is on Analog1
#define XM A2 // X- is on Analog2
#define YM 9  // Y- is on Digital7
#define XP 8  // X+ is on Digital6

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

//Inicializacao de pinos utilizados pela parte de touchscreen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);

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
    //-----MODIFIQUE ESSA FUNCAO PARA A ATUALIZACAO DO TEMPO NA TELA--------------//
    // cor do texto 
    tft.setTextColor(BLACK);
    tft.setTextSize(5);
    tft.setCursor(30, 100);
    Time t = clock.getTime();
    
    clock.update();               // Atualiza o relogio
    if(!(t == clock.getTime())){ 
      tft.println(t.toString());
      tft.setTextColor(WHITE);
      // tamanho do texto
      tft.setTextSize(5);
      // setCursor(offset_x, offset_y)
      // cursor da tela e colocado em posicao para escrita
      tft.setCursor(30, 100);
      // o novo horario e impresso 
      tft.println((clock.getTime()).toString());
    }
}

void drawMenu()
{
    tft.drawRoundRect(0, 195, 320, 45, 0, WHITE);
    tft.setTextSize(3);         // Font width is 15px with this size (I counted)
    //tft.setCursor(py, px);
    tft.setCursor(70, 205);
    tft.println("MENU TOUCH");    
}

void setup()
{
    Serial.begin(9600);         // Inicializa o serial

    tft.reset();                // Inicializacao da parte grafica
    tft.begin(0x9341);
    tft.fillScreen(BLACK);      // Preenche a tela com preto
    tft.setRotation(3);         // Rotacao do tela

    // drawRoundRect(posicao x, posicao y, largura, altura, raio, cor)

    // Desenha os blocos para o horario no meio da tela
    tft.drawRoundRect(20, 95, 75, 45, 5, WHITE);
    tft.drawRoundRect(110, 95, 75, 45, 5, WHITE);
    tft.drawRoundRect(200, 95, 75, 45, 5, WHITE);

    // Desenha o menu
    drawMenu();
}

void loop()
{
    //Inicializa os pinos analogicos utilizados (necessario colocar 
    //no loop para a parte de touch screen)
    pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    digitalWrite(YM, LOW);
    pinMode(XP, OUTPUT);
    digitalWrite(XP, HIGH);
    
    static Clock clock = Clock();  // Faz a leitura de tempo atual
                              
    drawTime(clock);     // Desenha o novo horario na tela
}//loop
