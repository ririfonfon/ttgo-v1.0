void tftclear_white() {

  LOG("tftclear_white()");

  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
}//tftclear

void tftprint_wifi() {

  LOG("tftprint_wifi()");

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

  LOG("tftfonction_init()");

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

  LOG("tftfonction_base()");

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

  LOG("tftfonction_wifi()");

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

  LOG("tftfonction_wifi_end()");

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

  LOG("tftprint_wifibase()");

  tftclear_white();
  tft.print(n);
  tft.println(" networks found");
}

void tftprint_wifilist() {

  LOG("tftprint_wifilist()");

  tftprint_wifibase();
  if (n >= wifi_end) {

    LOG("(n >= wifi_end)");
    LOGINL("wifi_start :");
    LOG(wifi_start);
    LOGINL("wifi_end :");
    LOG(wifi_end);
    LOGINL("n :");
    LOG(n);

    tftprint_wifilist_next ();

    while (menu == 1) {

      LOG("while (wifi_end > wifi_end)");

      if (button1.onPressed()) {

        LOG("(button1.tftprint_wifilist_back())");

        tftprint_wifilist_back ();
      }
      if (button2.onPressed()) {

        LOG("(button2.tftprint_wifilist_next())");

        tftprint_wifilist_next ();
      }
      if (button3.onPressed()) {

        LOG("(button3.tft_menu())");
        menu = 0;
        tft_menu();
      }
    }

  } else if (n <= wifi_end) {

    LOG("(n <= wifi_end)");
    LOGINL("wifi_start :");
    LOG(wifi_start);
    LOGINL("wifi_end :");
    LOG(wifi_end);
    LOGINL("n :");
    LOG(n);

    wifi_end = n;
    for ( i = wifi_start; i < wifi_end; ++i) {
      tftprint_wifi();
    }

    LOG("///////////");

    tftfonction_wifi_end();

    LOG("***********");

    while (menu == 1) {

      LOG("while (wifi_end > wifi_end)");

      if (button1.onPressed()) {

        LOG("(button1.tftprint_wifilist_back())");

        tftprint_wifilist_back ();
      }
      if (button2.onPressed()) {

        LOG("(button2.scan_wifi())");

        scan_wifi();
      }
      if (button3.onPressed()) {

        LOG("(button3.tft_menu())");

        tft_menu();
      }
    }
  }
}//tftprint_wifilist

void tftprint_wifilist_next () {

  LOG("tftprint_wifilist_next ()");

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

  LOG("tftprint_wifilist_back ()");

  tftclear_white();
  tftprint_wifibase();
  tftfonction_wifi();
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
      LOG("(button1.onPressed())");
      tft_menu_down();
    }
    if (button2.onPressed()) {
      LOG("(button2.onPressed())");
      tft_menu_up();
    }
    if (button3.onPressed()) {
      LOG("(button3.onPressed())");
      tft_menu_enter();
    }
  }
}//tft_meu

void tft_menu_down() {

  LOG("(tft_menu_down())");

  scroll -= 1;
  if (scroll < 1) scroll = scroll_range;
  tft_menu_menu();
}//tft_menu_down

void tft_menu_up() {

  LOG("(tft_menu_up())");

  scroll += 1;
  if (scroll > scroll_range) scroll = 1;

  LOGINL("scroll= ");
  LOG(scroll);

  tft_menu_menu();
}//tft_menu_up

void tft_menu_enter() {

  LOG("(tft_menu_enter())");

  if (scroll == 1) {
    menu = 1;
    scan_wifi();
  } else if (scroll == 2) {
    menu = 2;
    sd_init();
  }
}//tft_menu_enter

void tft_menu_menu() {

  LOG("tft_menu_menu()");

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

