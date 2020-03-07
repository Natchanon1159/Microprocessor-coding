#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SWITCH_PIN1 2
#define SWITCH_PIN2 3

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool sw1 = 0;
bool sw2 = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(SWITCH_PIN1, INPUT_PULLUP);
  pinMode(SWITCH_PIN2, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

}

void loop() 
{
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,11);
  display.println("SW1");
  display.drawCircle(90, 20, 9, WHITE); // x,y,radius
  display.println("SW2");
  display.drawCircle(90, 46, 9, WHITE);
  sw1 = digitalRead(SWITCH_PIN1);
  sw2 = digitalRead(SWITCH_PIN2);
  Serial.println(sw1);
  if(sw1 == LOW)
  {
     display.fillCircle(90, 20, 9, WHITE);
      
  }
    
  if(sw2 == LOW)
  {
     display.fillCircle(90, 46, 9, WHITE);
  }
    display.display();
}
