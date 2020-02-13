#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9

int counter;
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
}

void loop()
{
  for(int i=0; i<100; i++)
  {
  show_num(i);
    delay(800);
  }
  
}
