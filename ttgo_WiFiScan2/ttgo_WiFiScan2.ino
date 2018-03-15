
#define DEBUG 1

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
  tft.println("Setup done");
  tftfonction_init();
  SPEAKER().begin();
  SPEAKER().setVolume(20);
  SPEAKER().playMusic(startup_music, 25000);
#ifdef DEBUG
  Serial.println("Initializing SD card...");
#endif
  tft.println("Initializing SD card...");
  /* initialize SD library with SPI pins */
  if (!SD.begin(13, 15, 2, 14)) {         //T1:13,15,2,14  T2: 23,5,19,18
#ifdef DEBUG
    Serial.println("initialization failed!");
#endif
    tft.println("initialization failed!");
    delay(1000);
    return;
  }
#ifdef DEBUG
  Serial.println("initialization done.");
#endif
  tft.println("initialization done.");
  /* Begin at the root "/" */
  root = SD.open("/");
  if (root) {
    printDirectory(root, 0);
    root.close();
  } else {
#ifdef DEBUG
    Serial.println("error opening test.txt");
#endif
  }
  /* open "test.txt" for writing */
  root = SD.open("test.txt", FILE_WRITE);
  /* if open succesfully -> root != NULL
    then write string "Hello world!" to it
  */
  if (root) {
    root.println("Hello world!");
    root.flush();
    /* close the file */
    root.close();
  } else {
    /* if the file open error, print an error */
#ifdef DEBUG
    Serial.println("error opening test.txt");
#endif
  }
  delay(1000);
  /* after writing then reopen the file and read it */
  root = SD.open("test.txt");
  if (root) {
    /* read from the file until there's nothing else in it */
    while (root.available()) {
      /* read the file and print to Terminal */
      Serial.write(root.read());
    }
    root.close();
  } else {
#ifdef DEBUG
    Serial.println("error opening test.txt");
#endif
  }
#ifdef DEBUG
  Serial.println("done!");
#endif
}//setup

void loop()
{
  scan_wifi();
  SPEAKER().update();
}//loop

void tftclear_white() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
}//tftclear

void tftprint_wifi() {
  tft.setTextColor(ST7735_WHITE);
  tft.print(i + 1);
  tft.print(": ");
  tft.print(WiFi.SSID(i));
  tft.print(" (");
  tft.print(WiFi.RSSI(i));
  tft.print(")");
  tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
  delay(10);
}//tftprint

void tftfonction_init() {
  tft.setCursor(10, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(1)");
  tft.setCursor(50, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(2)");
  tft.setCursor(90, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(3)");
  tft.setCursor(0, 8);
}//tftfonction_init

void printDirectory(File dir, int numTabs) {
  tftclear_white();
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
#ifdef DEBUG
      Serial.print('\t');
#endif
      tft.println('\t');
    }
    // Print the name
#ifdef DEBUG
    Serial.print(entry.name());
#endif
    tft.print(entry.name());
    /* Recurse for directories, otherwise print the file size */
    if (entry.isDirectory()) {
#ifdef DEBUG
      Serial.println("/");
#endif
      tft.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      /* files have sizes, directories do not */
#ifdef DEBUG
      Serial.print("\t\t");
      Serial.println(entry.size());
#endif
      tft.print("\t\t");
      tft.println(entry.size());
    }

    entry.close();
  }
  while (!button3.onPressed()) {
  }
}//printDirectory

void tftprint_wifibase() {
  tftclear_white();
  tft.print(n);
  tft.println(" networks found");
  tftfonction_init();
}

void scan_wifi() {
  tftclear_white();
  tft.setCursor(0, 8);
  tft.setTextColor(ST7735_RED);
  tft.print("scan start");
  digitalWrite(LED_BUILTIN, HIGH);
  SPEAKER().beep();
  SPEAKER().update();
  n = WiFi.scanNetworks();
  wifi_start = 0;
  wifi_end = 14;
  tft.println("scan done");
  digitalWrite(LED_BUILTIN, LOW);
  if (n == 0) {
    tftclear_white();
    tft.println("no networks found");
  } else {
    tftprint_wifilist();
  }
}//scan_wifi

void tftprint_wifilist() {
  tftprint_wifibase();
  if (n >= wifi_end) {
#ifdef DEBUG
    Serial.println("(n >= wifi_end)");
    Serial.print("wifi_start :");
    Serial.println(wifi_start);
    Serial.print("wifi_end :");
    Serial.println(wifi_end);
    Serial.print("n :");
    Serial.println(n);
#endif
    tftprint_wifilist_list ();
  } else if (n <= wifi_end) {
#ifdef DEBUG
    Serial.println("(n <= wifi_end)");
    Serial.print("wifi_start :");
    Serial.println(wifi_start);
    Serial.print("wifi_end :");
    Serial.println(wifi_end);
    Serial.print("n :");
    Serial.println(n);
#endif
    wifi_end = n;
    for ( i = wifi_start; i < wifi_end; ++i) {
      tftprint_wifi();
    }
    while (!button2.onPressed()) {
    }
    while (button2.onPressed()) {
      scan_wifi();
    }
  }
}//tftprint_wifilist

void tftprint_wifilist_list () {
  for ( i = wifi_start; i < wifi_end; ++i) {
    tftprint_wifi();
  }
  wifi_start += 14;
  wifi_end += 14;
  while (!button1.onPressed()) {
    if (button1.onPressed()) {
#ifdef DEBUG
      Serial.println("(button1.onPressed())");
#endif
      tftprint_wifilist ();
    }
  }
}//tftprint_wifilist_list


