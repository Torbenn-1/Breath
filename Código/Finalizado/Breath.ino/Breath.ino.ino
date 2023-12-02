#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128 // Largura da tela em pixels
#define SCREEN_HEIGHT 64 // Altura da tela em pixels

#define OLED_RESET -1 // Pino de reset (usar -1 se não estiver conectado)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTpin 4 // D4 on the nodemcu ESP32
#define DHTTYPE DHT11
DHT dht_sensor(DHTpin, DHTTYPE);

int sensor = 34;

void setup() {
  Serial.begin(9600);
  delay(1500);

  dht_sensor.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao iniciar a tela OLED"));
    for(;;);
  }
  
  display.clearDisplay();
}

void loop() {
  float humi = dht_sensor.readHumidity();
  float tempC = dht_sensor.readTemperature();
  float tempF = dht_sensor.readTemperature(true);
  int airqualityvalue = analogRead(sensor);

  if (isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Falha ao ler do sensor DHT!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%  |  ");
    
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.print("°F  |  ");
    
    Serial.print("Gas Value: ");
    Serial.println(airqualityvalue);
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    String message = "Temperature = " + String(tempC) + "  Humidity = " + String(humi) + "  Air Quality = " + String(airqualityvalue);
    display.println(message);
    display.display();
  }

  delay(1000);
}
