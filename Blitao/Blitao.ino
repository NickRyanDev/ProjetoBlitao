//Shield Pins
const int EN0 = 12;
const int EN1 = 13;
const int motor0B = 4;
const int motor0F = 5;
const int motor1B = 6;
const int motor1F = 7;
const int motor2B = 8;
const int motor2F = 9;
const int motor3B = 10;
const int motor3F = 11;
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

void setup() {
  pinMode(motor0B, OUTPUT);
  pinMode(motor0F, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1F, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2F, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor3F, OUTPUT);
  //Iniciate motors
  digitalWrite(EN0, OUTPUT);
  digitalWrite(EN1, OUTPUT);
  //Iniciate Serial Communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    command = Serial.read();
    switch (command){
      case FORWARD:
        forwardTwoMotors(motor0B, motor0F, motor1B, motor1F);
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
void forwardTwoMotors(int pin0, int pin1, int pin3, int pin4){
  forward(pin0, pin1);
  forward(pin3, pin4);
}
void backwardTwoMotors(int pin0, int pin1, int pin3, int pin4){
  backward(pin0, pin1);
  backward(pin3, pin4);
}