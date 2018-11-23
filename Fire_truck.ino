#include<Servo.h>

Servo bottom;
Servo base;
Servo hand;

const int flamepin_left = A15;
const int flamepin_middle = A14;
const int flamepin_right = A13;

int water = 8;


int trigPin = 22;
int echoPin = 23;

int buzzer = 11;


int Motor_A_Enable = 2;
int Motor_A_Reverse = 4;
int Motor_A_Forward = 5;

int Motor_B_Enable = 3;
int Motor_B_Reverse = 7;
int Motor_B_Forward = 6;


int flame_value_left = 1;
int flame_value_middle = 1;
int flame_value_right = 1;


void setup() {

  Serial.begin(9600);

  bottom.attach(26);
  bottom.write(130);
  base.attach(25);
  base.write(160);
  hand.attach(52);
  hand.write(180);

  pinMode(Motor_A_Enable, OUTPUT);
  pinMode(Motor_A_Forward, OUTPUT);
  pinMode(Motor_A_Reverse, OUTPUT);

  pinMode(Motor_B_Enable, OUTPUT);
  pinMode(Motor_B_Forward, OUTPUT);
  pinMode(Motor_B_Reverse, OUTPUT);

  pinMode(flamepin_left, INPUT);
  pinMode(flamepin_right, INPUT);
  pinMode(flamepin_middle, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(water, OUTPUT);

}
void loop() {

  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  delay(10);

  if ((distance <= 15))
  {
    Serial.print("Obstacle ");
    //    Serial.print(distance);
    //    Serial.print("\n");
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }


  if (Serial.available() > 0)
  {
    char data;
    data = Serial.read();

    switch (data)
    {
      case 'F':

        analogWrite(Motor_B_Enable, 150);
        analogWrite(Motor_A_Enable, 150);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Forward, HIGH);
        Serial.print("Forward\n");
        break;

      case 'L':
        analogWrite(Motor_B_Enable, 150);
        analogWrite(Motor_A_Enable, 150);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_B_Forward, HIGH);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_A_Forward, LOW);
        Serial.print("left\n");
        break;


      case 'R':
        analogWrite(Motor_A_Enable, 150);
        analogWrite(Motor_B_Enable, 150);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Reverse, HIGH);
        digitalWrite(Motor_B_Forward, LOW);
        Serial.print("Right\n");
        break;

      case 'B':
        Serial.print("Reverse\n");
        analogWrite(Motor_B_Enable, 100);
        analogWrite(Motor_A_Enable, 1000);
        digitalWrite(Motor_A_Forward, LOW);
        digitalWrite(Motor_B_Forward, LOW);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_B_Reverse, HIGH);
        break;


      case 'V':
        fire();
        break;

      case 'w':
        base.write(160);
        break;

      case 'W':
        base.write(70);
        break;

      case 'U':
        hand.write(0);
        break;

      case 'u':
        hand.write(160);
        break;


      case '1':
        bottom.write(180);
        break;

      case '2':
        bottom.write(160);
        break;

      case '3':
        bottom.write(140);
        break;

      case '4':
        bottom.write(120);
        break;

      case '5':
        bottom.write(100);
        break;

      case '6':
        bottom.write(80);
        break;

      case '7':
        bottom.write(60);
        break;

      case '8':
        bottom.write(40);
        break;

      case '9':
        bottom.write(200);
        break;


        default:
        analogWrite(Motor_A_Enable, 0);
        analogWrite(Motor_B_Enable, 0);
        break;
        



    }

  }





}


int fire()
{

  while (1)
  {
    if (Serial.available() > 0)
    {
      char data;
      data = Serial.read();

      if (data == 'v')
      {
        return (0);
      }

    }

    else {




      long duration, distance;
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;
      delay(10);

      if ((distance <= 15))
      {
        Serial.print("Obstacle ");
        //    Serial.print(distance);
        //    Serial.print("\n");
        digitalWrite(buzzer, HIGH);
        analogWrite(Motor_B_Enable, 0);
        analogWrite(Motor_A_Enable, 0);
      }
      else if (distance > 10)
      {
        digitalWrite(buzzer, LOW);
      }
      flame_value_left = digitalRead(flamepin_left); // reads digital data from flame sensor
      Serial.print(flame_value_left);
      Serial.print("\t");
      Serial.print(flame_value_middle);
      Serial.print("\t");
      Serial.print(flame_value_right);
      Serial.print("\n");

      flame_value_middle = digitalRead(flamepin_middle); // reads digital data from flame sensor
      flame_value_right = digitalRead(flamepin_right); // reads digital data from flame sensor

      if (flame_value_left == LOW && flame_value_middle == HIGH && flame_value_right == HIGH) //left
      {
        digitalWrite(water, LOW);

        if ((distance <= 10))
        {
          Serial.print("Obstacle ");
          //    Serial.print(distance);
          //    Serial.print("\n");
          digitalWrite(buzzer, HIGH);
          analogWrite(Motor_B_Enable, 0);
          analogWrite(Motor_A_Enable, 0);
        }

        analogWrite(Motor_B_Enable, 150);
        analogWrite(Motor_A_Enable, 150);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_B_Forward, HIGH);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_A_Forward, LOW);
        Serial.print("left\n");
      }

      else if (flame_value_left == HIGH && flame_value_middle == LOW && flame_value_right == HIGH) // forward
      {
        digitalWrite(water, LOW);
        if ((distance <= 10))
        {
          Serial.print("Obstacle ");
          //    Serial.print(distance);
          //    Serial.print("\n");
          digitalWrite(buzzer, HIGH);
          analogWrite(Motor_B_Enable, 0);
          analogWrite(Motor_A_Enable, 0);
        }
        analogWrite(Motor_B_Enable, 150);
        analogWrite(Motor_A_Enable, 150);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Forward, HIGH);
        Serial.print("Forward\n");
      }

      else if (flame_value_left == HIGH && flame_value_middle == HIGH && flame_value_right == LOW) //right
      {
        digitalWrite(water, LOW);
        if ((distance <= 10))
        {
          Serial.print("Obstacle ");
          //    Serial.print(distance);
          //    Serial.print("\n");
          digitalWrite(buzzer, HIGH);
          analogWrite(Motor_B_Enable, 0);
          analogWrite(Motor_A_Enable, 0);
        }
        analogWrite(Motor_A_Enable, 150);
        analogWrite(Motor_B_Enable, 150);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Reverse, HIGH);
        digitalWrite(Motor_B_Forward, LOW);
        Serial.print("Right\n");
      }

      else if ((flame_value_left == LOW && flame_value_middle == LOW && flame_value_right == LOW) || (flame_value_left == LOW && flame_value_middle == LOW && flame_value_right == HIGH) || (flame_value_left == HIGH && flame_value_middle == LOW && flame_value_right == LOW))
      {
        analogWrite(Motor_A_Enable, 0);
        analogWrite(Motor_B_Enable, 0);
      }

      else if (flame_value_left == HIGH && flame_value_middle == HIGH && flame_value_right == HIGH)
      {
        analogWrite(Motor_A_Enable, 0);
        analogWrite(Motor_B_Enable, 0);
        digitalWrite(water, HIGH);
      }

    }

  }



}
