#include <LiquidCrystal.h> 
#include <MsTimer2.h>
LiquidCrystal lcd(23, 24, 25, 26, 27, 28); 

byte SpecialChar1[8]={B11111,10001,11111,10001,10001,11111,10001,10001};
byte SpecialChar2[8]={B11111,10001,10001,11111,11111,10001,10001,11111};

int sec, min1=58, hour=23, hour1;
int month=1, date=31;

void setup(){   
  pinMode(18, INPUT);
  pinMode(19, INPUT); 

  lcd.begin(16, 2);
  lcd.createChar(1, SpecialChar1);
  lcd.createChar(2, SpecialChar2);
  
  attachInterrupt(digitalPinToInterrupt(18), blink1, FALLING);
  attachInterrupt(digitalPinToInterrupt(19), blink2, FALLING);
  
  MsTimer2::set(1000, flash);
  MsTimer2::start();
 } 
void flash(){
         sec++;          //1초 마다 sec 변경
}
void blink1(){
          hour++;
      //외부 인터럽트 발생시 수행할 동작 (시 혹은 날짜 조정)
}
void blink2(){
            min1++;
     // 외부 인터럽트 발생시 수행할 동작 (분 조정)
}

void loop(){
  if(sec==60){
    sec=0;
  min1++;}

  if(min1==60){
    min1=0;
    hour++;
    }

   if(hour==24){
    hour=0;
    date++;}
    if (month==1 & date==32) {month++; date=1;}
 else if (month==2 & date==29) {month++; date=1;}
 else if (month==3 & date==32) {month++; date=1;}
 else if (month==4 & date==31) {month++; date=1;}
 else if (month==5 & date==32) {month++; date=1;}
else if (month==6 & date==31) {month++; date=1;}
else if (month==7 & date==32) {month++; date=1;}
else if (month==8 & date==31) {month++; date=1;}
else if (month==9 & date==32) {month++; date=1;}
else if (month==10 & date==31) {month++; date=1;}
else if (month==11 & date==32) {month++; date=1;}
else if (month==12 & date==31) {month++; date=1;}

 

lcd.setCursor(0,0);
lcd.print(month);
lcd.write(byte(1));
lcd.print(" ");
lcd.print(date);
lcd.write(byte(2));
lcd.print("  ");

lcd.setCursor(0, 1);
if(hour>11){
lcd.print("PM");
lcd.print((hour-12)/10);
  lcd.print((hour-12)%10);}
else{lcd.print("AM");
  lcd.print(hour/10);
  lcd.print(hour%10);}
  lcd.print(":"); 
  lcd.print(min1/10);
  lcd.print(min1%10);
 
  
}
