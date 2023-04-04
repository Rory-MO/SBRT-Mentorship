#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "thingProperties.h"
#include "arduino_secrets.h"

// Sensor values to be measured
uint8_t CO = 0;           // MQ7
uint8_t CO2 = 1;          // Sensirion
uint8_t Humidity = 2;     // Sensirion
uint8_t Temperature = 3;  // Sensirion
uint8_t Incline = 4;      // MPU6050
uint8_t Light = 5;        // TSL2561
uint8_t PM25 = 6;         // PMS5003
uint8_t Pressure = 7;     // MPL115A2

// For timer counter use
unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 5000;

void setup(){
  
  // Serial monitor, 9600 baud, 1.5 second delay to prevent IoT Cloud updating errors
  Serial.begin(9600);
  delay(1500);
  
  // Initialize IoT Cloud variables
  initProperties();
  
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  //setDebugMessageLevel(2);
  //ArduinoCloud.printDebugInfo();
  
  Serial.println("Setup finished");
}

void loop(){
  ArduinoCloud.update();  // Update values of IoT Cloud variables

/*
  The timer counter feature millis() is used 
  to output the sensor values every 5 seconds.
  This is to prevent lag, as outputting sensor values constantly 
  would slow down the movement sliders.
*/
  currentMillis = millis(); // Check current time
  if (currentMillis - previousMillis >= interval){  // If 5 seconds has passed
    previousMillis = currentMillis; // Set last output time as current time
    
    // Output to IoT cloud variable connected to Messenger display on dashboard
    // Typecast the values to strings b/c sensor_data is a string
    sensor_data = "CO = "           + String(CO)          + "\n" +
                  "CO2 = "          + String(CO2)         + "\n" +
                  "Humidity = "     + String(Humidity)    + "\n" +
                  "Temperature = "  + String(Temperature) + "\n" +
                  "Incline = "      + String(Incline)     + "\n" +
                  "Light = "        + String(Light)       + "\n" +
                  "PM2.5 = "        + String(PM25)        + "\n" +
                  "Pressure = "     + String(Pressure)    + "\n";
  }

}


void onForwardBackChange()  {
  nextMove();
}

void onRightLeftChange()  {
  nextMove();
}

void onSensorDataChange()  {
  /*
    The sensor_data variable is updated every 5 seconds
    with the values of all the sensors
  */
}

void onLEDChange()  {
  Serial.println("LED color changed");
}

#define ENABLE_SPEED    0
#define RIGHT_MOTORS_1  1
#define RIGHT_MOTORS_2  2
#define LEFT_MOTORS_1   3
#define LEFT_MOTORS_2   4

#define STOP_UPPER_BOUND  10
#define STOP_LOWER_BOUND -10

uint8_t speed;

void nextMove(){
  // Function to read/write variables between MKR1010 and cloud
  ArduinoCloud.update();

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