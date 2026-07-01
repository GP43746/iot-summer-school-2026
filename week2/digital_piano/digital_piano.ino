const int BUZZER_PIN = 11;

const int KEY_DO = 2;
const int KEY_RE = 3;
const int KEY_MI = 4;
const int KEY_FA = 5;

const int NOTE_DO = 262;
const int NOTE_RE = 294;
const int NOTE_MI = 330;
const int NOTE_FA = 349;
const int NOTE_SOL_CHORD = 392;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(KEY_DO, INPUT_PULLUP);
  pinMode(KEY_RE, INPUT_PULLUP);
  pinMode(KEY_MI, INPUT_PULLUP);
  pinMode(KEY_FA, INPUT_PULLUP);
}

void loop() {
  bool btnDo = (digitalRead(KEY_DO) == LOW);
  bool btnRe = (digitalRead(KEY_RE) == LOW);
  bool btnMi = (digitalRead(KEY_MI) == LOW);
  bool btnFa = (digitalRead(KEY_FA) == LOW);

  int activeKeysCount = btnDo + btnRe + btnMi + btnFa;

  if (activeKeysCount >= 2) {
    tone(BUZZER_PIN, NOTE_SOL_CHORD);
  } 
  else if (activeKeysCount == 1) {
    if (btnDo) tone(BUZZER_PIN, NOTE_DO);
    else if (btnRe) tone(BUZZER_PIN, NOTE_RE);
    else if (btnMi) tone(BUZZER_PIN, NOTE_MI);
    else if (btnFa) tone(BUZZER_PIN, NOTE_FA);
  } 
  else {
    noTone(BUZZER_PIN);
  }
}