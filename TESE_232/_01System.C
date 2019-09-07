

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
}

void RS485_TxMode(void)
{ digitalWrite(RS485_Ctrl, HIGH);   // 0 = Rx
  delay(50);
}

void RS485_RxMode(void)
{ delay(50);
  digitalWrite(RS485_Ctrl, LOW);    // 0 = Rx
}

void All_LED_Off(void) {
  digitalWrite(Port_LED1, HIGH);
  digitalWrite(Port_LED2, HIGH);
  digitalWrite(Port_LED3, HIGH);
  digitalWrite(Port_LED4, HIGH);
  digitalWrite(Port_LED5, HIGH);
  digitalWrite(Port_LED6, HIGH);
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
//=============================================================
void UpperDisplay(void) {
  modeDisp.setDigit(0, 0, U_DispBuff[0], false);
  modeDisp.setDigit(0, 1, U_DispBuff[1], false);
  modeDisp.setDigit(0, 2, U_DispBuff[2], false);
  modeDisp.setDigit(0, 3, U_DispBuff[3], false);
  modeDisp.setDigit(0, 4, U_DispBuff[4], false);
  modeDisp.setDigit(0, 5, U_DispBuff[5], false);
  modeDisp.setDigit(0, 6, U_DispBuff[6], false);
  modeDisp.setDigit(0, 7, U_DispBuff[7], false);
}

void LowerDisplay(void) {
  nCOuntDisp.setDigit(0, 0, L_DispBuff[0], false);
  nCOuntDisp.setDigit(0, 1, L_DispBuff[1], false);
  nCOuntDisp.setDigit(0, 2, L_DispBuff[2], false);
  nCOuntDisp.setDigit(0, 3, L_DispBuff[3], false);
  nCOuntDisp.setDigit(0, 4, L_DispBuff[4], false);
  nCOuntDisp.setDigit(0, 5, L_DispBuff[5], false);
  nCOuntDisp.setDigit(0, 6, L_DispBuff[6], false);
  nCOuntDisp.setDigit(0, 7, L_DispBuff[7], false);
}

void Init_All7SegDisplay(void) {
  modeDisp.shutdown(0, false);
  modeDisp.setIntensity(0, 2);
  modeDisp.clearDisplay(0);
  nCOuntDisp.shutdown(0, false);
  nCOuntDisp.setIntensity(0, 2);
  nCOuntDisp.clearDisplay(0);

  U_DispBuff[7] = 1;
  U_DispBuff[6] = 2;
  U_DispBuff[5] = 3;
  U_DispBuff[4] = 4;
  U_DispBuff[3] = 5;
  U_DispBuff[2] = 6;
  U_DispBuff[1] = 7;
  U_DispBuff[0] = 8;
  UpperDisplay();

  L_DispBuff[7] = 1;
  L_DispBuff[6] = 2;
  L_DispBuff[5] = 3;
  L_DispBuff[4] = 4;
  L_DispBuff[3] = 5;
  L_DispBuff[2] = 6;
  L_DispBuff[1] = 7;
  L_DispBuff[0] = 8;
  LowerDisplay();
}
