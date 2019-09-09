void control() {  
  resive();
  if (r_x == 1)x++;
  if (r_x == 0)x--;

  if (r_y == 1)y++;
  if (r_y == 0)y--;

  if (r_z == 1)z++;
  if (r_z == 0)z--;

  if (r_drop == 0)drop = 0;
  if (r_drop == 1)drop = 1;

  if (r_mode == 0){mode = 0; x=0; y=0; z=0;}
  else if (r_mode == 1)mode = 1;
  else mode = 0.5;


  //====speed=====================================
  speedx = map(r_speedx * 100,0,100,0,500);

  printcontrol();
}

void printcontrol() {
  
  Serial.print(" X : "); Serial.print(x);
  Serial.print(" Y : "); Serial.print(y);
  Serial.print(" Z : "); Serial.print(z);
  Serial.print(" Sp : "); Serial.print(speedx);
  Serial.print(" Mode : "); Serial.print(mode);
  Serial.print(" Drop : "); Serial.print(drop);
//  Serial.println();
}

void printChannel()
{
  for (int iChannel = 0; iChannel < 6; iChannel++)
  {
//    Serial.print(" #");
//    Serial.print(iChannel);
    Serial.print(": ");
    Serial.print(chValue[iChannel]);
  };
  Serial.println(";");
}

void printSW()
{
  for (int iChannel = 0; iChannel < 8; iChannel++)
  {
    Serial.print(" #");
    Serial.print(iChannel);
    Serial.print(": ");
    Serial.print(swValue[iChannel]);
  };
  Serial.print(";");
}


float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void readChannel(int channel)
{
  int rawValue = pulseIn(rcPins[channel], HIGH, pulseInDelay);
 // Serial.print(rawValue); Serial.print(" ");
  chValue[channel] = fmap( (float)rawValue, 1000.0, 1900.0, 0.0, 1.0);
  chValue[channel] = chValue[channel] < 0.0 ? 0.0 : chValue[channel];
  chValue[channel] = chValue[channel] > 1.0 ? 1.0 : chValue[channel];
}

void readSW(int channel)
{
 swValue[channel] = digitalRead(swPins[channel]);
}
