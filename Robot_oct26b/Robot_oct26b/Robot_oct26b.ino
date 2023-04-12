#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "thingProperties.h"
#include "arduino_secrets.h"

void setup(){
  
  // Serial monitor, 9600 baud, 1.5 second delay to prevent IoT Cloud updating errors
  Serial.begin(9600);
  delay(1500);
  
  // A1M8 LiDAR Setup
  Serial1.begin(115200);   // Set up UART
  pinMode(LIDAR_MOTOR, 1); // Motor that spins LiDAR
  lidar.begin(Serial1);

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

  //TSL2561 Light Sensor Setup
  //the TSL2561 Light Sensor will have an address of 
  TSL2561 tsl(0x39);
  tsl.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
  //tsl.setGain(TSL2561_GAIN_0X);         // set no gain (for bright situtations)
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);

  
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
    previousMillis = currentMillis; // Reset last output time as current time
    
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

  CO++; // Change the value of CO to keep refreshing messenger on dashboard
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

