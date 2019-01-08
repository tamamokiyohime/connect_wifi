void Serial_catch() {
  while (Serial.available()) {
    char inChar = Serial.read();
    inputstring += inChar;
    boolean checksum = true;
    int commacount = 0;
    if (inChar == '\r') {
      input_complete = true;
      for (int i = 0; i < inputstring.length() - 1; i++) {
        if (inputstring[i] > 58 || inputstring[i] < 46) {
          if (inputstring[i] != 44) {
            checksum = false;
          }
          
        }
        if( inputstring[i] == 44){
           commacount ++; 
          }
      }
      if(commacount != 12){
        checksum = false;
      }
    }
    if (!checksum) {
      input_clear();
      Serial.println("String Error");
    }
    delay(0);
  }
}

void input_clear() {
  input_complete = false;
  inputstring = "";
}

void serial_flush(){
  while(Serial.available()){
    Serial.read();
  }
}

