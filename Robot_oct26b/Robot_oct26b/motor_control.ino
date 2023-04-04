/*
    Motor driver code

*/


void nextMove(){
  // Function to read/write variables between MKR1010 and cloud
  // ArduinoCloud.update();

  // Stop robot, forward/back slider between -10 and 10
  if((forward_back < 10) && (forward_back > -10)){
    stop();
    return;
  }
  // Move right, left_right slider above 10
  if (right_left > 10){
    right();
    return;
  }
  // Move left, left_right slider below 10
  if (right_left < -10){
    left();
    return;
  }
  // Move forward, forward_back slider above 10
  if (forward_back > 10){
    forward();
    return;
  }
  // Move backward, forward_back slider below -10
  if (forward_back < -10){
    backward();
    return;
  }

}


/*************************************
*********** DIRECTIONS ***************
**************************************/

void stop(){
  analogWrite(ENABLE_SPEED, 0);
  Serial.println("Robot is stopped");
}

void forward(){
  // Take forward slider speed value and adjust it to range of PWM speed pin
  // left_right is the slider value in range of 10 to 50, translated to range of 0-255 for speed value
  speed = map(forward_back, 10, 50, 0, 255);
  analogWrite(ENABLE_SPEED, speed);

  // Set direction of motor spin to move forward
  digitalWrite(RIGHT_MOTORS_1, 1);
  digitalWrite(RIGHT_MOTORS_2, 0);
  digitalWrite(LEFT_MOTORS_1, 1);
  digitalWrite(LEFT_MOTORS_2, 0);

  Serial.print("Robot is moving forward, at speed: ");
  Serial.print(forward_back);
  Serial.print(", ");
  Serial.println(speed);
}

void backward(){
  // Take backward slider speed value and adjust it to range of PWM speed pin
  // left_right is the slider value in range of -10 to -50, translated to range of 0-255 for speed value
  speed = map(forward_back, -10, -50, 0, 255);
  analogWrite(ENABLE_SPEED, speed);

  // Set direction of motor spin to move backward
  digitalWrite(RIGHT_MOTORS_1, 0);
  digitalWrite(RIGHT_MOTORS_2, 1);
  digitalWrite(LEFT_MOTORS_1, 0);
  digitalWrite(LEFT_MOTORS_2, 1);

  Serial.print("Robot is moving backward, at speed: ");
  Serial.print(forward_back);
  Serial.print(", ");
  Serial.println(speed);
}

void right(){
  // Take forward slider speed value and adjust it to range of PWM speed pin
  // left_right is the slider value in range of 10 to 50, translated to range of 0-255 for speed value
  speed = map(abs(forward_back), 10, 50, 0, 255);
  analogWrite(ENABLE_SPEED, speed);

  // Set direction of motor spin to turn right
  digitalWrite(RIGHT_MOTORS_1, 0);
  digitalWrite(RIGHT_MOTORS_2, 1);
  digitalWrite(LEFT_MOTORS_1, 1);
  digitalWrite(LEFT_MOTORS_2, 0);  

  Serial.print("Robot is turning right, at speed: ");
  Serial.print(forward_back);
  Serial.print(", ");
  Serial.print(right_left);
  Serial.print(", ");
  Serial.println(speed);
}

void left(){
  // Take forward slider speed value and adjust it to range of PWM speed pin
  // left_right is the slider value in range of -10 to -50, translated to range of 0-255 for speed value
  speed = map(abs(forward_back), -10, -50, 0, 255);
  analogWrite(ENABLE_SPEED, speed);

  // Set direction of motor spin to turn left
  digitalWrite(RIGHT_MOTORS_1, 1);
  digitalWrite(RIGHT_MOTORS_2, 0);
  digitalWrite(LEFT_MOTORS_1, 0);
  digitalWrite(LEFT_MOTORS_2, 1);

  Serial.print("Robot is turning left, at speed: ");
  Serial.print(forward_back);
  Serial.print(", ");
  Serial.print(right_left);
  Serial.print(", ");
  Serial.println(speed);  
}