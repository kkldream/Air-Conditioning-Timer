#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(250000);
  Serial.println("Start");
}
bool bt_temp=0;
void loop() {
  if(digitalRead(13) == HIGH && bt_temp==0){
    bt_temp=1;
    unsigned long var = 0xCF3E11E;
    Serial.print("IR send ");
    Serial.println(var, HEX);
//    irsend.sendRC5(var, 32); // 輸出紅外線訊號
    irsend.sendNEC(var, 32); // 輸出紅外線訊號
  }
  else if(digitalRead(13) == LOW){
    bt_temp=0;
  }
}
