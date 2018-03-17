
#define DEBUG 1
uint8_t scroll = 1;
uint8_t scroll_range;

#include "WiFi.h"
int i;
uint8_t wifi_start;
uint8_t wifi_end;
int n;

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

#include "Speaker.h"
#include "startup_music.h"

#include <mySD.h>
File root;

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
#endif
  pinMode(LED_BUILTIN, OUTPUT);
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tftclear_white();

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  tftfonction_init();
  speaker_init();
#ifdef DEBUG
  Serial.println("done!");
#endif
  tft.println("Setup done");
  delay(1000);
}//setup

void loop()
{
  tft_menu();
  SPEAKER().update();
}//loop












