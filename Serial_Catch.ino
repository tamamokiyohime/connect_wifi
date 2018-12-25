void Serial_catch() {
  while (Serial.available()) {
    char inChar = Serial.read();
    inputstring += inChar;
    boolean checksum = true;
    if (inChar == '\r') {
      input_complete = true;
      for (int i = 0; i < inputstring.length() - 1; i++) {
        if (inputstring[i] > 58 || inputstring[i] < 46) {
          if (inputstring[i] != 44) {
            checksum = false;
          }
        }
      }

    }
    if (!checksum) {
      input_clear();
      Serial.println("String Error");
    }
  }
}

void input_clear() {
  input_complete = false;
  inputstring = "";
}

