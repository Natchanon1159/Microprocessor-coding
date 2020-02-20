#include <ThreeWire.h>
#include <RtcDS1302.h> 
ThreeWire myWire(4,5,2); // IO, SCLK, CE 
RtcDS1302<ThreeWire> Rtc(myWire); 


void printDateTime(const RtcDateTime & dt)
{
  
  Serial.print(dt.Year(), DEC);
  Serial.print('/');
  Serial.print(dt.Month(), DEC);
  Serial.print('/');
  Serial.print(dt.Day(), DEC);
  Serial.print(' ');
  Serial.print(dt.Hour(), DEC);
  Serial.print(':');
  Serial.print(dt.Minute(), DEC);
  Serial.print(':');
  Serial.print(dt.Second(), DEC);
  Serial.println();
  Serial.print("Total Seconds since 1/1/2000 : ");
  Serial.print(dt.TotalSeconds());
  Serial.println();
  
}
  RtcDateTime start_time;
void setup() { 
  pinMode(13, HIGH);
  pinMode(12, HIGH);
  digitalWrite(12, LOW);
  
 Serial.begin(57600); 
 Rtc.Begin(); 
 RtcDateTime setting_time(2020,2,20,00,0,0);
 printDateTime(setting_time);
 Rtc.SetDateTime(setting_time); 

 
 start_time = Rtc.GetDateTime().TotalSeconds();
 Serial.println("Start");
} 

void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();

  auto count = now.TotalSeconds();
  
  if(count - start_time <= (60*2))
  {
    printDateTime(now);

    digitalWrite(13,count%2);
  }
  else
  {
    digitalWrite(13,LOW);
    Serial.println("Stop");
  }
  delay(1000);
}
