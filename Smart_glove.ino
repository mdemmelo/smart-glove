#include <Wire.h>
#include <MPU6050_light.h>
#include <Keyboard.h>

MPU6050 mpu(Wire);

int flex01 = A0;
int flex02 = A1;
int valor01;
int valor02;
int stopButton = 13;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Keyboard.begin();
  pinMode(flex01, INPUT);
  pinMode(flex02, INPUT);
  pinMode(stopButton, INPUT);

  byte status = mpu.begin();
  Serial.print("Status do MPU6050: ");
  Serial.println(status);

  while (status != 0) { }

  Serial.println("Calibrando o sensor... DEIXE O MPU6050 PARADO NA HORIZONTAL");
  delay(2000);
  mpu.calcOffsets();
  Serial.println("Calibracao concluida!\n");
}

void loop() {
  mpu.update();

  float x = mpu.getAngleX();
  float y = mpu.getAngleY();

  valor01 = analogRead(flex01);
  valor02 = analogRead(flex02);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" \t Y: ");
  Serial.print(y);
  Serial.print(" \t Flex1: ");
  Serial.print(valor01);
  Serial.print(" \t Flex2: ");
  Serial.println(valor02);

  // --- Código para os sensores de pressão ---
  if (digitalRead(stopButton) == LOW) {

    if (valor01 > 10) {
      Keyboard.write(' ');
      delay(10);
    }
    if (valor02 > 10) {
      Keyboard.write('d');
      delay(100);
    }

    // --- MPU6050 - Eixo X (inclinação para frente/trás) ---
    if (x > 30) {
      Keyboard.write('w'); // inclinado para frente → pressiona W
      delay(100);
    }
    if (x < -30) {
      Keyboard.write('s'); // inclinado para trás → pressiona S
      delay(100);
    }

    // --- MPU6050 - Eixo Y (inclinação para esquerda/direita) ---
    if (y > 30) {
      Keyboard.write('a');   // inclinado para direita → pressiona A
      delay(100);
    }
    if (y < -30) {
      Keyboard.write('d');   // inclinado para esquerda → pressiona D
      delay(100);
    }
}
