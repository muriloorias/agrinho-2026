#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Definição dos pinos escolhidos por você
#define PIN_SDA 25
#define PIN_SCL 33

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);

  // Inicializa o barramento I2C com os seus pinos customizados
  Wire.begin(PIN_SDA, PIN_SCL);

  // Inicializa o sensor MPU6050 usando a configuração I2C criada acima
  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar o chip MPU6050 nos pinos 25 e 33");
    while (1) { delay(10); }
  }

  Serial.println("MPU6050 iniciado com sucesso!");

  // Configurações de estabilidade do sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
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

  // Nova lógica com a sua janela personalizada de calibração/nivelamento
  if (anguloX >= 1.47 && anguloX <= 1.71 && anguloY >= 1.73 && anguloY <= 2.00) {
    Serial.println("-> TERRENO NIVELADO!");
  } else {
    Serial.println("-> Terreno inclinado.");
  }

  delay(500); 
}
