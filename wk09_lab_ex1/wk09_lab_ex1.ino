#define LED_PIN 9
#define INT_PIN 3
volatile byte state = LOW;

int count  = 0;
int toggle = 1;
int t = 1000;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                  ISR_Callback, 
                  RISING);
  // RISING  : 0v --> 5V
  // FALLING : 5v --> 0V
  // CHANGE  : 0v --> 5V or 5v --> 0V
  Serial.begin(9600);
}
void loop()
{
  if(count == 0)
  {
    digitalWrite(LED_PIN, LOW);
  }
  else if(count == 1)
  {
    blink_1_sec(t);
  }
  else if(count == 2)
  {
    blink_2_sec(t);
  }
  else if(count == 3)
  {
    blink_3_sec(t);
  }
}
//this is use for interrupt
//if rising this will be call when release button
//if falling this will be call when push button
//if change this will be call when push button
void ISR_Callback()
{
  count++;
  Serial.println("Called");
}

void blink_1_sec(float x)
{
  digitalWrite(LED_PIN,state);
  delay(t);
  state = !state;
}
void blink_2_sec(float x)
{
  digitalWrite(LED_PIN,state);
  delay(t*2);
  state = !state;
}
void blink_3_sec(float x)
{
  digitalWrite(LED_PIN,state);
  delay(t*3);
  state = !state;
}
