// Serial Led
// Utilizando o Serial, é possível acender/desligar o led (porta 13) do Arduíno

#define led 13

void setup() {
  // Coloque seu setup aqui, roda somente uma vez...
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  // coloque seu código principal aqui, roda eternamente...
  if ( Serial.available() ) {  
    char c = Serial.read();
    if ( c == '1' ){
      digitalWrite(led,HIGH);
    } else if ( c == '0'){
      digitalWrite(led,LOW);   
    }
  }
}
