//Setting pins for motors
//Left motors
const int enA = 3;
const int leftmotor1 = 4;
const int leftmotor2 = 5;

//Right motors
const int enB = 11;
const int rightmotor1 = 6;
const int rightmotor2 = 7;

//Move forward function
void forward(float speed){
  digitalWrite(leftmotor1, HIGH);
  digitalWrite(leftmotor2, LOW);
  digitalWrite(rightmotor1, HIGH);
  digitalWrite(rightmotor2, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

//Move backward function
void backward(float speed){
  digitalWrite(leftmotor1, LOW);
  digitalWrite(leftmotor2, HIGH);
  digitalWrite(rightmotor1, LOW);
  digitalWrite(rightmotor2, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

//Turn left function
//Left motors go backward, right motors go forward
void left(float speed){
  digitalWrite(leftmotor1, LOW);
  digitalWrite(leftmotor2, HIGH);
  digitalWrite(rightmotor1, HIGH);
  digitalWrite(rightmotor2, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

//Turn right function
//Left motors go forward, right motors go backward
void right(float speed){
  digitalWrite(leftmotor1, HIGH);
  digitalWrite(leftmotor2, LOW);
  digitalWrite(rightmotor1, LOW);
  digitalWrite(rightmotor2, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

//Stop motors
void stop(){
  digitalWrite(leftmotor1, LOW);
  digitalWrite(leftmotor2, LOW);
  digitalWrite(rightmotor1, LOW);
  digitalWrite(rightmotor2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void setup() {
  //Set motor pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(leftmotor1, OUTPUT);
  pinMode(leftmotor2, OUTPUT);
  pinMode(rightmotor1, OUTPUT);
  pinMode(rightmotor2, OUTPUT);
}

void loop() {
  //Forward movement
  forward(100); //speed 100
  delay(1000);  //wait 1 second

  //Backward movement
  backward(100);
  delay(1000);

  //Turn left
  left(100);
  delay(1000);  

  //Turn right
  right(100);
  delay(1000);

  //Stop Motors
  stop();
  delay(1000);
}
