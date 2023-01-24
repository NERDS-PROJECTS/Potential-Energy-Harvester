#include <SoftwareSerial.h>
#include <Servo.h>
int motor1Pin1 = 3;
int motor1Pin2 = 4;
int enable1Pin = 6;
int motor2Pin1 = 8;
int motor2Pin2 = 9;
int enable2Pin = 11;
int bluetoothTx = 5;
int bluetoothRx = 7;
Servo servo1;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
int state;
int flag = 0;
int stateStop = 0;
void setup() {

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  servo1.attach(2);
 
 analogWrite(enable1Pin, 200);
 analogWrite(enable2Pin, 200);
  
Serial.begin(9600);
  bluetooth.begin(9600);
  servo1.write(0);
  
}

void loop() {

  while (bluetooth.available() == 0)
  {}

  state = bluetooth.read();
  flag = 0;

  
  if (state == 'F') {
    servo1.write(90);
   
    delay(10);
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("OK");
    if (flag == 0) {
      Serial.println("Go Forward!");
      flag = 1;
    }
  }


  else if (state == 'R') {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    if (flag == 0) {
      Serial.println("Turn RIGHT");
      flag = 1;
    }
    delay(1500);
    state = 3;
    stateStop = 1;
  }
else if (state == 'L') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2,HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);   
    if (flag == 0) {
      Serial.println("Turn LEFT");
      flag = 1;
    }
    delay(1500);
    state = 3;
    stateStop = 1;
  }
  else if (state == 'S' || stateStop == 1) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
     digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    if (flag == 0) {
     
      flag = 1;
    }
    stateStop = 0;
  }
  

  else if (state == 'S') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    if (flag == 0) {
    
      flag = 1;
    }
    delay(1500);
    state = 3;
    stateStop = 1;
  }

  else if (state == 'B') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    if (flag == 0) {
     
      flag = 1;
    }
  }
 
}