// CoreMark Benchmark for Arduino compatible boards
//   original CoreMark code: https://github.com/eembc/coremark
#include <Arduino.h>
#ifdef NRF52_SERIES
#include <Adafruit_TinyUSB.h>
#endif

#include <stdarg.h>

// A way to call the C-only coremark function from Arduino's C++ environment
extern "C" int coremark_main(void);

//#include <M5STACK>
//#define BOARD "Arduino Uno"  // describe your board here
//#define BOARD "Arduino Uno WiFi R2"
//#define BOARD "Arduino Due"
//#define BOARD "Arduino MKR 1000"
//#define BOARD "ESPduino-8266"  // repeated resets 2019-08-15
//#define BOARD "ESPduino-32"
//#define BOARD "M5STACK"
//#define BOARD "BBC Micro:bit"
//#define BOARD "NUCLEO-L476RG"
//#define BOARD "NUCLEO-L053R8"
//#define BOARD "NUCLEO-L412KB"
//#define BOARD "Maixduino"
//#define BOARD "Teensy 4.0"
//#define BOARD "Longan Nano - GD32FV103"
//#define BOARD "Arduino Nano Every"
//#define BOARD "Heltec CubeCell"
//#define BOARD "Wio Terminal"
//#define BOARD "STM32 Bluepill"
//#define BOARD "Arduino Nano 33 BLE"
//#define BOARD "ESP32-C3-DevKitC-02"
//#define BOARD "Raspberry Pi Pico"
//#define BOARD "Arduino Portenta H7 - Cortex-M7"
//#define BOARD "Wemos LOLIN ESP32-S3 Pro"
//#define BOARD "WisBlock Core RAK11722 - Ambiq Apollo3"
//#define BOARD "WisBlock Core RAK3372 - STM32WLE5 Core Module for LoRaWAN"
//#define BOARD "WisBlock Core RAK4631 - Nordic nRF52840 BLE Core Module for LoRaWAN with LoRa SX1262"
//#define BOARD "WisBlock Core RAK11310 - Raspberry Pi RP2040 Core Module for LoRaWAN with LoRa SX1262"
//#define BOARD "WisBlock Core RAK11200 - WiFi and BLE Espressif ESP32-WROVER"
//#define BOARD "Arduino UNO R4 WiFi"
//#define BOARD "Arduino Nano ESP32"
//#define BOARD "ESP32-C6 Dev Module"
//#define BOARD "XMC4700 Relax Kit - Cortex-M4F"
#define BOARD "XIAO nRF52840 - Cortex-M4F"

void setup() {
  Serial.begin(115200);
  while (!Serial);  // wait for Arduino Serial Monitor
  delay(2000);
  Serial.println(F("CoreMark Performance Benchmark"));
  Serial.print("for ");
  Serial.println(BOARD);
  Serial.print(F("Arduino SW Version "));
  Serial.println(ARDUINO);  // Arduino SW version
  Serial.print(F("Clock frequency "));
  Serial.print(F_CPU / 1000000);  // Oscillator frequency
  Serial.println(F(" MHz"));
  Serial.println();
  Serial.println("CoreMark measures how quickly your processor can manage linked");
  Serial.println("lists, compute matrix multiply, and execute state machine code.");
  Serial.println();
  Serial.println("Iterations/Sec is the main benchmark result, higher numbers are better");
  Serial.println("Running.... (usually requires 12 to 20 seconds)");
  Serial.println();
  delay(250);
  coremark_main();  // Run the benchmark  :-)
}

void loop() {}

// CoreMark calls this function to print results.
extern "C" int ee_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  for (; *format; format++) {
    if (*format == '%') {
      bool islong = false;
      format++;
      if (*format == '%') {
        Serial.print(*format);
        continue;
      }
      if (*format == '-') format++;                       // ignore size
      while (*format >= '0' && *format <= '9') format++;  // ignore size
      if (*format == 'l') {
        islong = true;
        format++;
      }
      if (*format == '\0') break;
      if (*format == 's') {
        Serial.print((char *)va_arg(args, int));
      } else if (*format == 'f') {
        Serial.print(va_arg(args, double));
      } else if (*format == 'd') {
        if (islong) Serial.print(va_arg(args, long));
        else Serial.print(va_arg(args, int));
      } else if (*format == 'u') {
        if (islong) Serial.print(va_arg(args, unsigned long));
        else Serial.print(va_arg(args, unsigned int));
      } else if (*format == 'x') {
        if (islong) Serial.print(va_arg(args, unsigned long), HEX);
        else Serial.print(va_arg(args, unsigned int), HEX);
      } else if (*format == 'c') {
        Serial.print(va_arg(args, int));
      }
    } else {
      if (*format == '\n') Serial.print('\r');
      Serial.print(*format);
    }
  }
  va_end(args);
  return 1;
}

// CoreMark calls this function to measure elapsed time
extern "C" uint32_t Arduino_millis(void) {
  return millis();
}
