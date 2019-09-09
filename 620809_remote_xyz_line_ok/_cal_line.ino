void cal_line() {
  if(x<=0)x=0;
  if(x>=limit_x)x=limit_x;
  if(y<=0)y=0;
  if(y>=limit_y)y=limit_y;
  if(z<=0)z=0;
  if(z>=limit_z)z=limit_z;
  //====================================
  int l1a[] = {x , y , z} ;
  int l1b[] = {0, 0, zzz};
  int l1c[] = {0, 0, 0};
  for (int i = 0 ; i < 3 ; i++) {
    l1c[ i ] = l1b[ i ] - l1a[ i ];
  }
  line_a = sqrt(l1c[0] * l1c[0] + l1c[1] * l1c[1] + l1c[2] * l1c[2]);

  int l2a[] = {x , y , z} ;
  int l2b[] = {0, yyy, zzz};
  int l2c[] = {0, 0, 0};
  for (int i = 0 ; i < 3 ; i++) {
    l2c[ i ] = l2b[ i ] - l2a[ i ];
  }
  line_b = sqrt(l2c[0] * l2c[0] + l2c[1] * l2c[1] + l2c[2] * l2c[2]);

  int l3a[] = {x , y , z} ;
  int l3b[] = {xxx, yyy, zzz};
  int l3c[] = {0, 0, 0};
  for (int i = 0 ; i < 3 ; i++) {
    l3c[ i ] = l3b[ i ] - l3a[ i ];
  }
  line_c = sqrt(l3c[0] * l3c[0] + l3c[1] * l3c[1] + l3c[2] * l3c[2]);

  int l4a[] = {x , y , z} ;
  int l4b[] = {xxx, 0, zzz};
  int l4c[] = {0, 0, 0};
  for (int i = 0 ; i < 3 ; i++) {
    l4c[ i ] = l4b[ i ] - l4a[ i ];
  }
  line_d = sqrt(l4c[0] * l4c[0] + l4c[1] * l4c[1] + l4c[2] * l4c[2]);




  Serial.print(" || A : "); Serial.print(line_a);
  Serial.print(" B : ");    Serial.print(line_b);
  Serial.print(" C : ");    Serial.print(line_c);
  Serial.print(" D : ");    Serial.print(line_d);
  Serial.println();

}
