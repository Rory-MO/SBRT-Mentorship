#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "thingProperties.h"

void setup(){
  
  Serial.begin(9600);
  delay(1500);
  
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
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  pinMode(LED_BUILTIN, 1);
  digitalWrite(LED_BUILTIN, 1);
  
  Serial.println("Setup finished");
}

// Testing values
uint8_t temp = 25;
uint8_t co2 = 500;
uint8_t pm25 = 20;

// For timer counter use
unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 5000;

void loop(){ 
  // Function to read/write variables between MKR1010 and cloud
  ArduinoCloud.update();

  // Print out values from movement sliders of dashboard
  Serial.print("Motor movement: ");
  Serial.print(forward_back);
  Serial.print(", ");
  Serial.println(right_left);

  // In order to prevent the send/receive requests from getting overloaded
  // and slowing down our movement control sliders,
  // we poll the sensor data every 5 seconds using the millis function (timer counter)
  currentMillis = millis(); // Read current time
  // If five seconds has passed since the last sensor reading
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis; // Set the last sensor reading

    // Output to IoT cloud variable connected to Messenger display on dashboard
    // Typecast the values to strings b/c sensor_data is a string
    sensor_data = "Temperature = " + String(temp) + 
    "\nCarbon Dioxide: " + String(co2) + "\nPM25: " + String(pm25);
  }
}

void onForwardBackChange()  {
  nextMove();
}

void onRightLeftChange()  {
  nextMove();
}

void onSensorDataChange()  {
  // Add your code here to act upon SensorData change
}

void onLEDChange()  {
  Serial.println("LED color changed");
}