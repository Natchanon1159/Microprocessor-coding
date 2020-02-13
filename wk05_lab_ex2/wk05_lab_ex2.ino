#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define add A0
#define minus A1
#define countdown A2

int count = 0;
int num;
int num0; //0
int num1; //1
int num2; //2
int num3; //3
int num4; //4
int num5; //5
int num6; //6
int num7; //7
int num8; //8
int num9; //9

int incomingbyte = 0;

int map7seg[] = {
  num0 = 0x3F,
  num1 = 0x06,
  num2 = 0x5B,
  num3 = 0x4F,
  num4 = 0x66,
  num5 = 0x6D,
  num6 = 0x7D,
  num7 = 0x07,
  num8 = 0x7F,
  num9 = 0x6F
};

void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN,CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}
void spi_write_2(unsigned char cData)
{
  shiftOut(DATA_PIN,CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
}

void show_num(int x)
{
  int x1, x2;
  x1 = x/10;
  x2 = x%10;
  spi_write_1(map7seg[x1]);
  spi_write_2(map7seg[x2]);
}

void setup()
{
  Serial.begin(9600);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(add,INPUT);
  pinMode(minus,INPUT);
  pinMode(countdown,INPUT);
  pinMode(6,OUTPUT);
}

void loop()
{   
  show_num(count);
  if(digitalRead(add)==0)
  {
    Serial.print(digitalRead(add));
    while(digitalRead(add)==0);
    count++;
  }
  if(digitalRead(minus)==0)
  {
    Serial.print(digitalRead(minus));
    while(digitalRead(minus)==0);
    count--;
  }
  if(digitalRead(countdown)==0)
  {
    while(digitalRead(countdown)==0);
    
    for(int i = count;i > 0;i--)
    {
      show_num(i);
      delay(200);
    }
    count = 0;
    tone(6,1000,2000);
  }
  delay(300);
}
