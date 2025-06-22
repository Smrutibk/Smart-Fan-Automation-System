#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define FAN_PIN 9
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define RED_LED_PIN 8
#define GREEN_LED_PIN 9
#define BLUE_LED_PIN 10

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}
void loop() {
float temp = dht.readTemperature();
if (isnan(temp)) {
return;
}
display.clearDisplay();
display.setCursor(0, 0);
display.print("Temp: ");
display.print(temp);
display.print(" C");
display.display();

 if(temp>=30) {
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
    } else if(temp>=25){
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(BLUE_LED_PIN, LOW);
    }else{
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, HIGH);
    }

}