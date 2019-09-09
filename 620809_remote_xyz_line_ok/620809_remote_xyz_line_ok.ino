#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);
#include "_portAssign.c"
#include "LedControl.h"
#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68

#define PMove "PMove"  // PMove +ID 255 99999999<Cr>
#define CMove "CMove"  // CMove +ID 255<Cr>
#define LMove "LMove"  // LMove ID 255 99999999<Cr>
#define GHome "GHome"  // GHome ID 255<Cr>
#define SHome "SHome"  // SHome ID<Cr>
#define ERead "ERead"  // ERead ID<Cr>
#define AStop "AStop"  // AStop<Cr>
#define Start "Start"  // Start<Cr>
#define nBuffer 23

LedControl modeDisp = LedControl(Port_UpDIN, Port_UpCLK, Port_UpEN, 1);
LedControl nCOuntDisp = LedControl(Port_DwDIN, Port_DwCLK, Port_DwEN, 1);

volatile long int nNowCounter = 0;
volatile int directionCount = 0;
long int nTargetCounter, nRunStep;
int RunDirection = 0, my_ID, Ctrl_ID = 0, RunSpeed = 500;
char ArrDataCMD[nBuffer + 1];

bool HeartBeat, SrlBeat;
unsigned int loopCnt;

//###############################################################

int rcPins[6] = {A0, A2, A4, A6, A8, A10};
float chValue[6];

int swPins[8] = {A15, A13, A11, A9, A7, A5, A3, A1};
int swValue[8];

float r_x, r_y, r_z, r_drop, r_mode, r_speedx;
float x, y, z, drop, mode, speedx = 0;

const int pulseInDelay = 30000;


//###############################################################
float line_a, line_b, line_c, line_d = 0;

int xxx = 140;
int yyy = 86;
int zzz = 0;

int limit_x = 140;
int limit_y = 86;
int limit_z = 12;

int sen = 0;
//###############################################################
void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Port_Initial();
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("1/3 DS1307 Connecting .........");
  Wire.begin();
  setDS1307time(1, 2, 3, 4, 11, 12, 18);  //SS,MM,HH,Dy,Dt,Mt,Yr
  Start_DS1307();   // Start DS1307-RTC
  Read_NVRAM();     // nNowCounter
  Serial.println("2/3 Display .........");
  modeDisp.shutdown(0, false);
  modeDisp.setIntensity(0, 8);
  modeDisp.clearDisplay(0);
  nCOuntDisp.shutdown(0, false);
  nCOuntDisp.setIntensity(0, 8);
  nCOuntDisp.clearDisplay(0);
  my_ID = Read_myID();
  RunDirection = 0;
  ModeDisplay();
  nRunCountDisplay();
  attachInterrupt(5, EncoderCount, RISING);
  Serial.println("3/3 Ready .........");
  RS485_RxMode();
}

//############################################################
void loop() {
  remote();
  disp_remote();
  cal_line();

  if (r_drop == 0 && sen == 0) {
    disp_line();
    RS485_TxMode();
    Serial.println("Sent_232");
    sent();
    delay(2000);
    Serial.println("Start...");
    Serial2.print("Start\r\n");
    RS485_RxMode();
    sen = 1;
  }
  if(r_drop == 1){sen=0;}

}
//############################################################
