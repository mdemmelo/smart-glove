#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Inicializa o sensor
  byte status = mpu.begin();
  Serial.print("Status do MPU6050: ");
  Serial.println(status);
  
  // Se o status for diferente de 0, significa que há um erro de conexão
  while(status != 0){ } 
  
  Serial.println("Calibrando o sensor... DEIXE O MPU6050 PARADO NA HORIZONTAL");
  delay(2000);
  mpu.calcOffsets(); // Calcula o zero do sensor para evitar desvios de leitura
  Serial.println("Calibracao concluida!\n");
}

void loop() {
  mpu.update(); // CRUCIAL: Atualiza os cálculos internos do sensor
  
  // Lê apenas os ângulos X e Y
  float x = mpu.getAngleX();
  float y = mpu.getAngleY();
  
  // Exibe no Monitor Serial
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" \t Y: ");
  Serial.println(y);
  
  delay(50); // Pequena pausa para facilitar a leitura no monitor
}