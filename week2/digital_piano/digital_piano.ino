const int BUZZER_PIN = 11;

const int KEY_DO = 2;
const int KEY_RE = 3;
const int KEY_MI = 4;
const int KEY_FA = 5;
const int SCALE_TOGGLE_BUTTON = 6;

const int NOTE_DO_MAJ = 262; const int NOTE_DO_MIN = 261;
const int NOTE_RE_MAJ = 294; const int NOTE_RE_MIN = 293;
const int NOTE_MI_MAJ = 330; const int NOTE_MI_MIN = 311;
const int NOTE_FA_MAJ = 349; const int NOTE_FA_MIN = 349;
const int NOTE_SOL_CHORD = 392;

bool isMinorScale = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(KEY_DO, INPUT_PULLUP);
  pinMode(KEY_RE, INPUT_PULLUP);
  pinMode(KEY_MI, INPUT_PULLUP);
  pinMode(KEY_FA, INPUT_PULLUP);
  pinMode(SCALE_TOGGLE_BUTTON, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SCALE_TOGGLE_BUTTON) == LOW) {
    isMinorScale = !isMinorScale;
    delay(300);
  }

  bool btnDo = (digitalRead(KEY_DO) == LOW);
  bool btnRe = (digitalRead(KEY_RE) == LOW);
  bool btnMi = (digitalRead(KEY_MI) == LOW);
  bool btnFa = (digitalRead(KEY_FA) == LOW);

  int activeKeysCount = btnDo + btnRe + btnMi + btnFa;

  if (activeKeysCount >= 2) {
    tone(BUZZER_PIN, NOTE_SOL_CHORD);
  } 
  else if (activeKeysCount == 1) {
    if (btnDo) {
      tone(BUZZER_PIN, isMinorScale ? NOTE_DO_MIN : NOTE_DO_MAJ);
    } else if (btnRe) {
      tone(BUZZER_PIN, isMinorScale ? NOTE_RE_MIN : NOTE_RE_MAJ);
    } else if (btnMi) {
      tone(BUZZER_PIN, isMinorScale ? NOTE_MI_MIN : NOTE_MI_MAJ);
    } else if (btnFa) {
      tone(BUZZER_PIN, isMinorScale ? NOTE_FA_MIN : NOTE_FA_MAJ);
    }
  } 
  else {
    noTone(BUZZER_PIN);
  }
}