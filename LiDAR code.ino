#include <RPLidar.h> //rp lidar library
#define RPLIDAR_MOTOR 3 //The PWM pin to control motor speed

RPLidar lidar; //creating an instance of the driver called lidar

void setup() {
  Serial.begin(115200); //set baud rate of data transmission
  Serial1.begin(115200);
  lidar.begin(Serial1);  //begin the lidar object
  pinMode(RPLIDAR_MOTOR, OUTPUT); // set pin modes
}

//initialize minimum distance and angle at minimum distance
float minDistance = 100000;
float angleAtMinDist = 0;

void loop() {
  if (IS_OK(lidar.waitPoint())) { //check if lidar is at a wait point
    float distance = lidar.getCurrentPoint().distance; //get current distance in mm
    float angle = lidar.getCurrentPoint().angle;  //0-360 degrees
    
    if (lidar.getCurrentPoint().startBit) { //check if this is a new scan
      //if new scan, display previous data
       Serial.print("dist: ");
       Serial.print(mindistance);
       Serial.print("    angle: ");
       Serial.println(angleatMinDist);
       //reset min distance and angle
       minDistance = 100000;
       angleAtMinDis = 0;
    } else {
      if (distance < minDistance) { //setting min distance and angle during scan
        minDistance = distance;
        angleAtMinDist = angle;
      }
    }
  }
  else { //if it isn't at the wait point
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    // Try to detect RPLIDAR
    rplidar_response_device_info_t info; 
    if (IS_OK(lidar.getDeviceInfo(info, 100))) { // Detected
       lidar.startScan(); //if lidar is detected, scan it
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000); //delay, then start motor again
    }
  }
}