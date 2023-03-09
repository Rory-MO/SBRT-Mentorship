// Have the values of the sensor written to the Serial terminal (Use Serial, not Serial1)
// Comment every line of code you write
// Create a branch on the Github to upload your code (do NOT push to the main branch, you must create your own with your own name in the name of the branch)
// Do not use the IoT features yet, just write the bare bones code of reading the sensor and outputting the sensor reading to the Serial terminal on your laptop
#include <RPLidar.h>
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).

RPLidar lidar;
                      
void setup() {
  Serial.begin(115200);   // output to Serial
  Serial1.begin(115200);  // For RPLidar
  lidar.begin(Serial);    // configure lidar for serial
  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes
}

float minDistance = 100000;   // set initial value of minDistance
float angleAtMinDist = 0;     // set initial value of angleAtMinDist

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    //perform data processing here... 
    float distance = lidar.getCurrentPoint().distance;  // get distance to nearest object
    float angle = lidar.getCurrentPoint().angle;  // get angle (0-360 deg)
    
    if (lidar.getCurrentPoint().startBit) {
       // a new scan, display the previous data...
       printData(angleAtMinDist, minDistance);  
       minDistance = 100000;  // reset to initial minDistance
       angleAtMinDist = 0;    // reset to initial angleAtMinDist
    } else {
       if ( distance > 0 &&  distance < minDistance) { // if within range
          minDistance = distance; // get new minDistance
          angleAtMinDist = angle; // get new angle
       }
    }
  }
  else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    // Try to detect RPLIDAR
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) { // check detection
       // Detected --> start the scan
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255); // turn on the motor
       delay(1000); // wait 1 second 
    }
  }
}

// prints the distance and angle during scan
void printData(float angle, float distance)
{
  Serial.print("dist: ");
  Serial.print(distance);
  Serial.print("    angle: ");
  Serial.println(angle);
}
