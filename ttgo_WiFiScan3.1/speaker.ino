void speaker_init() {
  SPEAKER().begin();
  SPEAKER().setVolume(20);
  SPEAKER().playMusic(startup_music, 25000);
}

