int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP 
int data_pin = 11; //DS 
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
  num0 = 0b00111111,
  num1 = 0b00000110,
  num2 = 0b01011011,
  num3 = 0b01001111,
  num4 = 0b01100110,
  num5 = 0b01101101,
  num6 = 0b01111101,
  num7 = 0b00100111,
  num8 = 0b01111111,
  num9 = 0b01101111
};


int i = 0;

void setLed(uint8_t _state){
  for(int i = 0 ; i < 8 ; i++){
  digitalWrite(data_pin,(_state >> (7-i)) & 0x01); 
    digitalWrite(clk_pin,HIGH); 
    digitalWrite(clk_pin,LOW);
}

  digitalWrite(latch_pin,HIGH); 
  digitalWrite(latch_pin,LOW); 
  
}
void setup() {
// put your setup code here, to run once: 
    pinMode(clk_pin,OUTPUT); 
    pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
    Serial.begin(9600);
  
    
}


void loop() 
  {
    
    if(Serial.available()>0)
    {
        char data = Serial.read();
      incomingbyte = data;
      Serial.print(data , DEC);
      Serial.print("\t");
    
        if(('0' <= data) && (data <= '9'))
        {
          num = data - 48;
        }
      Serial.println(num);
     }
  setLed(map7seg[num]);
}
