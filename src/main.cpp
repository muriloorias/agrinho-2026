#include <Arduino.h>
// Definição dos pinos do Sensor Ultrassônico
const int trigPin = 12;
const int echoPin = 13;

// Definição dos pinos - Motor 1 (Ajustados)
const int IN1 = 4;
const int IN2 = 5;

// Definição dos pinos - Motor 2 (Ajustados)
const int IN3 = 18;
const int IN4 = 19;

long duracao;
int distancia;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configuração dos pinos do sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(115200); 
}

void loop() {
  // Disparo do sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Cálculo da distância
  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;

  // Exibe a distância no Monitor Serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Lógica de controle: Gira motores se objeto estiver a menos de 20cm
  if (distancia > 0 && distancia < 20) { 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  delay(200); 
}
