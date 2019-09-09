
void Save_NVRAM(void) {
  long int  Temp = nNowCounter;
  byte TT = Temp % 100;    Temp = Temp / 100;
  byte UU = Temp % 100;    Temp = Temp / 100;
  byte SS = Temp % 100;    Temp = Temp / 100;
  byte XX = Temp % 100;
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(10); // Start Address Save
  Wire.write(XX); // set X
  Wire.write(SS); // set S
  Wire.write(UU); // set U
  Wire.write(TT); // set T
  Wire.endTransmission();
  Serial.print("Save == ");
  Serial.print(nNowCounter);
  Serial.print(" >> "); Serial.print(XX);
  Serial.print("-");    Serial.print(SS);
  Serial.print("-");    Serial.print(UU);
  Serial.print("-");    Serial.println(TT);
}

void Read_NVRAM(void) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(10); // Start Address Save
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 4);
  byte XX = Wire.read(); // read X
  byte SS = Wire.read(); // read S
  byte UU = Wire.read(); // read U
  byte TT = Wire.read(); // read T
  nNowCounter = XX * 1000000 + SS * 10000 + UU * 100 + TT;
  Serial.print("Read = ");
  Serial.println(nNowCounter);
  Serial.print(" >> "); Serial.print(XX);
  Serial.print("-");    Serial.print(SS);
  Serial.print("-");    Serial.print(UU);
  Serial.print("-");    Serial.println(TT);
}

byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

void Start_DS1307(void) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(7); // set next input to start at the seconds register
  Wire.write(0xff); // set data
  Wire.endTransmission();
}

void setDS1307time(byte SS, byte MM, byte HH, byte Dy, byte Dt, byte Mt, byte Yr) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(SS)); // set seconds
  Wire.write(decToBcd(MM)); // set minutes
  Wire.write(decToBcd(HH)); // set hours
  Wire.write(decToBcd(Dy)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(Dt)); // set date (1 to 31)
  Wire.write(decToBcd(Mt)); // set month
  Wire.write(decToBcd(Yr)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS1307time(byte *SS, byte *MM, byte *HH, byte *Dy, byte *Dt, byte *Mt, byte *Yr) {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  *SS = bcdToDec(Wire.read() & 0x7f); // read seconds
  *MM = bcdToDec(Wire.read());  // read minutes
  *HH = bcdToDec(Wire.read() & 0x3f); // read hours
  *Dy = bcdToDec(Wire.read());  // read day of week (1=Sunday, 7=Saturday)
  *Dt = bcdToDec(Wire.read());  // read date (1 to 31)
  *Mt = bcdToDec(Wire.read());  // read month
  *Yr = bcdToDec(Wire.read());  // read year (0 to 99)
}

#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(void) {
  char datestring[20];
  byte SS, MM, HH, Dy, Dt, Mt, Yr;
  readDS1307time(&SS, &MM, &HH, &Dy, &Dt, &Mt, &Yr);
  snprintf_P(datestring, countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             Dt, Mt, 2000 + Yr, HH, MM, SS);
  Serial.println(datestring);
}

void displayTime() {
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS1307time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute < 10)     Serial.print("0");
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10)  Serial.print("0");
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch (dayOfWeek) {
    case 1:
      Serial.print("Sunday");
      break;
    case 2:
      Serial.print("Monday");
      break;
    case 3:
      Serial.print("Tuesday");
      break;
    case 4:
      Serial.print("Wednesday");
      break;
    case 5:
      Serial.print("Thursday");
      break;
    case 6:
      Serial.print("Friday");
      break;
    case 7:
      Serial.print("Saturday");
      break;
  }
  Serial.println();
}
