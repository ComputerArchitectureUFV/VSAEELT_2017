#include <LiquidCrystal.h>

// Programa : Teste LCD 16x2 com Keypad
// Autor : Arduino e Cia
  

  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  
  
void setup()   
{  
 lcd.begin(16, 2);  
 lcd.clear();
 lcd.setCursor(0,0);  
 lcd.write(0xFF);  
}  
  int posH=0, posV=0;
  
void loop()  
{  
 int botao;  
 botao = analogRead (0);  //Leitura do valor da porta analógica A0
 if (botao < 100) {  
   lcd.clear();
   posH++;
   lcd.setCursor(posH,posV);
   lcd.write(0xFF);
   delay(500);
 }  
 else if (botao < 200) {  
  lcd.clear();
   posV--;
   lcd.setCursor(posH,posV);
   lcd.write(0xFF);
   delay(500);  
 }  
 else if (botao < 400){  
  lcd.clear();
   posV++;
   lcd.setCursor(posH,posV);
   lcd.write(0xFF);
   delay(500);  
 }  
 else if (botao < 600){  
  lcd.clear();
   posH--;
   lcd.setCursor(posH,posV);
   lcd.write(0xFF);
   delay(500);  
 }  
 else if (botao < 800){  
  lcd.clear();
   posH=0;
   posV=0;
   lcd.setCursor(posH,posV);
   lcd.write(0xFF);
   delay(500);  
 }
   
}
