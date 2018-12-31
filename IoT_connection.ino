void WiFi_connect() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void DB_connect() {
  if (database.connect(server_addr, 3306, user, password)) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);
  }

}

void DB_disconnect() {

  database.close();
  digitalWrite(LED_BUILTIN, HIGH);
}

void wifi_checkconn() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Detected WiFi Disconnect, Restarting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
  }
}

