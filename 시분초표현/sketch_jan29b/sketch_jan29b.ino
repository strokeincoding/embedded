#include <LiquidCrystal.h> // LCD를 사용하기 위한 헤더파일 선언
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);   // RS,EN,D4,D5,D6,D7(RW->GND)
int sec, min1,hour;
void setup() 
{
    lcd.begin(16, 2);     // 16x2 TextLCD를 사용하기 위한 선언함수
    
 }
void loop() 
{
  delay(1000);
  sec++;
     
  if(sec==60){
    sec=0;
  min1++;}

  if(min1==60){
    min1=0;
    hour++;
    }
lcd.setCursor(0, 0);  
  lcd.print(hour/10);
  lcd.print(hour%10);
  lcd.print(":"); 
  lcd.print(min1/10);
  lcd.print(min1%10);
  lcd.print(":");
  lcd.print(sec/10);
  lcd.print(sec%10);
}
