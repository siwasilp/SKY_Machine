
//################################################################
// LMove ID 255 99999999<Cr>
void cmd_LMove(void) {
  if (IS_Command(LMove) != 0) {
    Serial.println("cmd_LMove");
    int j = IS_Command(LMove);
    Ctrl_ID = (ArrDataCMD[j + 6] - '0') * 16;
    Ctrl_ID = Ctrl_ID + (ArrDataCMD[j + 7] - '0');
    bool bStatus = (Ctrl_ID == my_ID);
    bStatus = bStatus && (ArrDataCMD[j + 5] == ' ');
    bStatus = bStatus && (ArrDataCMD[j + 8] == ' ');
    bStatus = bStatus && (ArrDataCMD[j + 12] == ' ');
    if (bStatus == true) {
      RunSpeed  = ArrDataCMD[j + 9] - '0';
      RunSpeed  = RunSpeed * 10 + ArrDataCMD[j + 10] - '0';
      RunSpeed  = RunSpeed * 10 + ArrDataCMD[j + 11] - '0';
      nRunStep = ArrDataCMD[j + 13] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 14] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 15] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 16] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 17] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 18] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 19] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 20] - '0';

      nTargetCounter = nRunStep;
      if (nNowCounter == nRunStep) RunDirection = 0;
      if (nNowCounter > nRunStep)  RunDirection = 10;
      if (nNowCounter < nRunStep)  RunDirection = 01;
    }
    Display_RxBuff(j);
    Clear_RxBuff();
  }
}

//=== ERead ID<Cr> ===
void cmd_ERead(void) {
  if (IS_Command(ERead) != 0) {
    Serial.println("cmd_ERead");
    int j = IS_Command(ERead);
    Ctrl_ID = (ArrDataCMD[j + 6] - '0') * 16;
    Ctrl_ID = Ctrl_ID + (ArrDataCMD[j + 7] - '0');
    bool bStatus = (Ctrl_ID == my_ID);
    bStatus = bStatus && (ArrDataCMD[j + 5] == ' ');
    if (bStatus == true) {
      Read_NVRAM();
      Serial.print("Enc.Read = ");
      Serial.print(nNowCounter);
      Serial.print(",");
      if (RunDirection < 10) Serial.print("0");
      Serial.println(RunDirection);
      RS485_TxMode();
      Serial2.print("Enc.Read = ");
      Serial2.print(nNowCounter);
      Serial2.print(",");
      if (RunDirection < 10) Serial2.print("0");
      Serial2.println(RunDirection);
      RS485_RxMode();
    }
    Display_RxBuff(j);
    Clear_RxBuff();
  }
}

//=== GHome ID 255<Cr> ===
void cmd_GHome(void) {
  if (IS_Command(GHome) != 0) {
    Serial.println("cmd_GHome");
    int j = IS_Command(GHome);
    Ctrl_ID = (ArrDataCMD[j + 6] - '0') * 16;
    Ctrl_ID = Ctrl_ID + (ArrDataCMD[j + 7] - '0');
    bool bStatus = (Ctrl_ID == my_ID);
    bStatus = bStatus && (ArrDataCMD[j + 5] == ' ');
    bStatus = bStatus && (ArrDataCMD[j + 8] == ' ');
    if (bStatus == true) {
      RunSpeed = ArrDataCMD[j + 9] - '0';
      RunSpeed = RunSpeed * 10 + ArrDataCMD[j + 10] - '0';
      RunSpeed = RunSpeed * 10 + ArrDataCMD[j + 11] - '0';
      nTargetCounter = 0;
      if (nNowCounter == 0) RunDirection = 0;
      if (nNowCounter > 0)  RunDirection = 10;
      if (nNowCounter < 0)  RunDirection = 01;
    }
    Display_RxBuff(j);
    Clear_RxBuff();
  }
}

//=== SHome ID<CR> ===
void cmd_SHome(void) {
  if (IS_Command(SHome) != 0) {
    Serial.println("cmd_SHome");
    int j = IS_Command(SHome);
    Ctrl_ID = (ArrDataCMD[j + 6] - '0') * 16;
    Ctrl_ID = Ctrl_ID + (ArrDataCMD[j + 7] - '0');
    bool bStatus = (Ctrl_ID == my_ID);
    bStatus = bStatus && (ArrDataCMD[j + 5] == ' ');
    if (bStatus == true) {
      nRunStep = 0;
      nNowCounter = 0;
      nTargetCounter = 0;
      Save_NVRAM();
    }
    Display_RxBuff(j);
    Clear_RxBuff();
  }
}

//=== CMove +ID SPD<CR> ===
void cmd_CMove(void) {
  if (IS_Command(CMove) != 0) {
    Serial.println("cmd_CMove");
    int j = IS_Command(CMove);
    Ctrl_ID = (ArrDataCMD[j + 7] - '0') * 16;
    Ctrl_ID = Ctrl_ID + (ArrDataCMD[j + 8] - '0');
    bool bStatus = (Ctrl_ID == my_ID);
    bStatus = bStatus && (ArrDataCMD[j + 5] == ' ');
    bStatus = bStatus && (ArrDataCMD[j + 9] == ' ');
    if (bStatus == true) {
      if (ArrDataCMD[j + 6] == '+')  RunDirection = 01;
      if (ArrDataCMD[j + 6] == '-')  RunDirection = 10;
      RunSpeed  = ArrDataCMD[j + 10] - '0';
      RunSpeed  = RunSpeed * 10 + ArrDataCMD[j + 11] - '0';
      RunSpeed  = RunSpeed * 10 + ArrDataCMD[j + 12] - '0';
      nRunStep = 0;
      if (RunDirection == 01)  nTargetCounter = +99999999;
      if (RunDirection == 10)  nTargetCounter = -99999999;
    }
    Display_RxBuff(j);
    Clear_RxBuff();
  }
}

//=== PMove +ID SPD PPPPPPPP<CR> ===
void cmd_PMove(void) {
  if (IS_Command(PMove) != 0) {
    Serial.println("cmd_PMove");
    int j = IS_Command(PMove);
    Ctrl_ID = (ArrDataCMD[j + 7] - '0') * 16;
    Ctrl_ID = Ctrl_ID + (ArrDataCMD[j + 8] - '0');
    bool bStatus = (Ctrl_ID == my_ID);
    bStatus = bStatus && (ArrDataCMD[j + 5] == ' ');
    bStatus = bStatus && (ArrDataCMD[j + 9] == ' ');
    bStatus = bStatus && (ArrDataCMD[j + 13] == ' ');
    if (bStatus == true) {
      if (ArrDataCMD[j + 6] == '+')  RunDirection = 01;
      if (ArrDataCMD[j + 6] == '-')  RunDirection = 10;
      RunSpeed  = ArrDataCMD[j + 10] - '0';
      RunSpeed  = RunSpeed * 10 + ArrDataCMD[j + 11] - '0';
      RunSpeed  = RunSpeed * 10 + ArrDataCMD[j + 12] - '0';
      nRunStep = ArrDataCMD[j + 14] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 15] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 16] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 17] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 18] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 19] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 20] - '0';
      nRunStep = nRunStep * 10 + ArrDataCMD[j + 21] - '0';
      if (RunDirection == 10)  nRunStep = nRunStep * -1;
      nTargetCounter = nNowCounter + nRunStep;
      if (nTargetCounter > 99999999)  nTargetCounter = 99999999;
      if (nTargetCounter < -99999999) nTargetCounter = -99999999;
    }
    Display_RxBuff(j);
    Clear_RxBuff();
  }
}

void cmd_AStop(void) {
  if (IS_Command(AStop) != 0)  {
    RunDirection = 0;
    Save_NVRAM();
    Serial.println("cmd_AStop");
    Clear_RxBuff();
  }
}

void cmd_Start(void) {
  if (IS_Command(Start) != 0)
  { Save_NVRAM();
    Serial.println("cmd_Start");
    Clear_RxBuff();
  }
}

//###########################################################################
void Display_RxBuff(int x) {
  for (int i = 0; i < (nBuffer - x); i++)
    Serial.print(ArrDataCMD[x + i]);
  Serial.print("\n>> Dir = ");  Serial.print(RunDirection);
  Serial.print(", my_ID = ");   Serial.print(my_ID, HEX);
  Serial.print(", ctrl_ID = "); Serial.print(Ctrl_ID, HEX);
  Serial.print(", rSpeed = ");  Serial.print(RunSpeed);
  Serial.print(", Step = ");    Serial.print(nRunStep);
  Serial.print(", Target = ");  Serial.print(nTargetCounter);
  Serial.println();
}

void Clear_RxBuff(void) {
  for (int i = 0; i < nBuffer; i++)
    ArrDataCMD[i] = 0;
}

int IS_Command(String searchString) {
  int result = 0;
 
  for (int i = 0; i < nBuffer; i++) {
    bool bCheck = true;
    bCheck = bCheck && (searchString[0] == ArrDataCMD[i]);
    bCheck = bCheck && (searchString[1] == ArrDataCMD[i + 1]);
    bCheck = bCheck && (searchString[2] == ArrDataCMD[i + 2]);
    bCheck = bCheck && (searchString[3] == ArrDataCMD[i + 3]);
    bCheck = bCheck && (searchString[4] == ArrDataCMD[i + 4]);
    if (bCheck == true) {
      result = i;
      i = nBuffer + 5;
    }
  }
  return result;

}

void Help(void) {
  Serial.println("================================");
  Serial.println("--------------------------------");
  Serial.println(" PMove +ID 255 99999999<Cr>");
  Serial.println(" CMove +ID 255<Cr>");
  Serial.println(" LMove ID 255 99999999<Cr>");
  Serial.println(" GHome ID 255<Cr>");
  Serial.println(" SHome ID<Cr>");
  Serial.println(" ERead ID<Cr>");
  Serial.println(" AStop<Cr>");
  Serial.println(" Start<Cr>");
  Serial.println("--------------------------------");
  Clear_RxBuff();
}
