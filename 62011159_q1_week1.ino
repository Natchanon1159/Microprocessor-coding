void setup()
{
  DDRD = 0xFF;
  DDRB = 0xFF;
}

void loop()
{
  for(int i=0;i<9;i++)
    {
      PORTD = 1 << i;
      delay(10);
    }
  
    PORTB = 0b00000001;
    delay(10);
    for(int j=1;j<7;j++)
    {
      PORTB = 1 << j;
      delay(10);
    }
  
}
