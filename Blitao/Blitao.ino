//include Libraries
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
//L293D pins
const int EN0 = 14;
const int EN1 = 15;
const int EN2 = 18;
const int motor0B = 3; //PWM Pin
const int motor0F = 2;
const int motor1B = 9; //PWM Pin
const int motor1F = 8;
const int motor2B = 4;
const int motor2F = 7;
const int sawMotor = 13;
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
//Serial Communication Pins
const int playerPinRX = 10;
const int playerPinTX = 11;
const int blePinRX = 5;
const int blePinTX = 6;
//Instance Serial Variables
SoftwareSerial playerSerial(playerPinRX, playerPinTX);
SoftwareSerial bleSerial(blePinRX, blePinTX);
//Instance Player Variables
DFRobotDFPlayerMini player;

//Ornaments pins
const int leftEye = 16;
const int rightEye = 17;

void setup() {
  //Set Motors Pins
  pinMode(motor0B, OUTPUT);
  pinMode(motor0F, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1F, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2F, OUTPUT);
  pinMode(sawMotor, OUTPUT);
  //Set Enable Pins
  digitalWrite(EN0, OUTPUT);
  digitalWrite(EN1, OUTPUT);
  digitalWrite(EN2, OUTPUT);
  //Iniciate motors
  digitalWrite(EN0, HIGH);
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  //Iniciate Serial Communication
  Serial.begin(2000000);
  //Iniciate Bluethooth Serial Communication
  bleSerial.begin(9600);
  //Iniciate DFPlayer Serial Communication and set volume
  playerSerial.begin(9600);
  while(!player.begin(playerSerial)){
    Serial.println("Modulo nao disponivel");
  }
  if(player.begin(playerSerial)){
    Serial.println("Modulo Ativo");
  }
  Serial.println("Iniciando Configuracao do modulo...");
  player.setTimeOut(500);
  player.volume(28);
  player.EQ(0);
  Serial.println("Configuracao finalizada");
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
//Makes forward more slow
void slowSpeed(int pin0, int pin1){
  analogWrite(pin0, 60);
  digitalWrite(pin1, LOW);
}
//Turn to Left
void turnLeft(int pin0, int pin1, int pin3, int pin4){
  slowSpeed(pin0, pin1);
  forward(pin3, pin4);
}
//Turn to Right
void turnRight(int pin0, int pin1, int pin3, int pin4){
  forward(pin0, pin1);
  slowSpeed(pin3, pin4);
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

//Ornaments functions
void playFistSound(){
  player.play(1);
  delay(2000);
}
void playSecondSound(int leftEye, int rightEye){
  player.play(2);
  blinkEye(leftEye, rightEye),
}
void blinkEye(int leftEye, int rightEye){
  digitalWrite(leftEye, LOW);
  delay(500);
  digitalWrite(leftEye, HIGH);
  delay(250);
  digitalWrite(rightEye, LOW);
  delay(250);
  digitalWrite(rightEye, HIGH);
  delay(250);
  digitalWrite(rightEye, LOW);
  digitalWrite(leftEye, LOW);
  delay(250);
  digitalWrite(rightEye, HIGH);
  digitalWrite(leftEye, HIGH);
  delay(500);
}