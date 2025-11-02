#include <Arduino.h>

int botao1 = 3;
int botao2 = 4;
int rele = 2;

void setup() {
  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  pinMode(rele, OUTPUT);
  Serial.begin(9600); // inicia o monitor serial
}

void loop() {
  int estado = digitalRead(botao1);
  int estado = digitalRead(botao2);
  if (estado == LOW) {
    Serial.println("Botão pressionado!");
    digitalWrite(rele, HIGH);
  } else {
    Serial.println("Botão solto.");
  }
  delay(1000);
}