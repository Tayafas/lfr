#include <NewPing.h>
#include <Servo.h>


//sonar
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define max_distance 50

//ir
#define irLeft A4
#define irRight A2
#define irmiddle A3
#define irfarleft A5
#define irfarright A1

//mot
int ena = 1;
int in1 = 7;
int in2 = 6;
int in3 = 4;
int in4 = 5;
int enb = 9;

Servo servo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, max_distance);



int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

void setup() {
  Serial.begin(9600);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  pinMode(irmiddle, INPUT);
  pinMode(irfarleft, INPUT);
  pinMode(irfarright, INPUT);
  servo.attach(10);
  servo.write(90);
  
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  }

void loop() {
  if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 0 && digitalRead(irfarright) == 0 && digitalRead(irfarleft) == 0 && digitalRead(irmiddle) == 1){
    objectAvoid();
    moveForward();
    //forword
  }
  else if (digitalRead(irLeft) == 0 && (digitalRead(irRight) == 1 || digitalRead(irfarright) == 1 )) {
    objectAvoid();
    Serial.println("TR");
    //leftturn
    moveRight();
    delay(100);
  }
  else if ((digitalRead(irLeft) == 1 || digitalRead(irfarleft) == 1) && digitalRead(irRight) == 0 ) {
    objectAvoid();
    Serial.println("TL");
    //rightturn
    moveLeft();
    delay(100);
  }
  else if ((digitalRead(irLeft) == 1 && digitalRead(irRight) == 1 && digitalRead(irfarright) == 1 && digitalRead(irfarleft) == 1 && digitalRead(irmiddle) == 1)) {
    //Stop
    Stop();
  }
}

void objectAvoid() {
  distance = getDistance();
  if (distance <= 15) {
    //stop
    Stop();
    Serial.println("Stop");

    lookLeft();
    lookRight();
    delay(100);
    if (rightDistance <= leftDistance) {
      //left
      object = true;
      turn();
      Serial.println("moveLeft");
    } else {
      //right
      object = false;
      turn();
      Serial.println("moveRight");
    }
    delay(100);
  }
  else {
    //forword
    Serial.println("moveforword");
    moveForward();
  }
}

int getDistance() {
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}

int lookLeft () {
  //lock left
  servo.write(150);
  delay(500);
  leftDistance = getDistance();
  delay(100);
  servo.write(90);
  Serial.print("Left:");
  Serial.print(leftDistance);
  return leftDistance;
  delay(100);
}

int lookRight() {
  //lock right
  servo.write(30);
  delay(500);
  rightDistance = getDistance();
  delay(100);
  servo.write(90);
  Serial.print("   ");
  Serial.print("Right:");
  Serial.println(rightDistance);
  return rightDistance;
  delay(100);
}
void Stop() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(10);
}
void moveForward() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(10);
}
void moveBackward() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(10);
}
void turn() {
  if (object == false) {
    Serial.println("turn Right");
    moveLeft();
    delay(700);
    moveForward();
    delay(800);
    moveRight();
    delay(900);
    if (digitalRead(irRight) == 1) {
      loop();
    } else {
      moveForward();
    }
  }
  else {
    Serial.println("turn left");
    moveRight();
    delay(700);
    moveForward();
    delay(800);
    moveLeft();
    delay(900);
    if (digitalRead(irLeft) == 1) {
      loop();
    } else {
      moveForward();
    }
  }
}
void moveLeft() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(10);
}
void moveRight() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(10);}
