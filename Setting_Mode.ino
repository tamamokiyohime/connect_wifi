void setting_mode() {
  Serial.println("Waiting for Setting");
  String settinginput = "";
  settinginput.reserve(20);
  boolean finish = false;
  boolean settingStrFin = false;

  while (!finish) {
    while (Serial.available()) {
      char inChar = Serial.read();
      settinginput += inChar;
      if (inChar == '\r') {
        settingStrFin = true;
      }
      while (settingStrFin) {
        char string_array[settinginput.length() + 1];
        char *function, *content;
        settinginput.toCharArray(string_array, settinginput.length());
        function  = strtok(string_array, ",");
        content   = strtok(NULL, ",");
        
        switch (function[0]){
          case 'B':
          Serial.print("WiFi_SSID = ");
          break;
          case 'C':
          Serial.print("WiFi_Pass = ");
          break;
          case 'D':
          Serial.print("DB_IP = ");
          break;
          case 'E':
          Serial.print("DB_Port = ");
          break;
          case 'F':
          Serial.print("DB_ID = ");
          break;
          case 'G':
          Serial.print("DB_Pass = ");
          break;
          case 'H':
          break;
          case 'I':
          break;
          case 'Z':
          Serial.print("Finish");
          finish = true;
          break;
          default:
          Serial.println("ERROR");
          break;
        }
        
          Serial.println(content);
          settinginput = "";
          settingStrFin = false;
      }
    }
  }
}

