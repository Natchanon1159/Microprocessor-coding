#include <SPI.h> 
#define Data_pin 11
#define Clock_pin 13
#define SS_pin1 10
#define SS_pin2 9
#define EncoderB 3
#define EncoderA 2
#define MOTOR_PIN_1 8
#define MOTOR_PIN_2 7
#define PWM_PIN 6
#define LED 12

volatile int encoderCount = 0;
volatile int encoderDir;
int j = 0;

int map7seg[10] = 
{
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};

void setup()
{
  pinMode(Data_pin, OUTPUT);
  pinMode(Clock_pin, OUTPUT);
  pinMode(SS_pin1, OUTPUT);
  pinMode(SS_pin2, OUTPUT);
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(EncoderA),ChannelA, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),ChannelB, RISING);
}

void loop()
{
  int control_value = 100;
  //int control_value = -100;
  setSpeed(control_value);
  Serial.print(control_value);
  Serial.print(" , ");
  Serial.print(encoderCount);
  Serial.print(" , ");
  Serial.println(encoderDir);
}

void moveForward(int Speed)
{
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, HIGH);
  analogWrite(PWM_PIN, Speed);
}

void moveBackward(int Speed)
{
  digitalWrite(MOTOR_PIN_1, HIGH);
  digitalWrite(MOTOR_PIN_2, LOW);
  analogWrite(PWM_PIN, Speed);
}

void setSpeed(int i)
{
  if(i > 0 && i < 255)
  {
    moveForward(i);
  }
  if(i < 0 && i > -255)
  {
    int vv = i*(-1);
    moveBackward(i);
  }
  digitalWrite(LED, encoderDir);
  int j = encoderCount/100;
  write7Segment(j);
}

void spi_write_1(unsigned char cData)
{
  shiftOut(Data_pin, Clock_pin, MSBFIRST, cData);
    digitalWrite(SS_pin1, HIGH);
    digitalWrite(SS_pin1, LOW);
}
void spi_write_2(unsigned char cData)
{
  shiftOut(Data_pin, Clock_pin, MSBFIRST, cData);
    digitalWrite(SS_pin2, HIGH);
    digitalWrite(SS_pin2, LOW);
}
void write7Segment(unsigned char num)
{
  num = num*(-1);
  spi_write_1(map7seg[num/1000]);
  spi_write_2(map7seg[(num/100)%10]);
}
void ChannelA() 
{
  if (digitalRead(EncoderA) == 1 
      && digitalRead(EncoderB) == 0) {
    encoderCount--;
    encoderDir = 0;
  }
}
void ChannelB() 
{
  if (digitalRead(EncoderA) == 0 
      && digitalRead(EncoderB) == 1){
    encoderCount++;
    encoderDir = 1;
  }
}
