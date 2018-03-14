
#include "WiFi.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS 16
#define TFT_RST 9
#define TFT_DC 17
#define TFT_SCLK 5
#define TFT_MOSI 23
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define LED_BUILTIN 22

#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Button.h> // https://github.com/alextaujenis/RBD_Button

// input pullup enabled by default
RBD::Button button1(35);//btn 1
RBD::Button button2(34);//btn 2
RBD::Button button3(39);//btn 3

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
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Setup done");
}//setup

void loop()
{
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("scan start");
  digitalWrite(LED_BUILTIN, HIGH);
  int n = WiFi.scanNetworks();
  tft.println("scan done");
  digitalWrite(LED_BUILTIN, LOW);
  if (n == 0) {
    tft.setTextWrap(true);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.println("no networks found");
  } else {
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print(n);
    tft.println(" networks found");
    if (n <= 15) {
      for (int i = 0; i < n; ++i) {
        tftprint()
      }
    } else if (n >= 16) {
      for (int i = 0; i < 15; ++i) {
        tftprint()
      }
    }
  }


  // Wait a bit before scanning again
  delay(5000);
}//loop

void tftprint() {
  tft.print(i + 1);
  tft.print(": ");
  tft.print(WiFi.SSID(i));
  tft.print(" (");
  tft.print(WiFi.RSSI(i));
  tft.print(")");
  tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
  delay(10);
}//tftprint

