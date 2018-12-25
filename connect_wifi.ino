#include <ESP8266WiFi.h>                  // Use this for WiFi instead of Ethernet.h
#include <SPI.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#define STASSID "kiyohime"
#define STAPSK  "wakaba0331"

String inputstring = "";
boolean input_complete = false;

IPAddress server_addr(140, 117, 59, 26); // IP of the MySQL *server* here
char user[] = "test";              // MySQL user login username
char password[] = "password";        // MySQL user login password
const char* ssid     = STASSID;
const char* pass = STAPSK;

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection database((Client *)&client);
//char INSERT_DATA[] = "INSERT INTO drifter.sensor_01 (D,T,TP,KTP,P,H,C,FA,FO,EC,TDS,SAL,GRAV,pH) VALUES ('%s','%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)";
char INSERT_DATA[] = "INSERT INTO drifter.sensor_01 (date,time,temperature,K_temperature,pressure,humidity,valCO2,flat,flon,EC,TDS,SAL,GRAV,pH) VALUES ('%s','%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)";
char query[512];

String date_S, time_S;
float temp_F, K_temp_F, pressure_F, flat_F, flon_F, alti_F, EC_F, TDS_F, SAL_F, GRAV_F, pH_F;

int humi_I, CO2_I;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  inputstring.reserve(110);
  delay(500);
  
  setting_mode();
  WiFi_connect();
  DB_connect();
}
  

void loop() {
  Serial_catch();
  
  if (input_complete) {
    data_decode();
    input_clear();

  }
}


