enum VendingState { STATE_IDLE, STATE_COIN_INSERTED, STATE_ITEM_SELECTED, STATE_DISPENSING };
VendingState systemState = STATE_IDLE;

const int BTN_COIN = 2;
const int BTN_SELECT = 3;
const int BTN_CANCEL = 4;

const int LED_IDLE = 8;
const int LED_COIN = 9;
const int LED_ACTIVE = 10;

void updateDisplayOutputs() {
  switch (systemState) {
    case STATE_IDLE:
      digitalWrite(LED_IDLE, HIGH); 
      digitalWrite(LED_COIN, LOW); 
      digitalWrite(LED_ACTIVE, LOW);
      break;
    case STATE_COIN_INSERTED:
      digitalWrite(LED_IDLE, LOW);  
      digitalWrite(LED_COIN, HIGH); 
      digitalWrite(LED_ACTIVE, LOW);
      break;
    case STATE_ITEM_SELECTED:
    case STATE_DISPENSING:
      digitalWrite(LED_IDLE, LOW);  
      digitalWrite(LED_COIN, LOW);  
      digitalWrite(LED_ACTIVE, HIGH);
      break;
  }
}

void transitionTo(VendingState targetState, String logReason) {
  systemState = targetState;
  Serial.print("[STATE TRANSITION] -> ");
  Serial.println(logReason);
  updateDisplayOutputs();
}

void setup() {
  Serial.begin(9600);
  
  pinMode(BTN_COIN, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_CANCEL, INPUT_PULLUP);
  
  pinMode(LED_IDLE, OUTPUT);
  pinMode(LED_COIN, OUTPUT);
  pinMode(LED_ACTIVE, OUTPUT);

  updateDisplayOutputs();
  Serial.println("=== VENDING MACHINE STATE ENGINE ACTIVE ===");
}

void loop() {
  bool coinPressed   = (digitalRead(BTN_COIN) == LOW);
  bool selectPressed = (digitalRead(BTN_SELECT) == LOW);
  bool cancelPressed = (digitalRead(BTN_CANCEL) == LOW);

  switch (systemState) {
    case STATE_IDLE:
      if (coinPressed) {
        delay(200); 
        transitionTo(STATE_COIN_INSERTED, "IDLE -> COIN_INSERTED");
      }
      break;

    case STATE_COIN_INSERTED:
      if (selectPressed) {
        delay(200);
        transitionTo(STATE_ITEM_SELECTED, "COIN_INSERTED -> ITEM_SELECTED");
      } 
      else if (cancelPressed) {
        delay(200);
        transitionTo(STATE_IDLE, "COIN_INSERTED -> IDLE (Refund)");
      }
      break;

    case STATE_ITEM_SELECTED:
      transitionTo(STATE_DISPENSING, "ITEM_SELECTED -> DISPENSING");
      break;

    case STATE_DISPENSING:
      Serial.println("Action: Dispensing item... Please wait.");
      delay(2000); 
      transitionTo(STATE_IDLE, "DISPENSING -> IDLE (Cycle Complete)");
      break;
  }
}