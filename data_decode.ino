void data_decode() {
  int len = inputstring.length();
  char string_array[len + 1];
  char *date, *times, *temp, *K_temp, *pressure, *humi, *CO2, *flat, *flon, *alti, *EC, *TDS, *SAL, *GRAV, *pH;

  inputstring.toCharArray(string_array, len);
  date      = strtok(string_array, ",");
  times      = strtok(NULL, ",");
  temp      = strtok(NULL, ",");
  K_temp    = strtok(NULL, ",");
  pressure  = strtok(NULL, ",");
  humi      = strtok(NULL, ",");
  CO2       = strtok(NULL, ",");
//  flat      = strtok(NULL, ",");
//  flon      = strtok(NULL, ",");
//  alti      = strtok(NULL, ",");
  EC        = strtok(NULL, ",");
  TDS       = strtok(NULL, ",");
  SAL       = strtok(NULL, ",");
  GRAV      = strtok(NULL, ",");
  pH        = strtok(NULL, ",");
  
  //    temp_F      = atof(temp);
  //    K_temp_F    = atof(K_temp);
  //    pressure_F  = atof(pressure);
  //    flat_F      = atof(flat);
  //    flon_F      = atof(flon);
  //    alti_F      = atof(alti);
  //    EC_F        = atof(EC);
  //    TDS_F       = atof(TDS);
  //    SAL_F       = atof(SAL);
  //    GRAV_F      = atof(GRAV);
  //    humi_I      = atoi(humi);
  //    CO2_I       = atoi(CO2);
  //    pH_F        = atof(pH);

  Serial.println("Recording data.");

  sprintf(query, INSERT_DATA, date, times, temp, K_temp, pressure, humi, CO2, EC, TDS, SAL, GRAV, pH);
//  Serial.println(query);

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&database);
  cur_mem->execute(query);
  delete cur_mem;
}

