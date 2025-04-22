//include Libraries
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
//Shield Pins
const int EN0 = 18;
const int EN1 = 19;
const int motor0B = 7;
const int motor0F = 8;
const int motor1B = 12;
const int motor1F = 13;
const int motor2B = 14;
const int motor2F = 15;
const int sawMotor = 16;
//Bluethooth Control
char command;
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define FORWARD 'F'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
//Player Pins
const int pinRX = 10;
const int pinTX = 11;
//Instance Player Variables
SoftwareSerial serial(pinRX, pinTX);
DFRobotDFPlayerMini player;

void setup() {
  pinMode(motor0B, OUTPUT);
  pinMode(motor0F, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1F, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2F, OUTPUT);
  pinMode(sawMotor, OUTPUT);
  //Iniciate motors
  digitalWrite(EN0, OUTPUT);
  digitalWrite(EN1, OUTPUT);
  //Iniciate Bluethooth Serial Communication
  Serial.begin(9600);
  //Iniciate DFPlayer Serial Communication and set volume
  serial.begin(9600);
  player.volume(28);
}

void loop() {
  if (Serial.available()){
    command = Serial.read();
    switch (command){
      //Moves
      case FORWARD:
        forwardTwoMotors(motor0B, motor0F, motor1B, motor1F);
        break;
      case BACKWARD:
        backwardTwoMotors(motor0B, motor0F, motor1B, motor1F);
        break;
      case LEFT:
        turnLeft(motor0B, motor0F, motor1B, motor1F);
        break;
      case RIGHT:
        turnRight(motor0B, motor0F, motor1B, motor1F);
        break;
      //weapon
      case TRIANGLE:
        attack(sawMotor, motor2B, motor2F);
        break;
      case CROSS:
        backAttack(sawMotor, motor2B, motor2F);
        break;
      //Ornaments
      case SQUARE:
        player.play(1);
        break;
      default:
        standing(motor0B, motor0F, motor1B, motor1F);
        break;
    }
  }
}


//Move single motor forward
void forward(int pin0, int pin1){
  digitalWrite(pin0, HIGH);
  digitalWrite(pin1, LOW);
}
//Move single motor backward
void backward(int pin0, int pin1){
  digitalWrite(pin0, LOW);
  digitalWrite(pin1, HIGH);
}
//Turn to Left
void turnLeft(int pin0, int pin1, int pin3, int pin4){
  backward(pin0, pin1);
  forward(pin3, pin4);
}
//Turn to Right
void turnRight(int pin0, int pin1, int pin3, int pin4){
  forward(pin0, pin1);
  backward(pin3, pin4);
}
void forwardTwoMotors(int pin0, int pin3){
  digitalWrite(pin0, HIGH);
  digitalWrite(pin3, HIGH);
}
void backwardTwoMotors(int pin1, int pin4){
  digitalWrite(pin1, HIGH);
  digitalWrite(pin4, HIGH);
}
void standing(int pin0, int pin1, int pin3, int pin4){
  digitalWrite(pin0, LOW);
  digitalWrite(pin1, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
//Turn on saw's motor
void sawOn(int sawPin){
  digitalWrite(sawPin, HIGH);
}
void sawOff(int pisawPinn){
  digitalWrite(sawPin, LOW);
}

//Weapons attack
void attack(int sawPin, int pin0, int pin1){
  sawOn(sawPin);
  forward(pin0, pin1);
}
void backAttack(int sawPin, int pin0, intpin1){
  sawOff(sawPin);
  backward(pin0, pin1);
}