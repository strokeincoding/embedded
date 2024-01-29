#include <LiquidCrystal.h>
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);

// 문자 "부"
byte SpecialChar1[8] = {
B01010,B01110,B01010,B01110,B00000,B11111,B00100,B00100};
// 문자 "산"
byte SpecialChar2[8] = {
B01010,B10110,B10111,B00010,B00010,B01000,B01000,B01110};
// 문자 "외"
byte SpecialChar3[8] = {
B01001,B10101,B10101,B01001,B01001,B01001,B11111,B00001};
// 문자 "대"
byte SpecialChar4[8] = {
B00101,B11101,B10101,B10111,B10101,B10101,B11101,B00101};

void setup() {
// 문자 저장
  lcd.createChar(1, SpecialChar1);
  lcd.createChar(2, SpecialChar2);
  lcd.createChar(3, SpecialChar3);
  lcd.createChar(4, SpecialChar4);

  lcd.begin(16, 2);
  lcd.setCursor(4,0);
// 저장해 놓은 문자 출력("부산외대")
  for (int i = 1 ; i < 5 ; i++) { 
  lcd.write(byte(i));
  }
}
void loop() {
}
