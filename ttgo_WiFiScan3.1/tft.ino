void tft_clear_white() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
}//tftclear

void tft_wifi() {
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

void tft_f_init() {
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

void tft_f_base() {
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

void tft_f_wifi() {
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

void tft_f_wifi_end() {
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

void tft_wifi_base() {
  tft_clear_white();
  tft.print(n);
  tft.println(" networks found");
}//tft_wifi_base()

void tft_wifi_list() {
  tft_wifi_base();
  if (n >= wifi_end) {
    tft_wifi_list_next ();

    while (menu == 1) {
      if (button1.onPressed()) {
        tft_wifi_list_back ();
      }
      if (button2.onPressed()) {
        tft_wifi_list_next ();
      }
      if (button3.onPressed()) {
        menu = 0;
        tft_menu();
      }
    }

  } else if (n <= wifi_end) {
    wifi_end = n;
    for ( i = wifi_start; i < wifi_end; ++i) {
      tft_wifi();
    }
    tft_f_wifi_end();
    while (menu == 1) {
      if (button1.onPressed()) {
        tft_wifi_list_back ();
      }
      if (button2.onPressed()) {
        scan_wifi();
      }
      if (button3.onPressed()) {
        tft_menu();
      }
    }
  }
}//tftprint_wifilist

void tft_wifi_list_next () {
  tft_clear_white();
  tft_wifi_base();
  tft_f_wifi();
  wifi_start += 14;
  wifi_end += 14;
  for ( i = wifi_start; i < wifi_end; ++i) {
    tft_wifi();
  }
}//tftprint_wifilist_next

void tft_wifi_list_back () {
  tft_clear_white();
  tft_wifi_base();
  tft_f_wifi();
  wifi_start -= 14;
  wifi_end -= 14;
  for ( i = wifi_start; i < wifi_end; ++i) {
    tft_wifi();
  }
}//tftprint_wifilist_back

void tft_menu() {
  scroll_range = 2;
  tft_menu_scroll();
  while (!scroll_range < scroll_range) {
    if (button1.onPressed()) {
      tft_menu_down();
    }
    if (button2.onPressed()) {
      tft_menu_up();
    }
    if (button3.onPressed()) {
      tft_menu_enter();
    }
  }
}//tft_meu

void tft_menu_down() {
  scroll -= 1;
  if (scroll < 1) scroll = scroll_range;
  tft_menu_scroll();
}//tft_menu_down

void tft_menu_up() {
  scroll += 1;
  if (scroll > scroll_range) scroll = 1;
  tft_menu_scroll();
}//tft_menu_up

void tft_menu_enter() {
  if (scroll == 1) {
    menu = 1;
    scan_wifi();
  } else if (scroll == 2) {
    menu = 2;
    sd_init();
  }
}//tft_menu_enter

void tft_menu_scroll() {
  tft_clear_white();
  tft_f_base();
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
}//tft_menu_scroll

