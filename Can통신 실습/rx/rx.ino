const int cdsOutPin =  44;   //PB5

#include <LiquidCrystal.h> // LCD를 사용하기 위한 헤더파일 선언
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);// RS,EN,D4,D5,D6,D7(RW-<GND)
#include <mcp_can.h>
#include <SPI.h>

#define IN3 A1   //PF1
#define IN4 A2   //PF2
#define ENB 45  //PWM Pin, PB4
unsigned char dc_speed = 0;
unsigned char dc_dir = 0;


long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];   

int buzz = A12;
unsigned long last_millis;

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(53);                               // Set CS to pin 10

void setup()
{
  pinMode(IN3, OUTPUT); //IN01 포트 출력으로 설정
  pinMode(IN4, OUTPUT); //IN02 포트 출력으로 설정
  pinMode(ENB, OUTPUT); //ENB 포트 출력으로 설정

  
  pinMode(cdsOutPin, OUTPUT); // LED를 연결할 cdsOutPin 핀 모드를 OUTPUT로 설정
  lcd.begin(16, 2); // TextLCD를 사용하기 위한 최초 선언함수
  lcd.print("                "); //TextLCD를 공백으로 초기화 설정
  Serial.begin(115200);

if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
    
  CAN0.setMode(MCP_NORMAL);                   
  pinMode(CAN0_INT, INPUT);       

  last_millis = millis(); //setup에 추가

}
unsigned int Buzz_Time(double dist_cm) {

  if (dist_cm <= 30 && dist_cm > 20) {
    return 4000;
  } else if (dist_cm <= 20 && dist_cm > 10) {
    return 2000;
  } else if (dist_cm <= 10 && dist_cm > 5) {
    return 500;
  } else if (dist_cm <= 5 ) {
    return 100;
  } else {
    return 0;
  }
}  // 함수 Buzz_Time 


void loop()
{
  
  if (!digitalRead(CAN0_INT)) // CAN0_INT 핀이 LOW 이면 버퍼를 읽어온다.
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);  // Read data: len = data length, buf = data byte(s)
    lcd.clear();
    lcd.setCursor(0, 0); // TextLCD의 첫째 줄 첫째 칸 부터 문자열을 표시한다.
    lcd.print("CdS:");
    lcd.print(rxBuf[0]);
    Serial.print("CdS:");
    Serial.println(rxBuf[0]);
    
    analogWrite(cdsOutPin, rxBuf[0]);
   }
        
    lcd.setCursor(8,0);
    lcd.print(" temp:");
    lcd.print(rxBuf[1]);


    Serial.print(" temp:");
    Serial.println(rxBuf[1]);

    lcd.setCursor(0, 1); 
    lcd.print("Dis:");
    lcd.print(rxBuf[2]); // loop에 추가 

    lcd.setCursor(7, 1); 
    lcd.print("X:");
    lcd.print(rxBuf[3]); // loop에 추가 
    lcd.print("Y:");
    lcd.print(rxBuf[4]); // loop에 추가 

  int bz = Buzz_Time(rxBuf[2]);
    if (bz != 0) {
      if ( ( millis() - last_millis ) > bz  )
      {
        tone(buzz, 10000, 100);
        last_millis = millis();
      }
    }
    delay(300);     // loop에 추가 

    dc_dir = rxBuf[3];
   dc_speed =  rxBuf[4];
   analogWrite(ENB, 4*dc_speed);

if (dc_dir >= 32) {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    
   }
