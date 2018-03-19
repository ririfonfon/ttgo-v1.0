void tftclear_white() {
#ifdef DEBUG
  Serial.println("tftclear_white()");
#endif
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
}//tftclear

void tftprint_wifi() {
#ifdef DEBUG
  Serial.println("tftprint_wifi()");
#endif
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
#ifdef DEBUG
  Serial.println("tftfonction_init()");
#endif
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

void tftfonction_base() {
#ifdef DEBUG
  Serial.println("tftfonction_base()");
#endif
  tft.setCursor(7, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(Down)");
  tft.setCursor(48, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(Up)");
  tft.setCursor(82, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(Enter)");
  tft.setCursor(0, 8);
}//tftfonction_init

void tftfonction_wifi() {
#ifdef DEBUG
  Serial.println("tftfonction_wifi()");
#endif
  tft.setCursor(8, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(Back)");
  tft.setCursor(48, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(Next)");
  tft.setCursor(88, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(Scan)");
  tft.setCursor(0, 8);
}//tftfonction_init

void tftfonction_wifi_end() {
#ifdef DEBUG
  Serial.println("tftfonction_wifi_end()");
#endif
  tft.setCursor(8, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(Back)");
  tft.setCursor(48, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(Scan)");
  tft.setCursor(88, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(Menu)");
  tft.setCursor(0, 8);
}//tftfonction_init

void tftprint_wifibase() {
#ifdef DEBUG
  Serial.println("tftprint_wifibase()");
#endif
  tftclear_white();
  tft.print(n);
  tft.println(" networks found");
}

void tftprint_wifilist() {
#ifdef DEBUG
  Serial.println("tftprint_wifilist()");
#endif
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
    tftprint_wifilist_next ();
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
#ifdef DEBUG
    Serial.println("///////////");
#endif
    tftfonction_wifi_end();
#ifdef DEBUG
    Serial.println("***********");
#endif
    while (wifi_end > wifi_end) {
#ifdef DEBUG
      Serial.println("while (wifi_end > wifi_end)");
#endif
      if (button1.onPressed()) {
#ifdef DEBUG
        Serial.println("(button1.tftprint_wifilist_back())");
#endif
        tftprint_wifilist_back ();
      }
      if (button2.onPressed()) {
#ifdef DEBUG
        Serial.println("(button2.scan_wifi())");
#endif
        scan_wifi();
      }
      if (button3.onPressed()) {
#ifdef DEBUG
        Serial.println("(button3.tft_menu())");
#endif
        tft_menu();
      }
    }
  }
}//tftprint_wifilist

void tftprint_wifilist_next () {
#ifdef DEBUG
  Serial.println("tftprint_wifilist_next ()");
#endif
  tftclear_white();
  tftprint_wifibase();
  tftfonction_wifi();
  wifi_start += 14;
  wifi_end += 14;
  for ( i = wifi_start; i < wifi_end; ++i) {
    tftprint_wifi();
  }
}//tftprint_wifilist_next

void tftprint_wifilist_back () {
#ifdef DEBUG
  Serial.println("tftprint_wifilist_back ()");
#endif
  tftclear_white();
  tftprint_wifibase();
  tftfonction_wifi_end();
  wifi_start -= 14;
  wifi_end -= 14;
  for ( i = wifi_start; i < wifi_end; ++i) {
    tftprint_wifi();
  }
}//tftprint_wifilist_back

void tft_menu() {
  scroll_range = 2;
  tft_menu_menu();
  while (!scroll_range < scroll_range) {
    if (button1.onPressed()) {
#ifdef DEBUG
      Serial.println("(button1.onPressed())");
#endif
      tft_menu_down();
    }
    if (button2.onPressed()) {
#ifdef DEBUG
      Serial.println("(button2.onPressed())");
#endif
      tft_menu_up();
    }
    if (button3.onPressed()) {
#ifdef DEBUG
      Serial.println("(button3.onPressed())");
#endif
      tft_menu_enter();
    }
  }
}//tft_meu

void tft_menu_down() {
#ifdef DEBUG
  Serial.println("(tft_menu_down())");
#endif
  scroll -= 1;
  if (scroll < 1) scroll = scroll_range;
  tft_menu_menu();
}//tft_menu_down

void tft_menu_up() {
#ifdef DEBUG
  Serial.println("(tft_menu_up())");
#endif
  scroll += 1;
  if (scroll > scroll_range) scroll = 1;
#ifdef DEBUG
  Serial.print("scroll= ");
  Serial.println(scroll);
#endif
  tft_menu_menu();
}//tft_menu_up

void tft_menu_enter() {
#ifdef DEBUG
  Serial.println("(tft_menu_enter())");
#endif
  if (scroll == 1) {
    scan_wifi();
  } else if (scroll == 2) {
    sd_init();
  }
}//tft_menu_enter

void tft_menu_menu() {
#ifdef DEBUG
  Serial.println("tft_menu_menu()");
#endif
  tftclear_white();
  tftfonction_base();
  if (scroll == 1) {
    tft.setCursor(0, 8);
    tft.setTextColor(ST7735_RED);
    tft.println("->Wifi Scan");
    tft.setTextColor(ST7735_WHITE);
    tft.println("  SD");
  } else if (scroll == 2) {
    tft.setCursor(0, 8);
    tft.setTextColor(ST7735_WHITE);
    tft.println("  Wifi Scan");
    tft.setTextColor(ST7735_RED);
    tft.println("->SD");
  }
}//tft_menu_menu

