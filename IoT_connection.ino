void WiFi_connect() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("WiFi connected @");
  Serial.println(WiFi.localIP());
}

void DB_connect() {
  int retrytimes = 0;
  while(retrytimes < 5){
    
    if (database.connect(server_addr, 3306, user, password)) {
      digitalWrite(LED_BUILTIN, LOW);
      connection = true;
      retrytimes = 5;
    }else{
      retrytimes ++;
      Serial.print("Connecting DB Fail! Retrying for ");
      Serial.print(retrytimes);
      Serial.print(" times");
      connection = false;
      DB_disconnect();
    }
  }
}

void DB_disconnect() {

  database.close();
  digitalWrite(LED_BUILTIN, HIGH);
}

void wifi_checkconn() {
  int counttime = 0;
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Detected WiFi Disconnect, Restarting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(250);
      Serial.print(".");
      counttime ++;
      if(counttime == timeout_setting/250){
        Serial.print("timeout");
        timeout = true;
        break;
      }
    }
    Serial.println();
  }
}

