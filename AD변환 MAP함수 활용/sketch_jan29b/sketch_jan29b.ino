#include <LiquidCrystal.h> // LCD를 사용하기 위한 헤더파일 선언
LiquidCrystal lcd(23, 24, 25, 26, 27, 28); // RS,EN,D4,D5,D6,D7(RW->GND)
const int analogPin=A0;//PF0
const int analogOutPin=44; //PB5 
const int digitalOutPin=6; //D6
int sensorValue=0;

void setup() {
     lcd.begin(16, 2);   // 16x2 TextLCD를 사용하기 위한 선언함수
     lcd.print(“                "); //TextLCD를 공백으로 초기화 설정
     pinMode(digitalOutPin, OUTPUT);
     pinMode(analogOutPin, OUTPUT);

}

void loop() {
lcd.setCursor(0,0);
sensorValue=map(analogRead(analogPin),0,1023,0,255);
lcd.print(sensorValue);
analogWrite(analogOutPin, sensorValue);
digitalWrite(digitalOutPin, sensorValue);
}
