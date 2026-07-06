#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Definição dos pinos
#define PIN_SDA 25
#define PIN_SCL 33
#define in1 4
#define in2 5
#define in3 18
#define in4 19

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Wire.begin(PIN_SDA, PIN_SCL);

  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar o chip MPU6050 nos pinos 25 e 33");
    while (1) { delay(10); }
  }

  Serial.println("MPU6050 iniciado com sucesso!");

  // MODIFICAÇÃO 1: Aumenta a sensibilidade física do sensor para o valor máximo (2G)
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  
  // Mantém o filtro de ruído para evitar leituras falsas causadas pela vibração dos motores
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calcula os ângulos de inclinação em graus
  float anguloX = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;
  float anguloY = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;

  // Exibe os valores no Monitor Serial
  Serial.print("Inclinacao X: ");
  Serial.print(anguloX);
  Serial.print(" | Inclinacao Y: ");
  Serial.println(anguloY);

  // MODIFICAÇÃO 2: Nova janela baseada na média dos logs (X centralizado em -0.30 e Y em 2.80)
  // Margem de tolerância aplicada: ± 0.50 graus
  if (anguloX >= -0.80 && anguloX <= 0.20 && anguloY >= 2.30 && anguloY <= 3.30) {
    Serial.println("-> TERRENO NIVELADO! Parando motores.");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else {
    Serial.println("-> Terreno inclinado. Ativando motores.");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  delay(500); 
}
