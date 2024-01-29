#include <LiquidCrystal.h> // LCD 사용하기 위한 헤더 선언

int ultra = A13; // PE5, 초음파 신호 핀
int buzz = A12; // PE4, 부저 신호 핀

LiquidCrystal lcd(23, 24, 25, 26, 27, 28); // LCD 객체 선언 
unsigned long last_millis;  // 부저의 시간 체크하기 위한 변수

void setup() {
  lcd.begin(16, 2); // LCD 초기화
  lcd.clear(); // LCD 화면을 깨끗하게 지움

  pinMode(ultra, OUTPUT); // 초음파 신호 핀을 출력으로 설정
  pinMode(buzz, OUTPUT);  // 부저 신호 핀을 출력으로 설정

  last_millis = millis();
}

// 초음파 모듈이 측정한 거리에 따라 부저 울림 간격을 결정하는 함수
unsigned int Buzz_Time(double dist_cm) {
  if (dist_cm >= 81 && dist_cm <= 100) {
    return 2000;
  } else if (dist_cm >= 51 && dist_cm <= 80) {
    return 1000;
  } else if (dist_cm >= 21 && dist_cm <= 50) {
    return 500;
  } else if (dist_cm > 0 && dist_cm <= 20) {
    return 200;
  } else {
    return 0;
  }
}

void loop() {
  digitalWrite(ultra, LOW);
  delay(1);
  digitalWrite(ultra, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra, LOW);

  pinMode(ultra, INPUT); // 초음파 신호 핀을 입력으로 전환

  unsigned long duration = pulseIn(ultra, HIGH);
  double dist = (331.5 + (0.60714 * 25.0)) * (((double)duration / 1000000) / 2);
  double dist_cm = dist * 100; // 거리를 센티미터 단위로 변환

  int bz = Buzz_Time(dist_cm); // 부저 울림 간격 계산

  if (bz != 0) {
    if ((millis() - last_millis) > bz) {
      tone(buzz, 2000, 100); // 부저를 울림
      last_millis = millis();
    }
  }

  delay(50); // 다음 루프까지 약간의 지연
}
