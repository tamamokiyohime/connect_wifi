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
  Serial.println("Connecting to database...");
  if (database.connect(server_addr, 3306, user, password)) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
  else {
    Serial.println("Connection failed.");
  }

}
