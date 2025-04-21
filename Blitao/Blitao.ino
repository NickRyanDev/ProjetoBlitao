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


void setup() {
  pinMode(motor0B, OUTPUT);
  pinMode(motor0F, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1F, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2F, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor3F, OUTPUT);
  //Inicia motores
  digitalWrite(EN0, OUTPUT);
  digitalWrite(EN1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
//Move para frente
void forward(int pin0, int pin1){
  digitalWrite(pin0, HIGH);
  digitalWrite(pin1, LOW);
}
//Move para tras
void backward(int pin0, int pin1){
  digitalWrite(pin0, LOW);
  digitalWrite(pin1, HIGH);
}
//Vira para a esquerda
void turnLeft(int pin0, int pin1, int pin3, int pin4){
  backward(pin0, pin1);
  forward(pin3, pin4);
}
//Vira para direita
void turnRight(int pin0, int pin1, int pin3, int pin4){
  backward(pin0, pin1);
  forward(pin3, pin4);
}
