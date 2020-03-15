#define LED_PIN1 11
#define LED_PIN2 10
int port;
String buff;
float brightness = 0;
int state;

void setup()
{
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0)
  {
    char inByte = Serial.read();
    if(inByte == 'L')
    {
      state = 0;
      buff = ' ';
    }
    if(inByte == 'B')
    {
      state = 1;
      buff = ' ';
    }
    if(('0'<=inByte) && (inByte<='9') && (state==0))
    {
      if(inByte == '1')
      {
        port = 11;
      }
      if(inByte == '2')
      {
        port = 10;
      }
    }
   if(('0'<=inByte) && (inByte<='9') && (state==1))
   {
    buff += inByte;
   }
   if((inByte == '\n') && (state == 1))
    {
      brightness = buff.toInt();
      Serial.println(brightness);
      Serial.println(port);
      analogWrite(port,int(brightness*2.24));
    }
  }
}
    
