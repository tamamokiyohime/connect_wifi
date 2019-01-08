#include <ESP8266WiFi.h>                  // Use this for WiFi instead of Ethernet.h
#include <SPI.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#define STASSID "CAGD-LAB"
#define STAPSK  "1102049733"
#define timeout_setting 10000

String inputstring = "";
boolean input_complete = false;
boolean timeout = false;

IPAddress server_addr(140, 117, 59, 26); // IP of the MySQL *server* here
char user[] = "test";              // MySQL user login username
char password[] = "password";        // MySQL user login password
const char* ssid     = STASSID;
const char* pass = STAPSK;

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection database((Client *)&client);
char INSERT_DATA[] = "INSERT INTO drifter.sensor_%02d (date,time,temperature,K_temperature,pressure,humidity,valCO2,EC,TDS,SAL,GRAV,pH) VALUES ('%s','%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)";
char query[512];
boolean connection = true;

String date_S, time_S;
float temp_F, K_temp_F, pressure_F, flat_F, flon_F, alti_F, EC_F, TDS_F, SAL_F, GRAV_F, pH_F;

int humi_I, CO2_I;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  inputstring.reserve(256);
  for (int i = 0; i < 3 ; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  serial_flush();

  //setting_mode();
  //WiFi_connect();
  //DB_connect();
}


void loop() {

  Serial_catch();

  if (input_complete) {
    wifi_checkconn();
    //WiFi_connect();
    if (!timeout)
    {
      DB_connect();
      if(connection)
      {
      data_decode();
      }else{
        Serial.println("Database Fatal Error");
      }
      input_clear();
      DB_disconnect();
    }else{
      Serial.println("WiFi Connection Timeout! Abort....");
      timeout = false;
    }

    WiFi.disconnect();
    serial_flush();

  }
  delay(0);
}


