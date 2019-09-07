
#include "LedControl.h"
#include "_portAssign.C"
#define nBuffer 23

int testCounter;
int RunDirection = 0, my_ID;
char U_DispBuff[8], L_DispBuff[8];
char ArrDataCMD[nBuffer + 1];

long int myData, StepUpdateData = 11111111;

LedControl modeDisp = LedControl(Port_UpDIN, Port_UpCLK, Port_UpEN, 1);
LedControl nCOuntDisp = LedControl(Port_DwDIN, Port_DwCLK, Port_DwEN, 1);

#include "_01System.C"

void Help(void) {
  Serial.println("==============================");
  Serial.println(" RS485 = 9600, RS232 = 115200 ");
  Serial.println("------------------------------");
  Serial.println("xxxxxxxxWID<Cr> = Write ID");
  Serial.println("RID<Cr> = Read ID");
  Serial.println("UID<Cr> = Update ID");
  Serial.println("------------------------------");
  Serial.print("My ID = 0x");
  if (my_ID < 0x0f) Serial.print("0");
  Serial.println(my_ID, HEX);
  Serial.println("==============================");
}

void Pack_myData(void) {
  myData = L_DispBuff[7] % 10;
  myData = myData * 10 + (L_DispBuff[6] % 10);
  myData = myData * 10 + (L_DispBuff[5] % 10);
  myData = myData * 10 + (L_DispBuff[4] % 10);
  myData = myData * 10 + (L_DispBuff[3] % 10);
  myData = myData * 10 + (L_DispBuff[2] % 10);
  myData = myData * 10 + (L_DispBuff[1] % 10);
  myData = myData * 10 + (L_DispBuff[0] % 10);
}

void UnPack_myData(void) {
  L_DispBuff[0] = myData % 10;  myData /= 10;
  L_DispBuff[1] = myData % 10;  myData /= 10;
  L_DispBuff[2] = myData % 10;  myData /= 10;
  L_DispBuff[3] = myData % 10;  myData /= 10;
  L_DispBuff[4] = myData % 10;  myData /= 10;
  L_DispBuff[5] = myData % 10;  myData /= 10;
  L_DispBuff[6] = myData % 10;  myData /= 10;
  L_DispBuff[7] = myData % 10;
}

void Write_Data(void) {
  Serial.println("Write_Data");
  for (int i = 0; i < 8; i++)
    L_DispBuff[i] = ArrDataCMD[nBuffer - 4 - i] & 0xf;
  LowerDisplay();
}

void Read_Data(void) {
  Serial.println("Read_Data");
  Pack_myData();
  Serial.println(myData);
  RS485_TxMode();
  Serial2.print("ID = ");
  Serial2.print(my_ID,HEX);
  Serial2.print(",Data = ");
  Serial2.println(myData);
  RS485_RxMode();
}

void Incress_Data(void) {
  Serial.println("Incress_Data");
  Pack_myData();
  Serial.println(myData);
  myData = myData + StepUpdateData;
  Serial.println(myData);
  UnPack_myData();
  LowerDisplay();
}


void UpdateData(void) {
  for (int i = 0; i < 8; i++)
    U_DispBuff[i] = ArrDataCMD[nBuffer - i] & 0xf;
  UpperDisplay();
  if (ArrDataCMD[nBuffer] == 0x0d) {
    int temp_ID = ArrDataCMD[nBuffer - 2] & 0xf;
    temp_ID = temp_ID * 16 + (ArrDataCMD[nBuffer - 1] & 0xf);
    //Serial.println(temp_ID, HEX);
    if (temp_ID == my_ID) {
      if ((ArrDataCMD[nBuffer - 3] == 'W') || (ArrDataCMD[nBuffer - 3] == 'w'))  Write_Data();
      if ((ArrDataCMD[nBuffer - 3] == 'R') || (ArrDataCMD[nBuffer - 3] == 'r'))  Read_Data();
      if ((ArrDataCMD[nBuffer - 3] == 'U') || (ArrDataCMD[nBuffer - 3] == 'u'))  Incress_Data();
    }
  }
}



void setup() {
  Port_Initial();
  All_LED_Off();
  my_ID = Read_myID();
  Serial.begin(115200);
  Serial2.begin(9600);
  Init_All7SegDisplay();
  Pack_myData();

  Serial.print("ID(Hex) = ");
  Serial.print(my_ID,HEX);
  Serial.print(",Data = ");
  Serial.println(myData);
  
  RS485_TxMode();
  Serial2.print("CMove +11 100 \r\n");
  Serial2.print("Start \r\n");      
  RS485_RxMode();
}

void loop() {
 
  if (Serial.available()) {
    for (int i = 0; i < nBuffer; i++)
      ArrDataCMD[i] = ArrDataCMD[i + 1];
    ArrDataCMD[nBuffer] = Serial.read();
    if (ArrDataCMD[nBuffer] == '?') Help();
    else UpdateData();
  }

  if (Serial2.available()) {
    for (int i = 0; i < nBuffer; i++)
      ArrDataCMD[i] = ArrDataCMD[i + 1];
    ArrDataCMD[nBuffer] = Serial2.read();
    UpdateData();
  }
}
