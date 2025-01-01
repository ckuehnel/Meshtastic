#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin-Konfiguration
#define ONE_WIRE_BUS 0  // DS18B20 Datenleitung an Pin D0
#define SCREEN_WIDTH 128 // OLED Breite
#define SCREEN_HEIGHT 64 // OLED Höhe
#define OLED_RESET    -1 // Kein Reset-Pin benötigt
#define OLED_I2C_ADDR 0x3C // I2C-Adresse des OLED-Displays

// Objekte für DS18B20 und OLED
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() 
{
  // Serieller Monitor
  Serial.begin(115200);

  // OLED initialisieren
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
    Serial.println(F("OLED-Initialisierung fehlgeschlagen!"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Start DS18B20 Test"));
  display.display();

  // DS18B20 initialisieren
  sensors.begin();
  delay(1000);
}

void loop() 
{
  // Temperatur messen
  sensors.requestTemperatures();  
  float temperatureC = sensors.getTempCByIndex(0);

  // Temperatur auf dem seriellen Monitor ausgeben
  Serial.print(F("Temperatur: "));
  Serial.print(temperatureC);
  Serial.println(F(" °C"));

  // OLED aktualisieren
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Temperatur"));
  display.setCursor(0, 30);
  display.setTextSize(3);
  display.print(temperatureC, 1);
  display.print(F(" C"));
  display.display();

  // Kurze Pause
  delay(1000);
}

