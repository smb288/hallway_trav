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
int distance1, distance2, distance3; // variable for the distance measurement
int m1Speed = 100;
int m2Speed = 100;

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
  // Clears the trigPin condition
  int motor1Speed = map(m1Speed, 0, 1023, 0, 255);
  int motor2Speed = map(m2Speed, 0, 1023, 0, 255);
  distance1 = pulseUltra(echoPin1, trigPin1);
  distance2 = pulseUltra(echoPin2, trigPin2);
  distance3 = pulseUltra(echoPin3, trigPin3);
  // Displays the distance on the Serial Monitor
  /*Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm");
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.print(" cm");
  Serial.print(" Distance3: ");
  Serial.print(distance3);
  Serial.println(" cm");*/
  if(distance1 > 30) {
    analogWrite(Motor1, motor1Speed);
    analogWrite(Motor2, 0);
    analogWrite(Motor3, 0);
    analogWrite(Motor4, motor2Speed);
  }
  else {
    digitalWrite(Motor1, 0);
    digitalWrite(Motor2, 0);
    digitalWrite(Motor3, 0);
    digitalWrite(Motor4, 0);
  }
  delay(1);
}