


void carbonMonoxide(){
  
}

void pressure()
{
    
    //define Sensor MPL1152A

    int sensor = 11;
    int sensor1 = 12;
    int pcomp,pressure;
  
    long arr[20];
    int index = 0;
    Wire.beginTransmission(0x60);
    for(int i = 0; i < 12; i++)
    {
      Wire.write(i);
    }
    Wire.endTransmission(false);
    Wire.requestFrom(0x60,11);
    while (Wire.available())
    {
      arr[index++] = Wire.read();
     // Padc_MSB = Padc_MSB << 8;
    }
    for(int i = 0; i < 12; i++)
    {
      //Serial.println(arr[i]);
    }
    arr[0] = arr[0] << 8 || arr[1]; //padc
    arr[2] = arr[2] << 8 || arr[3];//tadc
    arr[4] = arr[4] << 8 || arr[5];//a0
    arr[6] = arr[6] << 8 || arr[7];//b1
    arr[8] = arr[8] << 8 || arr[9]; //b2
    arr[10] = arr[10] << 8 || arr[11];//c12
    pcomp = arr[4] + (arr[6] + arr[10] * arr[2]) * arr[0] + arr[8] + arr[2];
    pcomp = pcomp * ((115-50)/1023) + 50;
    pressure = pcomp;
    Serial.print("PCOMP = ");
    Serial.println(pcomp);
    Serial.println("new");
    delay(5000);
    
}