#include <LiquidCrystal.h>
#include <EEPROM.h>

/******* LCD PINS DECLARATION     **************************************************/
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


/******* VARIABLES USED IN THE PROJECT DECLARATIONSDECLARATION     **************************************************/
int pulse = 0;
int p2 = 0;
int unit = 0;
int w = 0;
int date = 1;

/******* SWITCHES PINS DECLARATION     **************************************************/
int sw1 = 5;
int sw2 = 4;
int sw3 = 3;

/******* DAYWISE UNITS DECLARATION     **************************************************/
int d1n = 0;  // DAY 1 NORMAL UNITS
int d1p1 = 0; // DAY 1 PEAK 1 UNITS --> D1P1
int d1p2 = 0; // DAY 1 PEAK 2 UNITS --> D2P2

int d2n = 0;
int d2p1 = 0;
int d2p2 = 0;

int d3n = 0;
int d3p1 = 0;
int d3p2 = 0;

int d4n = 0;
int d4p1 = 0;
int d4p2 = 0;

int d5n = 0;
int d5p1 = 0;
int d5p2 = 0;

/******* SWITCH DECLARATION FOR CHANGING DAY NUMBER    **************************************************/
int tact = 2;  // day selector


/******* GENERAL PURPOSE VARIABLES DECLARATION USED IN PROGRAM    **************************************************/
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int flag7 = 0;
int flag8 = 0;
int flag9 = 0;
int flag10 = 0;
int flag11 = 0;
int flag12 = 0;
int flag13 = 0;
int flag14 = 0;
int flag15 = 0;
int flag_c = 0;

/******* CLEAR ALL CONDITIONS **************************************************/
void flag()
{
 flag1 = 0;
 flag2 = 0;
 flag3 = 0;
 flag4 = 0;
 flag5 = 0;
 flag6 = 0;
 flag7 = 0;
 flag8 = 0;
 flag9 = 0;
 flag10 = 0;
 flag11 = 0;
 flag12 = 0;
 flag13 = 0;
 flag14 = 0;
 flag15 = 0; 
}

/******* CLEAR EEPROM FROM ALL PREVIOUSLY SAVED READINGS, DONE WHEN BILL IS GENERATED**************************************************/
void clear_e()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Clearing Data......");
  pulse = 0;
  d1n = 0; d2n = 0; d3n = 0; d4n = 0; d5n = 0;
  d1p1 = 0; d2p1 = 0; d3p1 = 0; d4p1 = 0; d5p1 = 0;
  d1p2 = 0; d2p2 = 0; d3p2 = 0; d4p2 = 0; d5p2 = 0;
  
  for(int s=11; s<=50; s++)
  {
    delay(10);
    pulse = 0;
    EEPROM.write(s, pulse);
    delay(20);
  }
  
  d1n = 0; d2n = 0; d3n = 0; d4n = 0; d5n = 0;
  d1p1 = 0; d2p1 = 0; d3p1 = 0; d4p1 = 0; d5p1 = 0;
  d1p2 = 0; d2p2 = 0; d3p2 = 0; d4p2 = 0; d5p2 = 0;

  lcd.setCursor(0,1);
  lcd.print("Done.........");
  delay(2000);
  lcd.clear();
}


/******* READ ALL VALUES STORED IN EEPROM ONCE EVERYTIME THE SYSTEM POWERS ON **************************************************/
void read_eeprom()
{
  delay(10); d1n = EEPROM.read(20); delay(20);
  delay(10); d1p1 = EEPROM.read(21); delay(20);
  delay(10); d1p2 = EEPROM.read(22); delay(20);

  delay(10); d2n = EEPROM.read(23); delay(20);
  delay(10); d2p1 = EEPROM.read(24); delay(20);
  delay(10); d2p2 = EEPROM.read(25); delay(20);

  delay(10); d3n = EEPROM.read(26); delay(20);
  delay(10); d3p1 = EEPROM.read(27); delay(20);
  delay(10); d3p2 = EEPROM.read(28); delay(20);

  delay(10); d4n = EEPROM.read(29); delay(20);
  delay(10); d4p1 = EEPROM.read(30); delay(20);
  delay(10); d4p2 = EEPROM.read(31); delay(20);

  delay(10); d5n = EEPROM.read(32); delay(20);
  delay(10); d5p1 = EEPROM.read(33); delay(20);
  delay(10); d5p2 = EEPROM.read(34); delay(20);
}

/******* PRINT THE DAY NO ON LCD**************************************************/
void day() 
{
  delay(10);
  flag_c = 0;
  delay(50);
  date = EEPROM.read(10);
  delay(20);
  date = date + 1;
  if(date > 5) date = 1;
  if(date <= 1) date = 1;
  delay(10);
  EEPROM.write(10, date);
  delay(20);
  lcd.clear();
  delay(100);
  lcd.setCursor(3,0);
  lcd.print("Day  ");
  lcd.setCursor(8,0);
  lcd.print(date);
  delay(2500);
  lcd.clear();
}

/***********LCD FUNCTION FOR PRINTING INTEGER VALUES *****/
void lcd_print(char col, char row, unsigned int value, int digits)
{
                unsigned int temp;
                unsigned int unit;
                unsigned int tens;
                unsigned int hundred;
                unsigned int thousand;
                unsigned int million;
                unsigned char flag=0;

                lcd.setCursor(col,row);
                
                if(digits==5 || flag==1)
                {
                                million=value/10000+48;
                                lcd.write(million);
                                flag=1;
                }
                if(digits==4 || flag==1)
                {
                                temp = value/1000;
                                thousand = temp%10 + 48;
                                lcd.write(thousand);
                                flag=1;
                }
                if(digits==3 || flag==1)
                {
                                temp = value/100;
                                hundred = temp%10 + 48;
                                lcd.write(hundred);
                                flag=1;
                }
                if(digits==2 || flag==1)
                {
                                temp = value/10;
                                tens = temp%10 + 48;
                                lcd.write(tens);
                                flag=1;
                }
                if(digits==1 || flag==1)
                {
                                unit = value%10 + 48;
                                lcd.write(unit);
                }
                if(digits>5)
                {
                                lcd.write('E');
                }        
}
/****** CHECK THE PULSES IF THEY'RE  ********/
void check()
{
  if(pulse >= 50)
   {
     unit = unit + 1;
     delay(10);
     EEPROM.write(1, unit);
     delay(100);
     pulse = 0;
     delay(100);
    }
    delay(100);
    w = unit * 1000;
    delay(200);
}

/******* INTERRUPT SETUP FOR PULE COUNTING  **************************************************/
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}


/******* INTERRUPT FUNCTION WHICH IS CALLED AUTOMATICALLY WHEN PULSE IS DETECTED **************************************************/
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
   if(digitalRead(sw1) != HIGH || digitalRead(sw2) != HIGH || digitalRead(sw3) != HIGH)
   {
     flag_c = 0;
     p2 = p2 + 1;
     delay(10);
     //EEPROM.write(0, pulse);
     delay(20); 
   }
 }  

void setup() 
{
  Serial.begin(
);
  pinMode(A2,INPUT);
  pinMode(tact,INPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(sw3,INPUT);
  delay(1000);
  digitalWrite(tact, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Demand Side EM");
  lcd.setCursor(1,1);
  lcd.print("Using LabView");
  delay(2000);
  
  lcd.clear();
  delay(10);
  date = EEPROM.read(10);
  delay(20);
  lcd.setCursor(3,0);
  lcd.print("Day  ");
  lcd.setCursor(8,0);
  lcd.print(date);
  delay(500);
  read_eeprom();
  delay(500);

  /*delay(30);
  EEPROM.write(0, pulse);
  delay(30);
  EEPROM.write(1, unit);
  delay(30);
  EEPROM.write(2, w);
  delay(30);
  
  delay(10);
  pulse = EEPROM.read(0);
  delay(30);
  unit = EEPROM.read(1);
  delay(30);
  w = EEPROM.read(2);
  delay(30);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pulse: ");
  lcd.setCursor(7,0);
  lcd.print(pulse);
  
  lcd.setCursor(0,1);
  lcd.print("Unit:");
  lcd.setCursor(5,1);
  lcd.print(unit);

  lcd.setCursor(9,1);
  lcd.print("W:");
  lcd.setCursor(11,1);
  lcd.print(w);
  lcd.setCursor(15,1);
  lcd.print("W");*/
  delay(500);
  pciSetup(A2);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), day, FALLING);  
  lcd.clear();
}

void loop()
{
  pulse = p2 / 2;   // READING IS INCREMENTED TWICE EVERY PULSE RECEIVED HENCE, READING IS DIVIDED BY 2
  //lcd.clear();
  date = EEPROM.read(10);
  delay(20);
  lcd.setCursor(0,0);
  lcd.print("Day=");
  lcd.setCursor(4,0);
  lcd.print(date);

  if(digitalRead(tact) == LOW)
  {
    delay(2000);
    if(digitalRead(tact) == LOW)
    {
      day();
      delay(500);
    }
    
  }

  if(Serial.available() > 0)  // CHECK IF SOMETHING IS RECEIVED FROM SERIAL PORT
  {
    char rx = Serial.read();

    if(rx == 'C' || rx == 'c') clear_e();   // IF CHARACTER 'C' IS RECEIVED, THEN CLEAR EVERYTHING, THIS HAPPENS WHEN BILL IS GENERATED
  }
  
  if(date == 1 && flag_c == 0)  // if day is 1 and if there is pulse
  {
    
    if(digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH && digitalRead(sw3) == HIGH) // for normal mode
    {
      if(flag1 == 0) { p2 = 0; pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d1n = EEPROM.read(20);  
      delay(15);
      d1n = d1n + pulse; pulse = 0;
      delay(10);
      EEPROM.write(20, d1n);
      delay(15);
      flag();
      flag1 = 10;
      flag_c = 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW && digitalRead(sw3) == HIGH) // for peak 1 mode
    {
      if(flag2 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15); }
      delay(10);
      //d1p1 = EEPROM.read(21);  
      delay(15);
      d1p1 = d1p1 + pulse;
      p2 = 0;
      pulse = 0;
      delay(10);
      EEPROM.write(21, d1p1);
      delay(15);
      flag();
      flag2 = 10;
      flag_c == 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH && digitalRead(sw3) == LOW)
    {
      if(flag3 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d1p2 = EEPROM.read(22);  
      delay(15);
      d1p2 = d1p2 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(22, d1p2);
      delay(15);
      flag();
      flag3 = 10;
      flag_c == 10;
      delay(100);
    }  

    lcd.setCursor(8,0);
    lcd.print("N= ");
    lcd.setCursor(11,0);
    lcd_print(11,0,d1n,3);
      
    lcd.setCursor(0,1);
    lcd.print("P1=");
    lcd_print(3,1,d1p1,3);
    //lcd.setCursor(3,1);
    //lcd.print(d1p1);
    //lcd.print("   ");
      
    lcd.setCursor(8,1);
    lcd.print("P2= ");
    lcd_print(12,1,d1p2,3);
    //lcd.setCursor(12,1);
    //lcd.print(d1p2);
   }

  if(date == 2 && flag_c == 0) // if day is 2 and if there is pulse
  {
    if(digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH && digitalRead(sw3) == HIGH)
    {
      if(flag4 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d2n = EEPROM.read(23);  
      delay(15);
      d2n = d2n + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(23, d2n);
      delay(15);
      flag();
      flag4 = 10;
      flag_c == 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW && digitalRead(sw3) == HIGH)
    {
      if(flag5 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d2p1 = EEPROM.read(24);  
      delay(15);
      d2p1 = d2p1 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(24, d2p1);
      delay(15);
      flag();
      flag5 = 10;
      flag_c == 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH && digitalRead(sw3) == LOW)
    {
      if(flag6 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d2p2 = EEPROM.read(25);  
      delay(15);
      d2p2 = d2p2 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(25, d2p2);
      delay(15);
      flag();
      flag6 = 10;
      flag_c == 10;
      delay(100);
    }  

    lcd.setCursor(8,0);
    lcd.print("N= ");
    lcd_print(11,0,d2n,3);
    //lcd.setCursor(11,0);
    //lcd.print(d2n);
      
    lcd.setCursor(0,1);
    lcd.print("P1=");
    lcd_print(3,1,d2p1,3);
    //lcd.setCursor(3,1);
    //lcd.print(d2p1);
      
    lcd.setCursor(8,1);
    lcd.print("P2= ");
    lcd_print(12,1,d2p2,3);
    //lcd.setCursor(12,1);
    //lcd.print(d2p2);
   }

  if(date == 3 && flag_c == 0) // if day is 3 and if there is pulse
  {
    if(digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH && digitalRead(sw3) == HIGH)
    {
      if(flag7 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d3n = EEPROM.read(26);  
      delay(15);
      d3n = d3n + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(26, d3n);
      delay(15);
      flag();
      flag7 = 10;
      flag_c = 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW && digitalRead(sw3) == HIGH)
    {
      if(flag8 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d3p1 = EEPROM.read(27);  
      delay(15);
      d3p1 = d3p1 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(27, d3p1);
      delay(15);
      flag();
      flag8 = 10;
      flag_c == 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH && digitalRead(sw3) == LOW)
    {
      if(flag9 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d3p2 = EEPROM.read(28);  
      delay(15);
      d3p2 = d3p2 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(28, d3p2);
      delay(15);
      flag();
      flag9 = 10;
      flag_c == 10;
      delay(100);
    }  

    lcd.setCursor(8,0);
    lcd.print("N= ");
    lcd.setCursor(11,0);
    lcd.print(d3n);
      
    lcd.setCursor(0,1);
    lcd.print("P1=");
    lcd.setCursor(3,1);
    lcd.print(d3p1);
      
    lcd.setCursor(8,1);
    lcd.print("P2= ");
    lcd.setCursor(12,1);
    lcd.print(d3p2);
   }

  if(date == 4 && flag_c == 0) // if day is 4 and if there is pulse
  {
    if(digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH && digitalRead(sw3) == HIGH)
    {
      if(flag10 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d4n = EEPROM.read(29);  
      delay(15);
      d4n = d4n + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(29, d4n);
      delay(15);
      flag();
      flag10 = 10;
      flag_c = 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW && digitalRead(sw3) == HIGH)
    {
      if(flag11 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d4p1 = EEPROM.read(30);  
      delay(15);
      d4p1 = d4p1 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(30, d4p1);
      delay(15);
      flag();
      flag11 = 10;
      flag_c == 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH && digitalRead(sw3) == LOW)
    {
      if(flag12 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d4p2 = EEPROM.read(31);  
      delay(15);
      d4p2 = d4p2 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(31, d4p2);
      delay(15);
      flag();
      flag12 = 10;
      flag_c == 10;
      delay(100);
    }  

    lcd.setCursor(8,0);
    lcd.print("N= ");
    lcd.setCursor(11,0);
    lcd.print(d4n);
      
    lcd.setCursor(0,1);
    lcd.print("P1=");
    lcd.setCursor(3,1);
    lcd.print(d4p1);
      
    lcd.setCursor(8,1);
    lcd.print("P2= ");
    lcd.setCursor(12,1);
    lcd.print(d4p2);
   }

  if(date == 5 && flag_c == 0) // if day is 5 and if there is pulse
  {
    if(digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH && digitalRead(sw3) == HIGH)
    {
      if(flag13 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d1n = EEPROM.read(32);  
      delay(15);
      d5n = d5n + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(32, d5n);
      delay(15);
      flag();
      flag13 = 10;
      flag_c = 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == LOW && digitalRead(sw3) == HIGH)
    {
      if(flag14 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d5p1 = EEPROM.read(33);  
      delay(15);
      d5p1 = d5p1 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(33, d5p1);
      delay(15);
      flag();
      flag14 = 10;
      flag_c == 10;
      delay(100);
    }

    if(digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH && digitalRead(sw3) == LOW)
    {
      if(flag15 == 0) { p2 = 0;pulse = 0; delay(10); EEPROM.write(0, pulse); delay(15);}
      delay(10);
      //d5p2 = EEPROM.read(34);  
      delay(15);
      d5p2 = d5p2 + pulse;pulse = 0;p2 = 0;
      delay(10);
      EEPROM.write(34, d5p2);
      delay(15);
      flag();
      flag15 = 10;
      flag_c == 10;
      delay(100);
    }  

    lcd.setCursor(8,0);
    lcd.print("N= ");
    lcd.setCursor(11,0);
    lcd.print(d5n);
      
    lcd.setCursor(0,1);
    lcd.print("P1=");
    lcd.setCursor(3,1);
    lcd.print(d5p1);
      
    lcd.setCursor(8,1);
    lcd.print("P2= ");
    lcd.setCursor(12,1);
    lcd.print(d5p2);
   }

  // SEND THE READINGS TO THE PC DEPENDING ON THE DATES, THIS VALUE SENDING IS FOR THE ANALYSIS TO BE DONE ON RECEIVING PART
 if(date == 1){Serial.print(date); Serial.print("/"); Serial.print(d1n); Serial.print("/"); Serial.print(d1p1); Serial.print("/"); Serial.println(d1p2);}
 if(date == 2){Serial.print(date); Serial.print("/"); Serial.print(d2n); Serial.print("/"); Serial.print(d2p1); Serial.print("/"); Serial.println(d2p2);}
 if(date == 3){Serial.print(date); Serial.print("/"); Serial.print(d3n); Serial.print("/"); Serial.print(d3p1); Serial.print("/"); Serial.println(d3p2);}
 if(date == 4){Serial.print(date); Serial.print("/"); Serial.print(d4n); Serial.print("/"); Serial.print(d4p1); Serial.print("/"); Serial.println(d4p2);}
 if(date == 5){Serial.print(date); Serial.print("/"); Serial.print(d5n); Serial.print("/"); Serial.print(d5p1); Serial.print("/"); Serial.println(d5p2);}
 delay(2000);
  
}

