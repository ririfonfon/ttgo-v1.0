void sd_init() {
  LOG("Initializing SD card...");

  tft.println("Initializing SD card...");
  /* initialize SD library with SPI pins */
  if (!SD.begin(13, 15, 2, 14)) {         //T1:13,15,2,14  T2: 23,5,19,18
    LOG("initialization failed!");
    sd = 0;
    tft.println("initialization failed!");
    delay(1000);
    return;
  }
  LOG("initialization done.");
  sd = 1;
  tft.println("initialization done.");
  /* Begin at the root "/" */
}

void printDirectory(File dir, int numTabs) {

  tft_clear_sd_white(dir.name());
  tft_sd_base();
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      LOG('\t');

      tft.print('\t');
    }
    // Print the name
    LOG(entry.name());
    tft.print(entry.name());

    /* Recurse for directories, otherwise print the file size */
    if (entry.isDirectory()) {
      LOG("/");
      tft.print("/ ");
      printDirectory(entry, numTabs + 1);
    } else {
      /* files have sizes, directories do not */

      LOGINL(entry.size());

      tft.println(entry.size());
    }

    entry.close();
  }
  while (menu == 2) {
    if (button1.onPressed()) {
      return;
    }
    if (button2.onPressed()) {
      return;
    }
    if (button3.onPressed()) {
      menu = 1;
      tft_menu();
    }
  }

}//printDirectory

void sd_list() {
  if (sd == 0) sd_init();

  root = SD.open("/");
  if (root) {
    printDirectory(root, 0);
    root.close();
  } else {
    LOG("error opening test.txt");
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
    LOG("error opening test.txt");
  }
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
    LOG("error opening test.txt");

  }

}//sd_list

void tft_clear_sd_white(String directory) {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(directory);
}//tft_clear_sd_white

