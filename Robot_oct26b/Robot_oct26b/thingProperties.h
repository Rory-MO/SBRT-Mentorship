#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "arduino_secrets.h"

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onSensorDataChange();
void onForwardBackChange();
void onRightLeftChange();
void onLEDChange();

String sensor_data;
int forward_back;
int right_left;
bool led;

void initProperties(){

  ArduinoCloud.addProperty(sensor_data, READWRITE, ON_CHANGE, onSensorDataChange);
  ArduinoCloud.addProperty(forward_back, READWRITE, ON_CHANGE, onForwardBackChange);
  ArduinoCloud.addProperty(right_left, READWRITE, ON_CHANGE, onRightLeftChange);
  ArduinoCloud.addProperty(led, READWRITE, ON_CHANGE, onLEDChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
