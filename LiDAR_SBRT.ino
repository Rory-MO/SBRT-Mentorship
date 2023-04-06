#include <RPLidar.h>
#define RPLIDAR_MOTOR 12 // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).
#define COLLISION_DISTANCE 200 // Min distnace before robot is forced to stop MUST BE GREATER THAN 70
#define GO 10 // Orange LED indicates clear collision zone
#define STOP 9 // Red LED indicates object in collision zone
RPLidar lidar;
                      
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);  // For RPLidar
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes
  pinMode(GO, OUTPUT); 
  pinMode(STOP, OUTPUT);
}




void loop() {
  if (IS_OK(lidar.waitPoint())) {
    //perform data processing here... 
    float distance = lidar.getCurrentPoint().distance - 30; //Get distance in mm, 30mm offset
    float angle = lidar.getCurrentPoint().angle;  // 0-360 deg
    //If the obstacle is within the collsion distance and infront of the robot, stop
     if((angle > 350 || angle < 10) && distance > 0 && distance < COLLISION_DISTANCE)  { 
      printData(angle, distance);
      digitalWrite(STOP, HIGH); // Turn on red LED
      digitalWrite(GO, LOW); // Turn off orange LED
      //stop();
      //return;
     }
     else if((angle > 350 || angle < 10) && distance > COLLISION_DISTANCE) {
       digitalWrite(STOP, LOW); // Turn off red LED
       digitalWrite(GO, HIGH); //Turn on orange LED
     }
    
  }
  else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor if unresponsive
    // Try to detect RPLIDAR
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // Detected
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255); // If the lidar is responsive resume motor
       delay(1000);
    }
  }
}

void printData(float angle, float distance)
{
  Serial.print("dist: ");
  Serial.print(distance);
  Serial.print(" mm");
  Serial.print("    angle: ");
  Serial.println(angle);
}

