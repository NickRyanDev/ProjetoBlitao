#include <SoftwareSerial.h>

#define RX 10
#define TX 11

#define MOTOR1F 3
#define MOTOR1B 5
#define MOTOR2F 6
#define MOTOR2B 9

#define LED1 7
#define LED2 8

#define STATE 12
int BLEState = 0;
SoftwareSerial BLE(RX, TX);

char command;

const int defaultSpeed = 225;
const int lowSpeed = 200;
const int highSpeed = 255;
const int stopped = 0;

void setup() {
  pinMode(MOTOR1F, OUTPUT);
  pinMode(MOTOR2F, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
  pinMode(MOTOR2B, OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(STATE, INPUT);

  BLE.begin(19200);
  Serial.begin(250000);
}

void loop() {
  Serial.println(STATE);
  if(BLE.available()>0){
    Serial.println("conectado");
    BLEState = digitalRead(STATE);
    command = BLE.read();
    Serial.println(command);
    switch(command){
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'C':
        blinkLed();
        break;
      default:
        digitalWrite(MOTOR1F, LOW);
        digitalWrite(MOTOR1B, LOW);
        digitalWrite(MOTOR2F, LOW);
        digitalWrite(MOTOR2B, LOW);
        indicatesConnection(BLEState);
        break;
      }
  }

}

void forward(){
  analogWrite(MOTOR1F, defaultSpeed);
  analogWrite(MOTOR1B, stopped);
  analogWrite(MOTOR2F, defaultSpeed);
  analogWrite(MOTOR2B, stopped);
}

void backward(){
  analogWrite(MOTOR1F, stopped);
  analogWrite(MOTOR1B, defaultSpeed);
  analogWrite(MOTOR2F, stopped);
  analogWrite(MOTOR2B, defaultSpeed);
}

void right(){
  analogWrite(MOTOR1F, defaultSpeed);
  analogWrite(MOTOR1B, lowSpeed);
  analogWrite(MOTOR2F, lowSpeed);
  analogWrite(MOTOR2B, defaultSpeed);
}

void left(){
  analogWrite(MOTOR1F, lowSpeed);
  analogWrite(MOTOR1B, defaultSpeed);
  analogWrite(MOTOR2F, defaultSpeed);
  analogWrite(MOTOR2B, lowSpeed);
}

void blinkLed(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(200);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void indicatesConnection(int BLEState){
  if(BLEState==0){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  else{
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
}
