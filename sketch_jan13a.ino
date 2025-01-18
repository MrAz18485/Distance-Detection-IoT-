#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5
#define WIRE Wire

// HC-SR04
#define TRIG_PIN 8
#define ECHO_PIN 9

// LED
#define GREENLED_PIN 10
#define REDLED_PIN 7


Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

unsigned long prevTime = 0;
int blinkDelay = 5000;
int duration;
float distance;

int STATE = -1;

void setup() {
  Serial.begin(9600);
  // Setting pinModes
  pinMode(GREENLED_PIN, OUTPUT);
  pinMode(REDLED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  delay(1);
  pinMode(ECHO_PIN, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x32

  // LCD Greeting
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();


  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello!");
  display.display();  // actually display all of the above
  delay(1000);
  display.clearDisplay();
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  if (duration > 2912)
  {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("No detection!");
    display.display();  // actually display all of the above
    digitalWrite(GREENLED_PIN, LOW);
    digitalWrite(REDLED_PIN, LOW);
  }
  else // in detectable range.
  {
    distance = duration * 0.01717;
    float meter = distance / 100;
    if (duration <= 2912 && duration > 1164) // between [50, 20] cm
    {
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print(meter);
      display.print(" m\n");
      display.display();  // actually display all of the above
      digitalWrite(GREENLED_PIN, HIGH);
      digitalWrite(REDLED_PIN, LOW);  
    }
    else // between [20, 2] cm
    {
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print(meter);
      display.print(" m\n");
      display.setTextSize(1);
      display.println("UNSAFE RANGE");
      display.display();  // actually display all of the above
      digitalWrite(GREENLED_PIN, LOW);
      digitalWrite(REDLED_PIN, HIGH); 
    }
  }
  display.clearDisplay();
}
