/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "WiFi.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS 16
#define TFT_RST 9  // you can also connect this to the Arduino reset
// in which case, set this #define pin to -1!
#define TFT_DC 17

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 5   // set these to be whatever pins you like!
#define TFT_MOSI 23   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define LED_BUILTIN 22

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop()
{
  Serial.println("scan start");
  digitalWrite(LED_BUILTIN, HIGH);

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  digitalWrite(LED_BUILTIN, LOW);
  if (n == 0) {
    Serial.println("no networks found");
    tft.setTextWrap(true);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print(n);
    tft.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      tft.print(i + 1);
      Serial.print(": ");
      tft.print(": ");
      Serial.print(WiFi.SSID(i));
      tft.print(WiFi.SSID(i));
      Serial.print(" (");
      tft.print(" (");
      Serial.print(WiFi.RSSI(i));
      tft.print(WiFi.RSSI(i));
      Serial.print(")");
      tft.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
