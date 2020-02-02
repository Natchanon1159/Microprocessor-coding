int clk_pin1   = 13; //shcp
int latch_pin1 = 10; //stcp
int data_pin1  = 11; //ds

int clk_pin2   = 4; //shcp
int latch_pin2 = 5; //stcp
int data_pin2  = 6; //ds

//bool toggle;
int data;
int i=0;
void setup()
{
  pinMode(clk_pin1,OUTPUT);
  pinMode(latch_pin1,OUTPUT);
  pinMode(data_pin1,OUTPUT);
  
  pinMode(clk_pin2,OUTPUT);
  pinMode(latch_pin2,OUTPUT);
  pinMode(data_pin2,OUTPUT);
}

void loop()
{
  data = 0b10000000;
  
  for(i=0;i<16;i++)
  {
    digitalWrite(data_pin1,(data>>(7-i))&0x01);
    digitalWrite(clk_pin1,HIGH);
    delay(150);
    digitalWrite(clk_pin1,LOW);
    delay(150);
    digitalWrite(latch_pin1,HIGH);
    delay(20);
    digitalWrite(latch_pin1,LOW);
    delay(20);
    
    digitalWrite(data_pin2,(data>>(15-i))&0x01);
    digitalWrite(clk_pin2,HIGH);
    delay(150);
    digitalWrite(clk_pin2,LOW);
    delay(150);
    digitalWrite(latch_pin2,HIGH);
    delay(20);
    digitalWrite(latch_pin2,LOW);
    delay(20);
  }
}
