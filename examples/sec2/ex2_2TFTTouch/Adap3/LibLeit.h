#ifndef __LIBLEIT_H
#define __LIBLEIT_H

#include "DHT.h"
#include "Ultrasonic.h"
#include "Arduino.h"

class Sensor {
  private:
    int sens, timerate, lastvet, hora, minuto, segundo, n_desc;
    long int timenow;
    double vet[50];
    bool min, max, med, dro;
    double h, cm, x, t, minimo, maximo, media, evento, eventomax;
    Ultrasonic *ultrasonic;
    DHT *dht;

  public:
    Sensor(String sen);
    ~Sensor();
    int getsens();
    void vetdef(String sen);
    void sample();
    void SensorRead();
    void vetInc(double x);
    void mini(String onoff, int event = -1);
    void maxi(String onoff, int event = -1);
    void medi(String onoff);
    void drop(String onoff, int desc = 0);
    void rateset(int rate);
    int rateget();
    String getMin();
    String getMax();
    String getMed();
    String getLeit();
    int getSens();
    int getLV();
    int getVet(int);
};

Sensor::Sensor(String sen) {
  pinMode(13, OUTPUT);
  timenow = millis() / 1000;
  lastvet = 0;
  dro = 0;
  evento = eventomax = -1;
  min = max = med = true;
  h = cm = x = t = sens = 0;
  for (int i = 0; i < 50; i++)
    vet[i] = 0;
  hora = minuto = segundo = -1;
  media = 0;
  minimo = 30000;
  maximo = -30000;
  timerate = 2;
  vetdef(sen);
}
Sensor::~Sensor() {
  delete []ultrasonic;
  delete []dht;
}
int Sensor::getsens() {
  return sens;
}
void Sensor::vetInc(double x) {
  if (lastvet < 50) {
    vet[lastvet] = x;
    lastvet++;
  }
  else {
    for (int i = 0; i < 49; i++) {
      vet[i] = vet[i + 1];
    }
    vet[49] = x;
  }
  return;
}
void Sensor::vetdef(String sen) {
  if (sen == "DHT") {
    dht = new DHT(12, 22);
    sens = 1;
  }
  else if (sen == "Sonic") {
    ultrasonic = new Ultrasonic(11, 12);
    sens = 2;
  }
  else if (sen == "LDR") {
    pinMode(0, INPUT);
    sens = 3;
  }
}
void Sensor::SensorRead() {
  switch (sens) {
    case 1:
      h = dht->readHumidity();
      t = dht->readTemperature();
      //t += 1;
      //h = 88;
      if (min) {
        if (t < minimo) minimo = t;
        Serial.println(t);
      }
      if (max) {
        if (t > maximo) maximo = t;
        Serial.println(t);
      }
      vetInc(t);
      break;
    case 2:
      cm = ultrasonic->Ranging(CM);
      if (min) {
        if (cm < minimo) minimo = cm;
      }
      if (max) {
        if (cm > maximo) maximo = cm;
      }
      vetInc(cm);
      break;
    case 3:
      x = map(analogRead(0), 0, 1023, 0, 5);
      if (min) {
        if (x < minimo) minimo = x;
      }
      if (max) {
        if (x > maximo) maximo = x;
      }
      vetInc(x);
      break;
    default:
      Serial.println("Sem sensor");
      break;
  }
}
void Sensor::mini(String onoff, int event = -1) {
  int value;
  if (onoff == "ON") value = 1;
  else if (onoff == "OFF") value = 2;
  else if (onoff == "PRINT") value = 3;
  else if (onoff == "EVENT") value = 4;
  switch (value) {
    case 1:
      min = true;
      break;
    case 2:
      min = false;
      break;
    case 3:
      if (min) {
        switch (sens) {
          case 1:
            Serial.println("Temperatura minima: ");
            Serial.println(minimo);
            break;
          case 2:
            Serial.println("Altitude minima: ");
            Serial.println(minimo);
            break;
          case 3:
            Serial.println("Luminosidade minima: ");
            Serial.println(minimo);
            break;
        }
      }
      break;
    case 4:
      min = true;
      if (event != -1) evento = event;
  }
}
void Sensor::maxi(String onoff, int event = -1) {
  int value;
  if (onoff == "ON") value = 1;
  else if (onoff == "OFF") value = 2;
  else if (onoff == "PRINT") value = 3;
  else if (onoff == "EVENT") value = 4;
  switch (value) {
    case 1:
      max = true;
      break;
    case 2:
      max = false;
      break;
    case 3:
      if (max) {
        switch (sens) {
          case 1:
            Serial.println("Temperatura maxima: ");
            Serial.println(maximo);
            break;
          case 2:
            Serial.println("Altitude maxima: ");
            Serial.println(maximo);
            break;
          case 3:
            Serial.println("Luminosidade maxima: ");
            Serial.println(maximo);
            break;
        }
      }
      break;
    case 4:
      max = true;
      if (event != -1) eventomax = event;
  }
}
void Sensor::medi(String onoff) {
  int value;
  if (onoff == "ON") value = 1;
  else if (onoff == "OFF") value = 2;
  else if (onoff == "PRINT") value = 3;
  switch (value) {
    case 1:
      med = true;
      break;
    case 2:
      med = false;
      break;
    case 3:
      if (dro) {
        drop("REF");
      }
      if (med) {
        switch (sens) {
          case 1:
            media = 0;
            for (int i = 0; i < lastvet; i++) {
              media += vet[i];
            }
            media /= lastvet;
            Serial.println("Temperatura media: ");
            Serial.println(media);
            break;
          case 2:
            media = 0;
            for (int i = 0; i < lastvet; i++) {
              media += vet[i];
            }
            media /= lastvet;
            Serial.println("Altitude media: ");
            Serial.println(media);
            break;
          case 3:
            media = 0;
            for (int i = 0; i < lastvet; i++) {
              media += vet[i];
            }
            media /= lastvet;
            Serial.println("Luminosidade media: ");
            Serial.println(media);
            break;
        }
      }
      break;
  }
}
void Sensor::rateset(int rate) {
  timerate = rate;
}
int Sensor::rateget() {
  return timerate;
}
void Sensor::sample() {
  Serial.println("Vetor Sample: ");
  for (int i = 0, j = 0; i < lastvet && j < 20; i++, j++) {
    Serial.print(vet[i]);
    if (i < lastvet - 1 && j < 19)
      Serial.print(", ");
  }
}
void Sensor::drop(String onoff, int desc = 0) {
  int value;
  if (onoff == "ON") value = 1;
  else if (onoff == "OFF") value = 2;
  else if (onoff == "SET") value = 3;
  else if (onoff == "REF") value = 4;
  switch (value) {
    case 1:
      dro = 1;
      break;
    case 2:
      dro = 0;
      break;
    case 3:
      n_desc = desc;
      dro = 1;
      break;
    case 4:
      if (n_desc > lastvet)
        break;
      double vetaux[lastvet];
      for (int i = 0; i < lastvet; i++)
        vetaux[i] = vet[i];
      for (int i = 0; i < lastvet; i++) {
        for (int j = i; j < lastvet - 1; j++) {
          if (vetaux[i] > vetaux[j + 1]) {
            double aux;
            aux = vetaux[j + 1];
            vetaux[j + 1] = vetaux[i];
            vetaux[i] = aux;
          }
        }
      }
      double vetn[n_desc];
      for (int i = 0, j = 0; i < lastvet && j < n_desc; i++, j++) {
        if (j % 2 == 0) {
          vetn[j] = vetaux[j / 2];
        }
        else {
          vetn[j] = vetaux[lastvet - (j / 2) - 1];
        }
      }
      for (int j = 0; j < n_desc; j++) {
        for (int i = 0; i < lastvet; i++) {
          if (vetn[j] == vet[i]) {
            vet[i] = -274 - j;
            break;
          }
        }
      }
      for (int j = 0; j < n_desc; j++) {
        for (int i = 0; i < lastvet - 1; i++) {
          if (vet[i] == -274 - j) {
            vet[i] = vet[i + 1];
            vet[i + 1] = -274 - j;
          }
        }
      }
      lastvet -= n_desc;
      break;
  }
}
String Sensor::getMin() {
  String a = "";
  a += minimo;
  return a;
}
String Sensor::getMax() {
  String a = "";
  a += maximo;
  return a;
}
String Sensor::getMed() {
  medi("PRINT");
  String a = "";
  a += media;
  return a;
}
String Sensor::getLeit() {
  String a = "";
  switch (sens) {
    case 1:
      a += h;
      a += " ";
      a += t;
      break;
    case 2:
      a += cm;
      break;
    case 3:
      a += x;
      break;
    default:
      a += "NaN";
      break;
  }
  return a;
}

int Sensor::getSens() {
  return sens;
}

int Sensor::getLV() {
  return lastvet;
}
int Sensor::getVet(int x) {
  if (x <= lastvet && x >= 0)
    return vet[x];
  return -1;
}

#endif
