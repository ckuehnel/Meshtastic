#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_GFX.h> // v1.11.11
#include <Adafruit_SSD1306.h> // 2.5.13
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SHT31 sht30 = Adafruit_SHT31(); // SHT30 object
Adafruit_BMP280 bmp; // BMP280 Objekt
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() 
{
  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(115200);
  Serial1.println("XIAO Sensor starts");

  pinMode(LED_BLUE, OUTPUT);

  if(!sht30.begin(0x44))
  {
    Serial.println("SHT30 Sensor nicht gefunden!");
    while (1);
  }
  
  if (!bmp.begin(0x76)) {  // Adresse des BMP280 (häufig 0x76 oder 0x77)
    Serial.println("BMP280 Sensor nicht gefunden!");
    while (1);
  }

  // OLED-Display Initialisierung
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Adresse 0x3C für OLED-Display
    Serial.println("OLED-Display nicht gefunden!");
    while (1);
  }
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() 
{
  // Blink BLue Led
  digitalWrite(LED_BLUE, LOW); 
  delay(500);
  digitalWrite(LED_BLUE, HIGH); 

  // SHT30 Werte abfragen
  float temperatureSHT30 = sht30.readTemperature();
  float humidity = sht30.readHumidity();

  // BMP280 Werte abfragen
  float temperatureBMP280 = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // in hPa

  // Prüfen auf Lesefehler
  if (isnan(temperatureSHT30) || isnan(humidity)) {
    Serial.println("Fehler beim Lesen des SHT30!");
    return;
  }
  if (isnan(temperatureBMP280) || isnan(pressure)) {
    Serial.println("Fehler beim Lesen des BMP280!");
    return;
  }

  // JSON-Dokument erstellen
  JsonDocument jsonDoc;
  jsonDoc["temperature_sht30"] = temperatureSHT30;
  jsonDoc["humidity"] = humidity;
  jsonDoc["temperature_bmp280"] = temperatureBMP280;
  jsonDoc["pressure"] = pressure;

  // JSON-Dokument in String umwandeln und seriell ausgeben
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  Serial.println(jsonString);
  Serial1.println(jsonString);

  // OLED-Anzeige
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Temp SHT30: ");
  display.print(temperatureSHT30);
  display.println(" C");

  display.setCursor(0, 16);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 32);
  display.print("Temp BMP280: ");
  display.print(temperatureBMP280);
  display.println(" C");

  display.setCursor(0, 48);
  display.print("Pressure: ");
  display.print(pressure);
  display.println(" hPa");

  display.display();

  delay(5000); // 5 Sekunden warten
}