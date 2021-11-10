#include <Arduino.h>

#define echoPin1 0 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 1 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 2
#define trigPin2 3
#define echoPin3 4
#define trigPin3 5
#define Motor1 16
#define Motor2 17
#define Motor3 18
#define Motor4 19
#define LED 25


long duration; // variable for the duration of sound wave travel
int distanceM, distanceL, distanceR; // variable for the distance measurement
int m1Speed = 250;
int m2Speed = 255;

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT);
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(Motor3, OUTPUT);
  pinMode(Motor4, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  
}
int pulseUltra(int echo, int trig) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return distance;
}
void loop() {
  int motor1Speed = map(m1Speed, 0, 1023, 0, 255);
  int motor2Speed = map(m2Speed, 0, 1023, 0, 255);
  distanceM = pulseUltra(echoPin1, trigPin1);
  distanceL = pulseUltra(echoPin2, trigPin2);
  distanceR = pulseUltra(echoPin3, trigPin3);
  // Displays the distance on the Serial Monitor
  /*Serial.print("DistanceL: ");
  Serial.print(distanceL);
  Serial.print(" cm");
  Serial.print("\tDistanceM: ");
  Serial.print(distanceM);
  Serial.print(" cm");
  Serial.print("\tDistanceR: ");
  Serial.print(distanceR);
  Serial.println(" cm");*/
  if(distanceM > 30) {
    analogWrite(Motor1, motor1Speed);
    analogWrite(Motor2, 0);
    analogWrite(Motor3, 0);
    analogWrite(Motor4, motor2Speed);
  }
  else if(distanceL > distanceR) {
    analogWrite(Motor1, 0);
    analogWrite(Motor2, 0);
    analogWrite(Motor3, 0);
    analogWrite(Motor4, motor1Speed);
    delay(100);
  }
  else if(distanceL < distanceR) {
    analogWrite(Motor1, motor1Speed);
    analogWrite(Motor2, 0);
    analogWrite(Motor3, 0);
    analogWrite(Motor4, 0);
    delay(100);
  }
  delay(1);
}