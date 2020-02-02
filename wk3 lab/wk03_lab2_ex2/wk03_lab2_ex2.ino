int clk_pin1   = 13; //shcp
int latch_pin1 = 10; //stcp
int data_pin1  = 11; //ds

int clk_pin2   = 4; //shcp
int latch_pin2 = 5; //stcp
int data_pin2  = 6; //ds

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
  for (int i = 0; i < 16 || i > 0; i = i)
  {
    //latchpin1
    digitalWrite(latch_pin1, LOW);
    for (int c = 0; c < 8; c++)
    {
      if (c == i)
      {
        digitalWrite(data_pin1, HIGH);
      }
      else
      {
        digitalWrite(data_pin1, LOW);
      }
      digitalWrite(clk_pin1, HIGH);
      digitalWrite(clk_pin1, LOW);
    }
    //latchpin2
    digitalWrite(latch_pin2, LOW);
    for (int c = 8; c < 16; c++)
    {
      if (c == i)
      {
        digitalWrite(data_pin2, HIGH);
      }
      else
      {
        digitalWrite(data_pin2, LOW);
      }
      digitalWrite(clk_pin2, HIGH);
      digitalWrite(clk_pin2, LOW);
    }
    
    Serial.println(analogRead(A1));
    if (analogRead(A0) == 0)
    {
      i--;
      if (i < 0) i = 15;
      digitalWrite(latch_pin1, HIGH);
      digitalWrite(latch_pin2, HIGH);
      delay(300);
    }
    if (analogRead(A1) == 0)
    {
      i++;
      if (i > 15) i = 0;
      digitalWrite(latch_pin1, HIGH);
      digitalWrite(latch_pin2, HIGH);
      delay(300);
    }
    digitalWrite(latch_pin1, HIGH);
 
  }
}
