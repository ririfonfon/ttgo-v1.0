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
  tft.setCursor(9, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(Up)");
  tft.setCursor(48, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(Down)");
  tft.setCursor(87, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(Enter)");
  tft.setCursor(0, 8);
}//tftfonction_init

void tftfonction_wifi() {
  tft.setCursor(10, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(Back)");
  tft.setCursor(50, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(Next)");
  tft.setCursor(90, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(Scan)");
  tft.setCursor(0, 8);
}//tftfonction_init

void tftprint_wifibase() {
  tftclear_white();
  tft.print(n);
  tft.println(" networks found");
  tftfonction_init();
}

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
      if (button2.isPressed()) {
#ifdef DEBUG
        Serial.println("(button2.onPressed())");
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
