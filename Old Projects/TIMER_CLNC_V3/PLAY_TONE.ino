//==================================== Playing the tone for the timer to end ==========================

void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW

    while (elapsed_time < duration) {
      digitalWrite(speakerOut, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);
    }
  }
}


//================================== SOME TUNE SETUP THINGY ============================================
void relayStatus(bool state)
{
  if (state)
  {
    digitalWrite(speakerOut, HIGH);// have to change this to high
  }
  else
  {
    // Set up a counter to pull from melody[] and beats[]
    for (int i = 0; i < ZMAX_COUNT; i++) {
      digitalWrite(4, LOW);//GPS OFF
      tone_ = Zmelody[i];
      beat = Zbeats[i];

      duration = beat * tempo * 15; // Set up timing
      playTone();
      // A pause between notes...
      delayMicroseconds(pause);


    }
  }
  digitalWrite(speakerOut, LOW);

}
