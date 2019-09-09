
//=============================================================
void Port_Initial(void) {
  pinMode(Port_ID1, INPUT_PULLUP);
  pinMode(Port_ID2, INPUT_PULLUP);
  pinMode(Port_ID3, INPUT_PULLUP);
  pinMode(Port_ID4, INPUT_PULLUP);
  pinMode(Port_ID5, INPUT_PULLUP);
  pinMode(Port_ID6, INPUT_PULLUP);
  pinMode(Port_ID7, INPUT_PULLUP);
  pinMode(Port_ID8, INPUT_PULLUP);

  pinMode(Port_Sw1, INPUT_PULLUP);
  pinMode(Port_Sw2, INPUT_PULLUP);
  pinMode(Port_Sw3, INPUT_PULLUP);
  pinMode(Port_Sw4, INPUT_PULLUP);

  pinMode(Port_LED1, OUTPUT);
  pinMode(Port_LED2, OUTPUT);
  pinMode(Port_LED3, OUTPUT);
  pinMode(Port_LED4, OUTPUT);
  pinMode(Port_LED5, OUTPUT);
  pinMode(Port_LED6, OUTPUT);

  pinMode(Pin_EncoderA, INPUT);
  pinMode(Pin_EncoderB, INPUT);
  pinMode(Pin_EncoderZ, INPUT);

  pinMode(Pin_APWM, OUTPUT);
  pinMode(Pin_AIN1, OUTPUT);
  pinMode(Pin_AIN2, OUTPUT);

  pinMode(RS485_Ctrl, OUTPUT);

    for (int iChannel = 0; iChannel < 8; iChannel++)
  {
    pinMode(swPins[iChannel], INPUT_PULLUP);
  }
}

void RS485_TxMode(void)
{ digitalWrite(RS485_Ctrl, HIGH);  // 0 = Rx
  delay(50);
}

void RS485_RxMode(void)
{ delay(50);
  digitalWrite(RS485_Ctrl, LOW);  // 0 = Rx
}


//=============================================================
int Read_myID(void) {
  int xAddress = 0;
  xAddress = xAddress * 2 + digitalRead(Port_ID1);
  xAddress = xAddress * 2 + digitalRead(Port_ID2);
  xAddress = xAddress * 2 + digitalRead(Port_ID3);
  xAddress = xAddress * 2 + digitalRead(Port_ID4);
  xAddress = xAddress * 2 + digitalRead(Port_ID5);
  xAddress = xAddress * 2 + digitalRead(Port_ID6);
  xAddress = xAddress * 2 + digitalRead(Port_ID7);
  xAddress = xAddress * 2 + digitalRead(Port_ID8);
  return xAddress ^ 0xff;
}

//=============================================================
void ModeDisplay(void) {
  int Temp = RunSpeed;
  if (RunDirection == 01)
    modeDisp.setRow(0, 7, B11100010);
  else if (RunDirection == 10)
    modeDisp.setRow(0, 7, B10011100);
  else
    modeDisp.setRow(0, 7, 0B10000001);
  modeDisp.setRow(0, 6, 0);

  modeDisp.setDigit(0, 5, my_ID / 16, false);
  modeDisp.setDigit(0, 4, my_ID % 16, true);

  modeDisp.setRow(0, 3, 0);
  modeDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 2, Temp % 10, false);
}

//=============================================================
void nTargetDisplay(void) {
  long int Temp = nTargetCounter;
  modeDisp.setRow(0, 7, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    modeDisp.setRow(0, 7, 1);
  }
  modeDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 2, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 3, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 4, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 5, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 6, Temp % 10, false);
}

//=============================================================
void nRunCountDisplay(void) {
  long int Temp = nNowCounter;
  nCOuntDisp.setRow(0, 7, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    nCOuntDisp.setRow(0, 7, 1);
  }
  nCOuntDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 2, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 3, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 4, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 5, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 6, Temp % 10, false);
}
