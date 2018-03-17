void sd_init() {
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
}

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
