#include <mcp_can.h>
#include <SPI.h>
MCP_CAN CAN0(53);     // Set CS to pin 53     

const int analogInPin1 = A0;  //PF0, CdS 아날로그 데이터 받을 핀 선언
const int analogInPin2 = A1;  //PF1, Temp 아날로그 데이터 받을 핀 선언
int cds_Value,temp_Value = 0;    //아날로그 데이터 받을 변수 선언2
int ultra = A13; //PE5

const int X_pin = A2; // analog pin connected to X output
const int Y_pin = A3; // analog pin connected to Y output
unsigned int joy_xdata = 0;
unsigned int joy_ydata = 0;

void setup()
{
  Serial.begin(115200);

  if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_16MHZ) == CAN_OK)   Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

byte data[8] = {};

void loop()
{

  cds_Value = map(analogRead(analogInPin1), 0, 1023, 0, 255);
  temp_Value = analogRead(analogInPin2)/12;      //12로 나누어 온도 값을 근사적으로 맞춤
  
  data[0] = cds_Value;
  data[1]= temp_Value;
  
  
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);

  if (sndStat == CAN_OK) {
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms

  pinMode(ultra, OUTPUT);
digitalWrite(ultra, LOW);
 delay(1);
 digitalWrite(ultra, HIGH);
 delayMicroseconds(10);
 digitalWrite(ultra, LOW);
  pinMode(ultra, INPUT);
  unsigned long duration = pulseIn(ultra, HIGH);
  double dist = (331.5 + (0.60714 * 25.0)) * (((double)duration / 1000000) / 2);
  double dist_cm = dist * 100;

  data[2] = dist_cm;

  joy_xdata = analogRead(X_pin);
joy_ydata = analogRead(Y_pin);

data[3] = {map(joy_xdata, 0, 1023, 0, 64)}; //회전방향 제어
data[4] = {map(joy_ydata, 0, 1023, 0, 64)}; //속도 제어


}
