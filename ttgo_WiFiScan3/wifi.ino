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
