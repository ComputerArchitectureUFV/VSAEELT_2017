
#define led 13

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( Serial.available() ) {  
    char c = Serial.read();
    if ( c == '1' ) digitalWrite(led,HIGH);
    else if ( c == '0') digitalWrite(led,LOW);
  }
}
