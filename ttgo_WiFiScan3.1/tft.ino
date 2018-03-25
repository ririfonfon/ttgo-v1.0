void tft_clear_white() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
}//tft_clear_white

void tft_wifi() {
  tft.setTextColor(ST7735_WHITE);
  tft.print(i + 1);
  tft.print(":");
  tft.print(WiFi.channel(i));
  tft.print(":");
  tft.print(WiFi.SSID(i));
  tft.print("(");
  tft.print(WiFi.RSSI(i));
  tft.print(")");
  tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
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
  scroll_range = 3;
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
    sd_list();
  } else if (scroll == 3) {
    menu = 3;
    tft_clear_white();
    tft_f_init();
    tft_bouton();
    LOG("tft_menu_btn");
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
    tft.println("  Bouton");
  } else if (scroll == 2) {
    tft.setCursor(0, 8);
    tft.setTextColor(ST7735_WHITE);
    tft.println("  Wifi Scan");
    tft.setTextColor(ST7735_RED);
    tft.println("->SD");
    tft.setTextColor(ST7735_WHITE);
    tft.println("  Bouton");
  } else if (scroll == 3) {
    tft.setCursor(0, 8);
    tft.setTextColor(ST7735_WHITE);
    tft.println("  Wifi Scan");
    tft.println("  SD");
    tft.setTextColor(ST7735_RED);
    tft.println("->Bouton");
  }
}//tft_menu_scroll

void tft_sd_base() {
  tft.setCursor(8, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("(.)");
  tft.setCursor(48, 121);
  tft.setTextColor(ST7735_GREEN);
  tft.print("(.)");
  tft.setCursor(88, 121);
  tft.setTextColor(ST7735_BLUE);
  tft.print("(Menu)");
  tft.setCursor(0, 8);
  tft.setTextColor(ST7735_WHITE);
}//tft_sd_base()

void tft_bouton() {
  while (!button1.isPressed() || !button2.isPressed()) {
    if (count_btn > 13) {
      count_btn = 0;
      tft_clear_white();
      tft_f_init();
    }
    //    if (button1.onPressed()) {
    //      count_btn += 1;
    //      tft.println("1 onPressed");
    //    }
    //    if (button2.onPressed()) {
    //      count_btn += 1;
    //      tft.println("2 onPressed");
    //    }
    //    if (button3.onPressed()) {
    //      count_btn += 1;
    //      tft.println("3 onPressed");
    //    }
    //        if (button1.setDebounceTimeout(1000)) {
    //          count_btn += 1;
    //          tft.println("1 setDebounceTimeout");
    //        }
    //        if (button2.setDebounceTimeout(1000)) {
    //          count_btn += 1;
    //          tft.println("2 setDebounceTimeout");
    //        }
    //        if (button3.setDebounceTimeout(1000)) {
    //          count_btn += 1;
    //          tft.println("3 setDebounceTimeout");
    //        }
    if (button1.onReleased()) {
      count_btn += 1;
      tft.println("1 onReleased");
    }
    if (button2.onReleased()) {
      count_btn += 1;
      tft.println("2 onReleased");
    }
    if (button3.onReleased()) {
      count_btn += 1;
      tft.println("3 onReleased");
    }
    //    if (button1.isReleased()) tft.print("1 isReleased");
    //    if (button2.isReleased()) tft.print("2 isReleased");
    //    if (button3.isReleased()) tft.print("3 isReleased");
    if (button1.onLongPressed()) {
      count_btn += 1;
      tft.println("1 onLongPressed");
    }
    if (button2.onLongPressed()) {
      count_btn += 1;
      tft.println("2 onLongPressed");
    }
    if (button3.onLongPressed()) {
      count_btn += 1;
      tft.println("3 onLongPressed");
    }
    if (button1.onLongReleased()) {
      count_btn += 1;
      tft.println("1 onLongReleased");
    }
    if (button2.onLongReleased()) {
      count_btn += 1;
      tft.println("2 onLongReleased");
    }
    if (button3.onLongReleased()) {
      count_btn += 1;
      tft.println("3 onLongReleased");
    }
  }
  LOG("return");
  return;
}//tft_bouton

