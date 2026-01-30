    #include <Arduino.h>

//Definição dos pinos do semáforo
int vermelho=7;
int amarelo=4;
int verde=2;

void setup()
{
  //Inicialozação da comunicação serial e configuração dos pinos
  Serial.begin(9600);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);  
  pinMode(verde, OUTPUT);

}

void loop()
{
  //Sequencia do semáforo
  
    digitalWrite(vermelho,HIGH);
    digitalWrite(amarelo,LOW);
    digitalWrite(verde,LOW);
    Serial.println("Vermelho Ligado");
    delay(10000); //Vermelho por 10 segundos

    digitalWrite(vermelho,LOW);
    digitalWrite(amarelo,HIGH);
    digitalWrite(verde,LOW); 
    Serial.println("Amarelo Ligado");
    delay(10000); //Amarelo por 10 segundos

    digitalWrite(vermelho,LOW);
    digitalWrite(amarelo,LOW);
    digitalWrite(verde,HIGH);
    Serial.println("Verde Ligado");
    delay(10000); //Verde por 10 segundos

   
}


