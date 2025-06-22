/*
 * This Arduino Sketch controls a fan's speed based on temperature readings
 * from a DHT11 sensor. The fan speed is varied using a MOSFET controlled
 * by the Arduino. The fan speed increases when the temperature is above
 * 35°C, runs at normal speed between 25°C and 35°C, and decreases when
 * the temperature is below 25°C. The temperature is also displayed on an
 * OLED screen.
 */

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define FAN_PIN 9
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BLUE_LED 4
#define GREEN_LED 5
#define RED_LED 6


DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  dht.begin();
  if(!screen.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(SSD1306_WHITE);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  screen.setCursor(0, 0);
  screen.print("Temperature: ");

  screen.setCursor(0, 35);
  screen.print("Humidity: ");

  if((isnan(hum) || isnan(temp))){
   
   screen.clearDisplay();
    screen.setCursor(0, 0);
    screen.setTextSize(2);
    
    screen.print("Failed to read from DHT sensor!");
    screen.display();
    return;
  }

    screen.setCursor(0, 12);
  screen.setTextSize(2);
  screen.print(temp);
  screen.print((char)247);
  screen.print("C");

  screen.setCursor(0, 47);
  screen.print(hum);
  screen.print(" %");
  screen.display();

  if (temp > 30) {
    analogWrite(FAN_PIN, 255);

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

  } else if (temp >= 25) {
    analogWrite(FAN_PIN, 70);

    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

  } else {
    analogWrite(FAN_PIN, 64);

    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

  }
  delay(2000);
}