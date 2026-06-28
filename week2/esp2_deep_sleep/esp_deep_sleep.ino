/**
 * @file esp32_deep_sleep.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 2 Q6 - Low-power ESP32 state configuration deploying 
 * RTC-backed timer wakeup vectors to optimize power budgets.
 */

// Define the factor to convert microseconds to seconds
#define uS_TO_S_FACTOR 1000000ULL  
// Duration the ESP32 will remain asleep in deep sleep mode (e.g., 10 seconds)
#define TIME_TO_SLEEP  10        

// Store data in RTC Slow Memory so it survives deep sleep power-downs
RTC_DATA_ATTR int bootCount = 0;

/*
Method to print the reason by which the ESP32 has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_TIMER : 
      Serial.println("Wakeup caused by numeric RTC hardware timer interrupt."); 
      break;
    case ESP_SLEEP_WAKEUP_EXT0 : 
      Serial.println("Wakeup caused by external signal using RTC_IO peripheral."); 
      break;
    case ESP_SLEEP_WAKEUP_EXT1 : 
      Serial.println("Wakeup caused by external signal using RTC_CNTL peripheral."); 
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : 
      Serial.println("Wakeup caused by capacitive touchpad sensing interrupt."); 
      break;
    case ESP_SLEEP_WAKEUP_ULP : 
      Serial.println("Wakeup caused by Ultra Low Power (ULP) co-processor program."); 
      break;
    default : 
      Serial.printf("Wakeup was not caused by deep sleep routines: %d\n", wakeup_reason); 
      break;
  }
}

void setup(){
  Serial.begin(115200);
  delay(1000); // Takeoff delay buffer to let Serial Monitor settle

  // Increment boot number and print it on every single wakeup cycle
  ++bootCount;
  Serial.println("------------------------------------");
  Serial.print("Boot Cycle Counter Tracker: ");
  Serial.println(bootCount);

  // Print the structural reason why the device just woke up
  print_wakeup_reason();

  Serial.printf("ESP32 active core task processing execution for 3 seconds...\n");
  delay(3000); // Simulate processing active sensor work / transmitting radio data

  // 1. Configure the internal RTC clock counter as the active wakeup source
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for " + String(TIME_TO_SLEEP) + " Seconds.");
  
  // 2. Shut down core power planes and enter authentic deep sleep state
  Serial.println("Entering Deep Sleep Mode Now. Goodnight!");
  Serial.println("------------------------------------");
  Serial.flush(); // Ensure all serial bytes are fully sent before cores power down
  
  esp_deep_sleep_start();
  
  // This line will NEVER execute because the CPU completely powers off at deep sleep entry.
  Serial.println("This will never be printed.");
}

void loop(){
  // The loop function remains completely empty because the execution thread restarts at setup() upon wakeup.
}