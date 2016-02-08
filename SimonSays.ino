#include "pitches.h"

int cnt = 4;
int leds[] = {7, 9, 11, 13};
int btns[] = {6, 8, 10, 12};
int tones[] = {NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4};
int buzzer = 3;
int toneWait = 500;
int silentWait = 500;
int level = 0;
int seq[100];
bool gameover = false;

void setup() {
  randomSeed(analogRead(0));
  
  for(int i = 0; i < cnt; i++) {
    pinMode(btns[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  int i, inp;

  if(gameover) return;
  
  seq[level++] = random(4);
  
  for(i = 0; i < level; i++) {
    play(seq[i], true);
  }

  for(i = 0; i < level; i++) {
    do {
      inp = read();
    } while(inp == -1);

    if(inp != seq[i]) {
      break;
    }
  }

  if(i != level) {
    gameover = true;
    
    for(i = 0; i < cnt; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }

  delay(1000);
}

void play(int i, bool silent) {
  digitalWrite(leds[i], HIGH);
  tone(buzzer, tones[i], toneWait);
  delay(toneWait);
  digitalWrite(leds[i], LOW);
  if(silent) {
    delay(silentWait);
  }
}

int read() {
  for(int i = 0; i < cnt; i++) {
    if(digitalRead(btns[i]) == HIGH) {
      play(i, false);
      return i;
    }
  }
  return -1;
}
