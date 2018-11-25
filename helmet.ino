#include<Servo.h>

int buzzer = 11;

int flame = A0;

Servo helmet;

void setup() {
  // put your setup code here, to run once:

  helmet.attach(7);
  helmet.write(0);
  pinMode(flame, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  int sensor_value = digitalRead(flame);
  switch (sensor_value)
  {
    case LOW:
      digitalWrite(buzzer, HIGH);
      Serial.print("Fire\n");
      Serial.print("Buzzing\n");
      helmet.write(60);
      delay(1000);
      digitalWrite(buzzer, LOW);
      Serial.print("Buzzing off\n");
      break;

    case HIGH:

      helmet.write(0);
      break;

  }

}
