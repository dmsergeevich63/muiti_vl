
unsigned long wifi_lastTime = millis();
unsigned long wifi_timerDelay =  180000; //120000-2 минуты //5000-5сек //180000-3мин




int wifi_i = 0;

/*void wifi_reconnect()//выполняется если идёт откладка
{

  
  if (((millis() - wifi_lastTime) > wifi_timerDelay) and wifi_debug==1) {
    if ( WiFi.status() ==  WL_CONNECTED )
    {}
    else {

      // wifi down, reconnect here
      WiFi.begin(  );
    }
    wifi_lastTime = millis();
  }


}*/
void wifi_off() { //выполняется если отладка отключена//отключает wifi через 2 минуты

  //Serial.println("wifi_reconnect");
  if (((millis() - wifi_lastTime) > wifi_timerDelay) and wifi_i ==0) { // после 2м wifi_i=1, для выполнения оключения 1 раз 
    // Serial.println("проверка, wifi выключен?");
    //Serial.println(WiFi.status());
    if ( WiFi.status() ==  WL_CONNECTED )
    {
      //Serial.println("wifi работал, выключаю");
      //Serial.println(WiFi.status());
      //if (WiFi.getPersistent() == true)
      WiFi.persistent(false);   //disable saving wifi config into SDK flash area
      WiFi.mode(WIFI_OFF); // отключаем WIFI
      WiFi.persistent(true);   //enable saving wifi config into SDK flash area
      //Serial.println("wifi_off");
      //Serial.println(WiFi.status());
    }
    wifi_i++;
    wifi_lastTime = millis();

  }


}
void wifi() { //просто подкючение wifi в setup

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WIFI_ON");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);


  }

  // else {
  //Serial.println("WIFI_OFF");
  //WiFi.mode(WIFI_OFF);
  //}
}
void ota() {
  ArduinoOTA.setHostname("Датчики входной двери(ESP32)");
  ArduinoOTA.setPassword("esp32");

  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}
