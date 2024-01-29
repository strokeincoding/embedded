#include <LiquidCrystal.h> // LCD를 사용하기 위한 헤더파일 선언
LiquidCrystal lcd(23, 24, 25, 26, 27, 28); // RS,EN,D4,D5,D6,D7(RW->GND)
const int analogPin=A0;//PF0
int sensorValue=0;

void setup() 
{
     lcd.begin(16, 2);   // 16x2 TextLCD를 사용하기 위한 선언함수
     lcd.print(“                "); //TextLCD를 공백으로 초기화 설정
}

void loop() {
lcd.setCursor(0,0);
sensorValue=analogRead(analogPin);
 lcd.print(sensorValue);
// lcd.print(“  “);
 delay(100);
 lcd.clear();
 //현재값만 찍는지 표현 자릿수와 다르게 이전 값도 표현하는지 확인

}
