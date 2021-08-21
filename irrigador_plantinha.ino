// C++ code
//
#include <Servo.h>

Servo servo9;

int buzzer = 2;
int amarelo = 4;
int verde = 3;
float umidade = A0;
float sinalUMD = 0; //variável que lê o valor do sensor

void setup ()
{
  Serial.begin(9600);
  servo9.attach(9);
  pinMode (buzzer, OUTPUT); //Adicionando o buzzer como saída
  pinMode (amarelo, OUTPUT); //Adicionando LED amarelo como saída
  pinMode (verde, OUTPUT); //Adicionando LED verde como saída
  pinMode (umidade, INPUT); //Adicionando o sensor como entrada 
}

void loop ()
{
  sinalUMD = analogRead (umidade);
  
  //Transformar o valor analógico recebido em porcentagem
  	sinalUMD = map(sinalUMD, 1023, 0, 0, 100);
  
  	Serial.print("sinalUMD(%): ");
    Serial.println(sinalUMD);
  
  if (sinalUMD>60)
  {
    Serial.println(" Status: Solo umido");
    servo9.write (0);
    digitalWrite (buzzer, LOW);
    digitalWrite (amarelo, LOW);
    digitalWrite (verde, HIGH);
  }
  else
  {
    Serial.println(" Status: Solo seco. Irrigando...");
    servo9.write (180);
    digitalWrite (buzzer, HIGH);
    digitalWrite (amarelo, HIGH);
    digitalWrite (verde, LOW);
    delay (1000);
  }  
}
