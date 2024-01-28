#include <Servo.h> 
Servo myservo;     
int code_motor;

char buf[3];
char bufindex;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("OK");
  myservo.attach(44);  

}
unsigned long lastDebounceTime=0;
const int analogPin_temp=A9;
float sensorValue_temp=0;

void loop() {
   if (millis() - lastDebounceTime > 1000) {
    sensorValue_temp=analogRead(analogPin_temp);
    sensorValue_temp=(5.0 * sensorValue_temp * 100.0) / 1024.0;
    sensorValue_temp=sensorValue_temp / 7.3;  //대략적인 온도 

    Serial.print(sensorValue_temp);
    Serial.println("℃");

    Serial3.print(sensorValue_temp,1); //소수 첫째 자리까지 전송
    lastDebounceTime = millis();
    }  // if
if (Serial3.available()) {
    char c = Serial3.read();
       
    if (c=='\n') {
        if (buf[0]=='P') {

    if(buf[1]=='1'){digitalWrite(13,LOW);}
    else if(buf[1]=='0') {digitalWrite(13,HIGH);}


           }  
           if (buf[0]=='I') {
        code_motor=(buf[1]-'0')*100+(buf[2]-'0')*10+(buf[3]-'0')*1;
        myservo.write(code_motor);
           //if-buf
      memset(buf, 0, 3);
      bufindex=0; } // if
      
    else if (bufindex<3){
      buf[bufindex]=c;
      bufindex++;}


        }
      } // if-Serial3


}
