#include <Keyboard.h>

int sensor = A0;
int sensor2 = A1;
int valor;
int valor2;
int stopButton = 13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(sensor, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(stopButton, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  valor = analogRead(sensor);
  valor2 = analogRead(sensor2);
  Serial.print("sensor: ");
  Serial.println(valor);
  Serial.print("sensor 2: ");
  Serial.println(valor2);
  //mapped1 = map(valor, 0, 1023, 0, 255);
  //mapped2 = map(valor2, 0, 1023, 0, 255);
  if (digitalRead(stopButton) == LOW) {
    if(valor > 10){
    Keyboard.write(' ');
    delay(10);
    }
    if(valor2 > 10){
      Keyboard.write('d');
      delay(100);
    }
  }  
  delay(50);
}
