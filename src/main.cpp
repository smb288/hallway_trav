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
// defines variables
long duration; // variable for the duration of sound wave travel
int distance1, distance2, distance3; // variable for the distance measurement

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
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
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
    digitalWrite(Motor1, 1);
    digitalWrite(Motor2, 0);
    digitalWrite(Motor3, 0);
    digitalWrite(Motor4, 1);
  }
  else {
    digitalWrite(Motor1, 0);
    digitalWrite(Motor2, 0);
    digitalWrite(Motor3, 0);
    digitalWrite(Motor4, 0);
  }
  delay(1);
}