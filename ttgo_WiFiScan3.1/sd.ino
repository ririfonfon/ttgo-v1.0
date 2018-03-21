void sd_init() {
  LOG("Initializing SD card...");

  tft.println("Initializing SD card...");
  /* initialize SD library with SPI pins */
  if (!SD.begin(13, 15, 2, 14)) {         //T1:13,15,2,14  T2: 23,5,19,18
    LOG("initialization failed!");

    tft.println("initialization failed!");
    delay(1000);
    return;
  }
  LOG("initialization done.");

  tft.println("initialization done.");
  /* Begin at the root "/" */
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
    LOG("error opening test.txt");

  }
}

void printDirectory(File dir, int numTabs) {
  tft_clear_white();
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      LOG('\t');

      tft.println('\t');
    }
    // Print the name
    LOG(entry.name());

    tft.print(entry.name());
    /* Recurse for directories, otherwise print the file size */
    if (entry.isDirectory()) {
      LOG("/");

      tft.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      /* files have sizes, directories do not */
      LOG("\t\t");
      LOGINL(entry.size());

      tft.print("\t\t");
      tft.println(entry.size());
    }

    entry.close();
  }
  while (!button3.onPressed()) {
  }
}//printDirectory
