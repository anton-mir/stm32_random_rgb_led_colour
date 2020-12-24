#include <Arduino.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <analogWrite.h>

#define red_pin 21 // 16pin
#define green_pin 13 // 17pin
#define blue_pin 12 // 4pin
#define led_buildin 2
#define display_pin 16
#define button_pin 0
#define LED_OK_COUNTS 100
#define LED_WAIT_TIME 1500

//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA -- GPIO4
//OLED_SCL -- GPIO15
//OLED_RST -- GPIO16

SSD1306  display(0x3c, 4, 15);
int sum = 0;
byte red = 0, green = 0, blue = 0;

int counter = 1;
bool ledvar = 0;
byte led_stream=0;
long int numbers_counters[6] = {0};

int redCounter = 0, greenCounter = 0, blueCounter = 0, yellowCounter = 0, purpleCounter = 0, lightBlueCounter = 0, orangeCounter = 0;

void resetCounters()
{
  purpleCounter = 0; 
  redCounter = 0; 
  blueCounter = 0;
  greenCounter = 0;
  lightBlueCounter = 0;  
  orangeCounter = 0; 
  yellowCounter = 0; 
  Serial.println("Reset counters");
}  

void colour(byte r, byte g, byte b)
{
  analogWrite(red_pin, r);
  analogWrite(green_pin, g);
  analogWrite(blue_pin, b);
}

void showRed()
{
  Serial.println("Red");
  display.clear();
  display.drawString(10, 5, "RED");
  display.display();
  colour(255,0,0);
  delay(LED_WAIT_TIME);
  resetCounters();
}
void showBlue()
{
  Serial.println("Blue");
  display.clear();
  display.drawString(10, 5, "BLUE");
  display.display();
  colour(0,0,255);
  delay(LED_WAIT_TIME);
  resetCounters();
}
void showGreen()
{
  Serial.println("Green");
  display.clear();
  display.drawString(10, 5, "GREEN");  
  display.display();
  colour(0,255,0);
  delay(LED_WAIT_TIME);
  resetCounters();
}
void showOrange()
{
  Serial.println("Orange");
  display.clear();
  display.drawString(10, 5, "ORANGE");
  display.display();
  colour(49,23,17);
  delay(LED_WAIT_TIME);
  resetCounters();
}
void showYellow()
{
  Serial.println("Yellow");
  display.clear();
  display.drawString(10, 5, "YELLOW");
  display.display();
  colour(53,68,28);
  delay(LED_WAIT_TIME);
  resetCounters();
}
void showLightBlue()
{
  Serial.println("Light Blue");
  display.clear();
  display.drawString(10, 5, "LIGHT BLUE");
  display.display();
  colour(25,152,220);
  delay(LED_WAIT_TIME);
  resetCounters();
}
void showPurple()
{
  Serial.println("Purple");
  display.clear();
  display.drawString(10, 5, "PURPLE");
  display.display();
  colour(140,13,120);
  delay(LED_WAIT_TIME);
  resetCounters();
}

void setup() 
{
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(display_pin, OUTPUT);
  pinMode(led_buildin, OUTPUT);

  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT); 
  
  digitalWrite(display_pin, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(display_pin, HIGH); // while OLED is running, must set GPIO16 in high
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  showRed();
  showGreen();
  showBlue();
  showOrange();
  showYellow();
  showLightBlue();
  showPurple();
}

void processRandom()
{
    uint32_t raw_value = esp_random();
    
    if (raw_value == 0) return;
    else
    {
      switch (raw_value % 6)
      {
        case 1:
          red == 255 ? 255 : ++red;
          ++numbers_counters[0];
        break;
        case 2:
          red == 0 ? 0 : --red;
          ++numbers_counters[1];
        break;
        case 3:
          green == 255 ? 255 : ++green;
          ++numbers_counters[2];
        break;
        case 4:
          green == 0 ? 0 : --green;
          ++numbers_counters[3];
        break;
        case 5:
          blue == 255 ? 255 : ++blue;
          ++numbers_counters[4];
        break;
        case 0:
          blue == 0 ? 0 : --blue;
          ++numbers_counters[5];
        break;
        default:
          blue == 0 ? 0 : --blue;
          green == 0 ? 0 : --green;
          red == 0 ? 0 : --red;
        break;
      }
    }
}

void showDisplay()
{
  display.clear();
  
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT); 

  display.drawString(10, 5, "R");
  display.drawString(20, 5, String(red));
  display.drawString(50, 5, "G");
  display.drawString(60, 5, String(green));
  display.drawString(90, 5, "B");
  display.drawString(100, 5, String(blue));

  display.drawString(10, 25, "R");
  display.drawString(20, 25, String(redCounter));
  display.drawString(50, 25, "G");
  display.drawString(60, 25, String(greenCounter));
  display.drawString(90, 25, "B");
  display.drawString(100, 25, String(blueCounter));

  display.drawString(10, 45, "Y");
  display.drawString(20, 45, String(yellowCounter));
  display.drawString(40, 45, "O");
  display.drawString(50, 45, String(orangeCounter));
  display.drawString(70, 45, "P");
  display.drawString(80, 45, String(purpleCounter));
  display.drawString(105, 45, "LB");
  display.drawString(120, 45, String(lightBlueCounter));
  
  display.display();

  Serial.println();
  Serial.print(red);
  Serial.print(" ");
  Serial.print(green);
  Serial.print(" ");
  Serial.print(blue);
  Serial.print(" ");
  Serial.print(++numbers_counters[0]);
  Serial.print(" ");
  Serial.print(++numbers_counters[1]);
  Serial.print(" ");
  Serial.print(++numbers_counters[2]);
  Serial.print(" ");
  Serial.print(++numbers_counters[3]);
  Serial.print(" ");
  Serial.print(++numbers_counters[4]);
  Serial.print(" ");
  Serial.println(++numbers_counters[5]);
}

void litLeds()
{
  if (ledvar)
  {
    led_stream == 255 ? ledvar = !ledvar : ++led_stream;
  }
  else
  {
    led_stream == 0 ? ledvar = !ledvar : --led_stream;
  }
  
  analogWrite(led_buildin, led_stream);  
  colour(red,green,blue);
}

void loop() {

  processRandom(); 

  litLeds();

  if (red > 240 && blue < 10 && green < 10) ++redCounter;
  if (blue > 240 && red < 10 && green < 10) ++blueCounter;
  if (green > 240 && blue < 10 && red < 10) ++greenCounter;
  if (red > 211 && red < 243 && green > 84 && green < 156 && blue > 15 && blue < 34) ++orangeCounter;
  if (red > 230 && red < 243 && green > 156 && green < 200 && blue > 10 && blue < 20) ++yellowCounter;
  if (red > 41 && red < 60 && green > 128 && green < 160 && blue > 185 && blue < 220) ++lightBlueCounter;
  if (red > 140 && red < 160 && green > 65 && green < 90 && blue > 170 && blue < 185) ++purpleCounter;

  showDisplay();
  
  if (redCounter == LED_OK_COUNTS) showRed();
  else if (blueCounter == LED_OK_COUNTS) showBlue();
  else if (greenCounter == LED_OK_COUNTS) showGreen();
  else if (orangeCounter == LED_OK_COUNTS) showOrange();
  else if (yellowCounter == LED_OK_COUNTS) showYellow();
  else if (lightBlueCounter == LED_OK_COUNTS) showLightBlue();
  else if (purpleCounter == LED_OK_COUNTS) showPurple();

  while (!digitalRead(button_pin))
  {
    delay(100);
  }

  delay(1);
}