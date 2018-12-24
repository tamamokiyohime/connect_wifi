#include <ESP8266WiFi.h>                  // Use this for WiFi instead of Ethernet.h
#include <SPI.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#define STASSID "kiyohime"
#define STAPSK  "wakaba0331"

String inputstring = "";
boolean input_complete = false;

IPAddress server_addr(140,117,59,26);  // IP of the MySQL *server* here
char user[] = "test";              // MySQL user login username
char password[] = "password";        // MySQL user login password
const char* ssid     = STASSID;
const char* pass = STAPSK;

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection database((Client *)&client);
//char INSERT_DATA[] = "INSERT INTO drifter.sensor_01 (D,T,TP,KTP,P,H,C,FA,FO,EC,TDS,SAL,GRAV,pH) VALUES ('%s','%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)";
char INSERT_DATA[] = "INSERT INTO drifter.sensor_01 (date,time,temperature,K_temperature,pressure,humidity,valCO2,flat,flon,EC,TDS,SAL,GRAV,pH) VALUES ('%s','%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)";
char query[256];

String date_S, time_S;
float temp_F, K_temp_F, pressure_F, flat_F, flon_F, alti_F, EC_F, TDS_F, SAL_F, GRAV_F, pH_F;
int humi_I, CO2_I;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  inputstring.reserve(110);
  
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

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
  
  Serial.println("Connecting to database...");
  if (database.connect(server_addr, 3306, user, password)) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
}

void loop() {
  serialEvent();
  if(input_complete){
    
    int len = inputstring.length();
    char string_array[len+1];
    char *date, *time, *temp, *K_temp, *pressure, *humi, *CO2, *flat, *flon, *alti, *EC, *TDS, *SAL, *GRAV, *pH;
    
    inputstring.toCharArray(string_array, len);
    date      = strtok(string_array, ",");
    time      = strtok(NULL, ",");
    temp      = strtok(NULL, ",");
    K_temp    = strtok(NULL, ",");
    pressure  = strtok(NULL, ",");
    humi      = strtok(NULL, ",");
    CO2       = strtok(NULL, ",");
    flat      = strtok(NULL, ",");
    flon      = strtok(NULL, ",");
    alti      = strtok(NULL, ",");
    EC        = strtok(NULL, ",");
    TDS       = strtok(NULL, ",");
    SAL       = strtok(NULL, ",");
    GRAV      = strtok(NULL, ",");
    pH        = strtok(NULL, ",");
    
  
    temp_F      = atof(temp);
    K_temp_F    = atof(K_temp);
    pressure_F  = atof(pressure);
    flat_F      = atof(flat);
    flon_F      = atof(flon);
    alti_F      = atof(alti);
    EC_F        = atof(EC);
    TDS_F       = atof(TDS);
    SAL_F       = atof(SAL);
    GRAV_F      = atof(GRAV);
    humi_I      = atoi(humi);
    CO2_I       = atoi(CO2);
    pH_F        = atof(pH);
    Serial.println("Recording data.");
  
    sprintf(query, INSERT_DATA, date, time, temp, K_temp, pressure, humi, CO2, flat, flon, EC, TDS, SAL, GRAV, pH);
    Serial.println(query);
    
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&database);
    cur_mem->execute(query);
    delete cur_mem;
    
{/*
    Serial.print(date);
    Serial.print('\t');
    Serial.print(time);
    Serial.print('\t');
    Serial.print(temp_F);
    Serial.print('\t');
    Serial.print(K_temp_F);
    Serial.print('\t');
    Serial.print(pressure_F);
    Serial.print('\t');
    Serial.print(humi_I);
    Serial.print('\t');
    Serial.print(CO2_I);
    Serial.print('\t');
    Serial.print(flat_F);
    Serial.print('\t');
    Serial.print(flon_F);
    Serial.print('\t');
    Serial.print(alti_F);
    Serial.print('\t');
    Serial.print(EC_F);
    Serial.print('\t');
    Serial.print(TDS_F);
    Serial.print('\t');
    Serial.print(SAL_F);
    Serial.print('\t');
    Serial.print(GRAV_F);
    Serial.print('\t');
    Serial.print(pH_F);
    Serial.print('\n');
*/}
  input_complete = false;
  inputstring = "";
    
  }

  
  
 
 
}

void serialEvent(){
  while(Serial.available()){
    char inChar = Serial.read();
    inputstring += inChar;
    boolean checksum = true;
    if(inChar == '\r'){
      input_complete = true;
      for(int i = 0; i < inputstring.length() - 1; i++){
        if(inputstring[i] > 58 || inputstring[i] < 46){
          if(inputstring[i] != 44){
          checksum = false;
          }
        }
      }
      
    }
    if(!checksum){
      input_complete = false;
      inputstring = "";
      Serial.println("String Error");
    }
  }
}

