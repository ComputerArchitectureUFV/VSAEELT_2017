// Código Receiver (recebe)

#include <SPI.h>  
#include "RF24.h" 
RF24 myRadio (9, 10);

struct package{
  int id=0;
  float temperature = 0.0;
  char  text[100] ="empty";
};
byte addresses[][6] = {"0"}; 

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Receiver");
  myRadio.begin(); 
  // Note que o Canal do Receiver e Transmitter devem ser iguais  
  myRadio.setChannel(115); // Mudar o Canal para evitar conflito (0-127)
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop() {

  if (myRadio.available()) {
    while (myRadio.available()){
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
  }

}
