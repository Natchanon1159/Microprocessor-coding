#include <SPI.h> 
#define EncoderB 3
#define EncoderA 2
#define MOTOR_PIN_1 8
#define MOTOR_PIN_2 7
#define PWM_PIN 6


volatile int encoderCount = 0;
volatile int encoderDir;
int setpoint = 300;

void setup()
{
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(EncoderA),ChannelA, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),ChannelB, RISING);
}

void loop()
{
  int error = setpoint - encoderCount;
  int control_value= 3.5*(float)(error);
  setSpeed(control_value);
  Serial.print(control_value);
  Serial.print(" , ");
  Serial.println(encoderCount);
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
  //digitalWrite(LED, encoderDir);
  int j = encoderCount/100;
  //write7Segment(j);
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
