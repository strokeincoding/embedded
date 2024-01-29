#include <LiquidCrystal.h> // LCD를 사용하기 위한 헤더파일 선언
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);   // RS,EN,D4,D5,D6,D7(RW->GND)


// 문자 1초 깜빡이기 + 왼쪽으로 한칸씩이동
void setup() 
{
    lcd.begin(16, 2);     // 16x2 TextLCD를 사용하기 위한 선언함수
    lcd.print("                ");  //TextLCD를 공백으로 초기화 설정
 }
void loop() 
{
  lcd.setCursor(0, 0);      // TextLCD의 첫째 줄 첫째 칸 부터 문자열을 표시한다.
  lcd.print("HELLO, Aduino!!");  //문자열을 LCD에 표시한다.
  lcd.setCursor(0, 1);     // TextLCD의 둘째 줄 첫째 칸 부터 문자열을 표시한다.
  lcd.print("Let's GO Aduino");  
  lcd.display();
  delay(1000);
  lcd.noDisplay();
  delay(1000);
  lcd.scrollDisplayLeft();
다.
} 
