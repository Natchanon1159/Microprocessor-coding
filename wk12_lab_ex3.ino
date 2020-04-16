#define EncoderB 3
#define EncoderA 2
#define MOTOR_PIN_1 8
#define MOTOR_PIN_2 7
#define MOTOR_PWM 6
#include <EEPROM.h>
#define SW1 5
#define SW2 4

unsigned long preMilli = 0;
unsigned long state = LOW;
int speedMotor = 100;
int typespeed = 0;
int motorspeed = 0;
float Kp = 0.2;
float Ki = 0.1;
int errorI = 0;
int currentMotorState = 0;
String buff;
int encoderCount = 0;

void setup()
{
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  Serial.begin(9600);

  timer_initial(300);
  
  attachInterrupt(digitalPinToInterrupt(EncoderA),
                  ChannelA,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),
                  ChannelB,RISING);
}

void loop()
{
  typespeed = 100;
  int error = typespeed - motorspeed;
  int pid = Kp*(float)(error) + Ki*(float)(errorI);
  errorI += error;
  setSpeed(pid);
  
  Serial.print(typespeed);
  Serial.print(" | ");
  Serial.println(motorspeed);
}

void SerialEvent()
{
  if (Serial.available() > 0) 
  {
    char inByte = Serial.read();
    if(inByte == 's' && currentMotorState == 0)
    {
      currentMotorState = 1;
      buff = " ";
    }
    if(inByte == '-'&& currentMotorState == 1)
    {
      buff += inByte;
    } 
    if(('0'<= inByte) && (inByte <= '9') && (currentMotorState == 1))
    {
      buff += inByte;
    }
    if((inByte == 'n') && (currentMotorState == 1))
    {
      typespeed = buff.toInt();
      currentMotorState = 0;
     }  
  }
}
void moveForward(int velo)
{
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, HIGH);
  analogWrite(MOTOR_PWM, velo);
}

void moveBackward(int velo)
{
  digitalWrite(MOTOR_PIN_1, HIGH);
  digitalWrite(MOTOR_PIN_2, LOW);
  analogWrite(MOTOR_PWM, velo);
}

void setSpeed(int i)
{
  if(i > 100)
    i=100;
  if(i < -100)
    i=-100;
  if(i > 0){
    moveForward(i);
  }
  if(i < 0){
    int vv = i*(-1);
    moveBackward(i);
  }
}

void timer_initial(int period)
{
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = 0;
  OCR1A = (16000000.0/(256.0*100.0))*period - 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}


void ChannelA() 
{
  if (digitalRead(EncoderA) == 1 
      && digitalRead(EncoderB) == 0) 
  {
    encoderCount++;
    //encoderDir = 0;
  }
}
void ChannelB() 
{
  if (digitalRead(EncoderA) == 0
      && digitalRead(EncoderB) == 1)
  {
    encoderCount--;
    //encoderDir = 1;
  }
}
