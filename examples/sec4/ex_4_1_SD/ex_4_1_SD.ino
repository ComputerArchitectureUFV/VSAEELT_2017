#include <SD.h>
File myFile;
void setup() {
  // Abre a comunicacao serial:
  Serial.begin(9600);
  while (!Serial){; //espera o serial comunicar, necessario apenas no Leonardo}
  Serial.print("Initializing SD card...");
  // No Shield Ethernet, CS é o pino 4. É definido
  // Como saída por padrão.
  // Observe que, mesmo se ele não for usado como o pino CS, o
  // Pino SS do hardware
  // (10 na maioria das placas Arduino, 53 na mega) deve ser
  // Deixado como uma saída
  // Ou as funções da biblioteca SD não vao funcionar.
  comandosSD();
}

void loop () { 
  
}

void comandosSD(){
  
  if (!SD.begin(4)){
    Serial.println("inicializacao falhou!");
    return;
  }
  Serial.println("inicializacao completa!");

  //verificando se o arquivo existe
  if (SD.exists("exemplo.txt")){
    Serial.println("exemplo.txt existe.");
  } else {
    Serial.println("exemplo.txt nao existe.");
  }
  Serial.println("Criando exemplo.txt...");
  // abre um novo arquivo e fecha ele em seguida:
  myFile = SD.open("exemplo.txt", FILE_WRITE);
  myFile.close();
}
