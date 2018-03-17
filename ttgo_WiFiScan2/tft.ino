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

void tftfonction_base() {
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

void tftprint_wifibase() {
  tftclear_white();
  tft.print(n);
  tft.println(" networks found");
}

void tftprint_wifilist() {
  tftprint_wifibase();
  tftfonction_wifi();
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
    while (!button3.onPressed()) {
      if (button3.isPressed()) {
#ifdef DEBUG
        Serial.println("(button3.onPressed())");
#endif
        scan_wifi();
        return;
      }
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
    if (button1.isPressed()) {
#ifdef DEBUG
      Serial.println("(button1.onPressed())");
#endif
      tftprint_wifilist ();
      return;
    }
  }
}//tftprint_wifilist_list

void tft_menu() {
  scroll_range = 2;
  tft_menu_menu();
  while (!scroll_range < scroll_range) {
    if (button1.onPressed()) {
#ifdef DEBUG
      Serial.println("(button1.onPressed())");
#endif
      tft_menu_down();
      //      return;
    }
    if (button2.onPressed()) {
#ifdef DEBUG
      Serial.println("(button2.onPressed())");
#endif
      tft_menu_up();
      //      return;
    }
    if (button3.onPressed()) {
#ifdef DEBUG
      Serial.println("(button3.onPressed())");
#endif
      tft_menu_enter();
      //      return;
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

