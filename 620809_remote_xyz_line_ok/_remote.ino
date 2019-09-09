void resive() {
  for (int iChannel = 0; iChannel < 6; iChannel++)
  {
    readChannel(iChannel);
  }
  r_x = chValue[0];
  r_y = chValue[1];
  r_z = chValue[3];

  r_mode = chValue[4];
  r_drop = chValue[5];
  r_speedx = chValue[2];
}

void remote() {
  for (int iChannel = 0; iChannel < 8; iChannel++)
  {
    readSW(iChannel);
  }

  //printChannel();
  // printSW();
  control();
}

void disp_remote() {
  //==============================================

  int   Temp = z;
  modeDisp.setRow(0, 3, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    modeDisp.setRow(0, 3, 1);
  }
  modeDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 2, Temp % 10, false);

  Temp = y;
  nCOuntDisp.setRow(0, 3, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    nCOuntDisp.setRow(0, 3, 1);
  }
  nCOuntDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 2, Temp % 10, false);

  Temp = x;
  nCOuntDisp.setRow(0, 7, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    nCOuntDisp.setRow(0, 7, 1);
  }
  nCOuntDisp.setDigit(0, 4, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 5, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 6, Temp % 10, false);
  speed_disp();
}

void speed_disp() {
  int Temp = speedx;
  modeDisp.setRow(0, 7, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    modeDisp.setRow(0, 7, 1);
  }
  modeDisp.setDigit(0, 4, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 5, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 6, Temp % 10, false);
}
