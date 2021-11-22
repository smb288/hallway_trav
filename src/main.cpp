#include <Arduino.h>

#define echoPin1 0 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 1 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 2
#define trigPin2 3
#define echoPin3 4
#define trigPin3 5
#define IRFrontCenter 6
#define IRBackCenter 7
#define IRFrontLeft 8
#define IRFrontRight 9
#define Motor1 16
#define Motor2 17
#define Motor3 18
#define Motor4 19
#define LED 25


long duration; // variable for the duration of sound wave travel
int distanceM, distanceL, distanceR; // variable for the distance measurement
int m1Speed = 250;
int m2Speed = 255;
int m1Slow = 100;
int m2Slow = 100;
bool FOUNDMID = false;
bool FOUNDLEFT = false;
bool FOUNDRIGHT = false;
void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT);
  pinMode(IRFrontCenter, INPUT);
  pinMode(IRBackCenter, INPUT);
  pinMode(IRFrontLeft, INPUT);
  pinMode(IRFrontRight, INPUT);
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
  // Calculating the distance in cm
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return distance;
}

//movement functions to move the car
void forward(){
  analogWrite(Motor1, m1Speed);
  analogWrite(Motor2, 0);
  analogWrite(Motor3, 0);
  analogWrite(Motor4, m2Speed);
}

void back(){
  analogWrite(Motor1, 0);
  analogWrite(Motor2, m1Speed);
  analogWrite(Motor3, m2Speed);
  analogWrite(Motor4, 0);
}

void right(){
  analogWrite(Motor1, m1Slow);
  analogWrite(Motor2, 0);
  analogWrite(Motor3, 0);
  analogWrite(Motor4, 0);
}

void left(){
  analogWrite(Motor1, 0);
  analogWrite(Motor2, 0);
  analogWrite(Motor3, 0);
  analogWrite(Motor4, m2Slow);
}

void backright(){
  analogWrite(Motor1, 0);
  analogWrite(Motor2, m1Speed);
  analogWrite(Motor3, m2Slow);
  analogWrite(Motor4, 0);
}

void backleft(){
  analogWrite(Motor1, 0);
  analogWrite(Motor2, m1Slow);
  analogWrite(Motor3, m2Speed);
  analogWrite(Motor4, 0);
}

void stop(){
  back();
  delay(10);
  analogWrite(Motor1, 0);
  analogWrite(Motor2, 0);
  analogWrite(Motor3, 0);
  analogWrite(Motor4, 0);
}

//-------------------------------------------------------------------------------------------
//Main Loop function with algorithm
//-------------------------------------------------------------------------------------------
void loop() {
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

  if(digitalRead(IRFrontCenter) && digitalRead(IRFrontLeft) && digitalRead(IRFrontRight)) {
    //The ring is 122cm so we should be detecting that far from the sensors to check for any object in the ring
    //modified the distance to 122 to check for that.
    if(distanceM < 50){
      forward();
      delay(100);
    }
    else if(distanceR < 50){
      right();
      delay(100);
    }
    else if(distanceL < 50){
      left();
      delay(100);
    }
    else{
      right();
      delay(100);
    }
  }
  else if (!digitalRead(IRFrontCenter)){
    //write code to interrupt this code if another border is detected in the process of going through this piece of code
    back();
    delay(500);
    right();
    delay(500);
  }
  else if (!digitalRead(IRFrontRight)){
    //write code to interrupt this code if another border is detected in the process of going through this piece of code
    back();
    delay(500);
    left();
    delay(500);
  }
  else if (!digitalRead(IRFrontLeft)){
    //write code to interrupt this code if another border is detected in the process of going through this piece of code
    back();
    delay(500);
    right();
    delay(500);
  }
  /*else if (!digitalRead(IRBackCenter)){
    //write code to interrupt this code if another border is detected in the process of going through this piece of code
    forward();
    delay(500);
    left();
    delay(500);
  }*/
  
  delay(1);
}