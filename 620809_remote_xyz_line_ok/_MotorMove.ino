void EncoderCount() {
  cli();  //stop interrupts happening before we read pin values
  nNowCounter = nNowCounter + directionCount;
  sei();  //restart interrupts
}
//=============================================================
void DC_MotorControl(void) {
  if (RunDirection == 10)   {
    digitalWrite(Port_LED5, LOW);     // 1=On
    digitalWrite(Port_LED6, HIGH);    // 0=Off
    digitalWrite(Pin_AIN1, LOW);
    digitalWrite(Pin_AIN2, HIGH);
    analogWrite(Pin_APWM, RunSpeed);
    directionCount = -1;
  }
  else if (RunDirection == 01) {
    digitalWrite(Port_LED5, HIGH);    // 0=Off
    digitalWrite(Port_LED6, LOW);     // 0=On
    digitalWrite(Pin_AIN1, HIGH);
    digitalWrite(Pin_AIN2, LOW);
    analogWrite(Pin_APWM, RunSpeed);
    directionCount = +1;
  }
  else {
    digitalWrite(Port_LED5, HIGH);  // 1=Off
    digitalWrite(Port_LED6, HIGH);  // 1=Off
    digitalWrite(Pin_AIN1, HIGH);
    digitalWrite(Pin_AIN2, HIGH);
    digitalWrite(Pin_APWM, LOW);
    directionCount = 0;
  }
}


//=============================================================
void Go_Move(void) {
  RunSpeed = 200;
  RunDirection = 01;
  nTargetCounter = +99999999;
  DC_MotorControl();
  Save_NVRAM();
  Serial.println("cmd_Force Go");
  while (digitalRead(Port_Sw4) == LOW) {
    nTargetDisplay();
    nRunCountDisplay();
    delay(100);
  }
  RunDirection = 0;
  DC_MotorControl();
}

//=============================================================
void Back_Move(void) {
  RunSpeed = 200;
  RunDirection = 10;
  nTargetCounter = -99999999;
  DC_MotorControl();
  Save_NVRAM();
  Serial.println("cmd_Force Back");
  while (digitalRead(Port_Sw1) == LOW) {
    nTargetDisplay();
    nRunCountDisplay();
    delay(100);
  }
  RunDirection = 0;
  DC_MotorControl();
}
