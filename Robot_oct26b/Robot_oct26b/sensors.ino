void carbonMonoxide(){
  
}

void pressure()
{
    
    //define Sensor MPL1152A

    int sensor = 11;
    int sensor1 = 12;
    int pcomp,Pressure;
  
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
    Pressure = pcomp;
    Serial.print("PCOMP = ");
    Serial.println(pcomp);
    Serial.println("new");
    delay(5000);
    
}

void light(){
  //ADDR pin is left floating
  //VDD is connected to 3.3V

  //uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);
  //uint16_t x = tsl.getLuminosity(TSL2561_FULLSPECTRUM);
  //uint16_t x = tsl.getLuminosity(TSL2561_INFRARED);

  //Serial.print(x, DEC);
  //Serial.print("\t");

  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;

  int visibleLight = full-ir;
  Light = visibleLight; 
  Serial.print("Visible Light: "); Serial.print(visibleLight);   Serial.print("\t");
  //Serial.print("Infared Light: "); Serial.print(ir);   Serial.print("\t");
  //Serial.print("Full rangle: "); Serial.print(full);   Serial.print("\t");
  Serial.print("\n");
}