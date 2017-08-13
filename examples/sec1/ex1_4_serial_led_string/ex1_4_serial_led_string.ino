
#define led 13

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( Serial.available() ) {  
    String c = Serial.readString();
    if ( c == "ON" ) digitalWrite(led,HIGH);
    else if ( c == "OFF") digitalWrite(led,LOW);
  }
}
