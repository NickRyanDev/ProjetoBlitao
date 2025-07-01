#include <SoftwareSerial.h>

#define RX 10
#define TX 11

#define MOTOR1F 3
#define MOTOR1B 5
#define MOTOR2F 6
#define MOTOR2B 9

#define LED1 7
#define LED2 8

SoftwareSerial BLE(RX, TX);

char command;

void setup() {
  pinMode(MOTOR1F, OUTPUT);
  pinMode(MOTOR2F, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
  pinMode(MOTOR2B, OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  BLE.begin(19200);
  Serial.begin(250000);
}

void loop() {
  if(BLE.available()>0){
    Serial.println("conectado");
    command = BLE.read();
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
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        break;
      }
  }

}

void forward(){
  digitalWrite(MOTOR1F, HIGH);
  digitalWrite(MOTOR1B, LOW);
  digitalWrite(MOTOR2F, HIGH);
  digitalWrite(MOTOR2B, LOW);
}

void backward(){
  digitalWrite(MOTOR1F, LOW);
  digitalWrite(MOTOR1B, HIGH);
  digitalWrite(MOTOR2F, LOW);
  digitalWrite(MOTOR2B, HIGH);
}

void left(){
  digitalWrite(MOTOR1F, HIGH);
  digitalWrite(MOTOR1B, LOW);
  digitalWrite(MOTOR2F, LOW);
  digitalWrite(MOTOR2B, HIGH);
}

void right(){
  digitalWrite(MOTOR1F, LOW);
  digitalWrite(MOTOR1B, HIGH);
  digitalWrite(MOTOR2F, HIGH);
  digitalWrite(MOTOR2B, LOW);
}

void blinkLed(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(200);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}
