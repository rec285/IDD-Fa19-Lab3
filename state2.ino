// This borrows code from Examples->EEPROM->eeprom_write


int endAddr;

void state2Setup() {
  digitalWrite(ledPin, LOW);
  Serial.println("Writing to EEPROM");
  
  
}

void state2Loop() {
  //if any of the pin settings for the different states differed for the different states, you could change those settings here.
  int data = analogRead(8);
  endAddr = sizeof(data);
  for (int i = 0; i < endAddr; i++) {
    EEPROM.write(i, data);
  }

  Serial.println("Audio committed to EEPROM!");
}

void doState2() {
  if (lastState != 2) state2Setup();
  state2Loop();
}
