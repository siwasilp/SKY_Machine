
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

void setup() {
  Port_Initial();
  All_LED_Off();
  my_ID = Read_myID();
  Serial.begin(9600);
  Serial2.begin(9600);
  Init_All7SegDisplay();
  Pack_myData();

  Serial.print("ID(Hex) = ");
  Serial.print(my_ID,HEX);
  Serial.print(",Data = ");
  Serial.println(myData);
  
  RS485_TxMode();

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
