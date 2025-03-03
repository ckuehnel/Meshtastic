/*
   File: HelloWorld.ino

   This program is used to verify correct installation of Arduino IDE
   and correct connection and configuration of an Arduino or
   Arduino-compatible board in Tools menu.

   It is based on the well known http://www.arduino.cc/en/Tutorial/Blink
*/
#include <Arduino.h>
#ifdef NRF52_SERIES
#include <Adafruit_TinyUSB.h>
#endif

// define your bord here, comment not used boards
//#define BOARD "Nucleo-L476RG"
//#define BOARD "Nucleo-L053R8"
//#define BOARD "Teensy 4.0"
//#define BOARD "Arduino Uno WiFi R2"
//#define BOARD "ESPduino - ESP8266"
//#define BOARD "Arduino Uno R3"
//#define BOARD "Arduino Leonardo R3"
//#define BOARD "WeMos LoLin D32 Pro"
//#define BOARD "Arduino Yun"
//#define BOARD "M5StickC"
//#define BOARD "Arduino M0"
//#define BOARD "Wio Terminal"
//#define BOARD "Adafruit HUZZAH32 – ESP32 Feather Board"
//#define BOARD "ESP32-S2-SAOLA-1M"
//#define BOARD "M5Stack Core"
//#define BOARD "Raspberry Pi Pico RP2040"
//#define BOARD "WisCore RAK11200 (Espressif ESP32-WROVER)"
//#define BOARD "WisCore RAK11722 (Apollo3)"
//#define BOARD "WisCore RAK4631 (nRF52840)"
//#define BOARD "ESP32-C6 Dev Module"
//#define BOARD "Infineon XMC1100 XMC2Go"
#define BOARD "XIAO nRF52840"

// int LED_BUILTIN = 10; // uncomment if LED_BUILIN is not defined

//#define Serial SerialUSB // for Arduino M0
//#define Serial Serial0   // for ESP32-S2-SAOLA-1M
//#define Serial Serial1

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for native USB.
  delay(5000);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("\nHello World from ");
  Serial.println(BOARD);            // used board
  Serial.print("Arduino SW Version ");
  Serial.println(ARDUINO);          // Arduino SW version
  Serial.print("Clock frequency ");
  Serial.print(F_CPU / 1000000);    // Oscillator frequency
  Serial.println(" MHz");
  Serial.println();

//  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Serial.println(F("Blink LED"));
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(950);                       // wait for a second
}
