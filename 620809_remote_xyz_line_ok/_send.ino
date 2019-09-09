void sent() {

  int ss = map(speedx,0,100,0,255);
  String sp = (String)ss;
  
  if (ss >= 100) {
    sp=""+sp;
  }
  else if (ss >= 10) {
    sp="0"+sp;
  }
  else{
    sp="00"+sp;
  }

  
//=============== Line A ==================================================
 
  if (line_a >= 1000) {
    Serial2.print("LMove 11 "+sp+" 0000");
    Serial2.print((int)line_a); Serial2.print("\r\n");
  }
  
  else if (line_a >= 100) {
    Serial2.print("LMove 11 "+sp+" 00000");
    Serial2.print((int)line_a); Serial2.print("\r\n");
  }
  
  else if (line_a >= 10) {
    Serial2.print("LMove 11 "+sp+" 000000");
    Serial2.print((int)line_a); Serial2.print("\r\n");
  }

  else {
    Serial2.print("LMove 11 "+sp+" 0000000");
    Serial2.print((int)line_a);  Serial2.print("\r\n");
  }

  //=============== Line B ==================================================
  if (line_b >= 1000) {
    Serial2.print("LMove 12 "+sp+" 0000");
    Serial2.print((int)line_b); Serial2.print("\r\n");
  }

  else if (line_b >= 100) {
    Serial2.print("LMove 12 "+sp+" 00000");
    Serial2.print((int)line_b); Serial2.print("\r\n");
  }

  else if (line_b >= 10) {
    Serial2.print("LMove 12 "+sp+" 000000");
    Serial2.print((int)line_b); Serial2.print("\r\n");
  }

  else {
    Serial2.print("LMove 12 "+sp+" 0000000");
    Serial2.print((int)line_b);  Serial2.print("\r\n");
  }

  //=============== Line C ==================================================

  if (line_c >= 1000) {
    Serial2.print("LMove 13 "+sp+" 0000");
    Serial2.print((int)line_c); Serial2.print("\r\n");
  }

  else if (line_c >= 100) {
    Serial2.print("LMove 13 "+sp+" 00000");
    Serial2.print((int)line_c); Serial2.print("\r\n");
  }

  else if (line_c >= 10) {
    Serial2.print("LMove 13 "+sp+" 000000");
    Serial2.print((int)line_c); Serial2.print("\r\n");
  }

  else {
    Serial2.print("LMove 13 "+sp+" 0000000");
    Serial2.print((int)line_c);  Serial2.print("\r\n");
  }



  //=============== Line D ==================================================

  if (line_d >= 1000) {
    Serial2.print("LMove 14 "+sp+" 0000");
    Serial2.print((int)line_d); Serial2.print("\r\n");
  }

  else if (line_d >= 100) {
    Serial2.print("LMove 14 "+sp+" 00000");
    Serial2.print((int)line_d); Serial2.print("\r\n");
  }

  else if (line_d >= 10) {
    Serial2.print("LMove 14 "+sp+" 000000");
    Serial2.print((int)line_d); Serial2.print("\r\n");
  }

  else {
    Serial2.print("LMove 14 "+sp+" 0000000");
    Serial2.print((int)line_d);  Serial2.print("\r\n");
  }
}


void disp_line() {
  int   Temp = line_b;
  modeDisp.setRow(0, 3, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    modeDisp.setRow(0, 3, 1);
  }
  modeDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 2, Temp % 10, false);

  Temp = line_d;
  nCOuntDisp.setRow(0, 3, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    nCOuntDisp.setRow(0, 3, 1);
  }
  nCOuntDisp.setDigit(0, 0, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 1, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 2, Temp % 10, false);

  Temp = line_c;
  nCOuntDisp.setRow(0, 7, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    nCOuntDisp.setRow(0, 7, 1);
  }
  nCOuntDisp.setDigit(0, 4, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 5, Temp % 10, false);  Temp /= 10;
  nCOuntDisp.setDigit(0, 6, Temp % 10, false);

  Temp = line_a;
  modeDisp.setRow(0, 7, 0);
  if (Temp < 0) {
    Temp = Temp * -1;
    modeDisp.setRow(0, 7, 1);
  }
  modeDisp.setDigit(0, 4, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 5, Temp % 10, false);  Temp /= 10;
  modeDisp.setDigit(0, 6, Temp % 10, false);
}
