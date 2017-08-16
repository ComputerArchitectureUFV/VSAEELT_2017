/**
 * Exemplo básico para HC-12
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //RX, TX

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  
  if(Serial.available() > 0){ // ler a partir do serial monitor envia para o HC-12
    String input = Serial.readString();
    mySerial.println(input);
    Serial.print("Voce enviou: ");
    Serial.println(input);    
  }
 
  if(mySerial.available() > 0){ // ler a partir do HC-12 and envia para o serial monitor
    
    Serial.print("Voce recebeu: ");
    String input = mySerial.readString();
    Serial.println(input);    
  }
  delay(20);
}
