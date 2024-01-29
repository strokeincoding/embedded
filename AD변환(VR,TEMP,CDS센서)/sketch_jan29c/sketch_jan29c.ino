#include <LiquidCrystal.h> // LCD를 사용하기 위한 헤더파일 선언
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);// RS,EN,D4,D5,D6,D7(RW->GND)

const int analogInPin_var = A0;
const int analogInPin_temp = A1;
const int analogInPin_cds = A2;
int sensorValue_var = 0;
int sensorValue_temp = 0;
int sensorValue_cds = 0;

void setup() {
  lcd.begin(16, 2); // TextLCD를 사용하기위한 최초 선언 함수
  lcd.print("                "); //TextLCD를 공백으로 초기화 설정
}
void loop() {
  sensorValue_var = analogRead(analogInPin_var);
  sensorValue_temp = analogRead(analogInPin_temp)/12;
  //수식을 이용하여 계산하여야하나 온도 센서의 동작을 보기 위해 12로 나눈것 큰의미X
  sensorValue_cds = analogRead(analogInPin_cds);

  lcd.setCursor(0, 0); // TextLCD의 첫째 줄 첫째 칸 부터 문자열을 표시한다.
  lcd.print("Var="); //문자열을 LCD에 표시한다.
  lcd.print(sensorValue_var);
  lcd.print(" ");
  lcd.setCursor(8,0);
  lcd.print("cds=");
  lcd.print(sensorValue_cds);
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print("temp=");
  lcd.print(sensorValue_temp);
  lcd.print(" ");
}
