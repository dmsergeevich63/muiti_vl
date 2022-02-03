void print_reset_reason(RESET_REASON reason)
{
  Serial.println( reason);
  /* {
     case 1 : Serial.println ("POWERON_RESET");break;          //1, Vbat power on reset
     case 3 : Serial.println ("SW_RESET");break;               //3, Software reset digital core
     case 4 : Serial.println ("OWDT_RESET");break;             //<4, Legacy watch dog reset digital core
     case 5 : Serial.println ("DEEPSLEEP_RESET");break;        //<5, Deep Sleep reset digital core
     case 6 : Serial.println ("SDIO_RESET");break;             //<6, Reset by SLC module, reset digital core
     case 7 : Serial.println ("TG0WDT_SYS_RESET");break;       //<7, Timer Group0 Watch dog reset digital core
     case 8 : Serial.println ("TG1WDT_SYS_RESET");break;       //<8, Timer Group1 Watch dog reset digital core
     case 9 : Serial.println ("RTCWDT_SYS_RESET");break;       //<9, RTC Watch dog Reset digital core
     case 10 : Serial.println ("INTRUSION_RESET");break;       //<10, Instrusion tested to reset CPU
     case 11 : Serial.println ("TGWDT_CPU_RESET");break;       //<11, Time Group reset CPU
     case 12 : Serial.println ("SW_CPU_RESET");break;          ///<12, Software reset CPU
     case 13 : Serial.println ("RTCWDT_CPU_RESET");break;      //<13, RTC Watch dog Reset CPU
     case 14 : Serial.println ("EXT_CPU_RESET");break;         //<14, for APP CPU, reseted by PRO CPU
     case 15 : Serial.println ("RTCWDT_BROWN_OUT_RESET");break;//<15, Reset when the vdd voltage is not stable
     case 16 : Serial.println ("RTCWDT_RTC_RESET");break;      //<16, RTC Watch dog reset digital core and rtc module
     default : Serial.println ("NO_MEAN");
    }*/
}
unsigned long r_led_lastTime = millis();
unsigned long r_led_timerDelay =  180000; //120000-2 минуты //5000-5сек //180000-3мин
void Task1code( void * pvParameters ) {
  //***//  terminal.print("Task1 running on core ");
  //***//  terminal.println(xPortGetCoreID());

  for (;;) {
    Serial.print("CPU0: ");
    print_reset_reason(rtc_get_reset_reason(0));
    Serial.print("CPU1: ");
    print_reset_reason(rtc_get_reset_reason(1));
    Serial.print("MEM: "); Serial.println(ESP.getFreeHeap());

    ledd();


    if ((millis() - r_led_lastTime) > r_led_timerDelay )
    {
      if (ploskii != 0 or babochka != 0 or  zadvijka != 0)
      {
        r_led = 1;
      }
      r_led_lastTime = millis();
    }

    // app();

  }
}



int migalka = 1;
void ledd() {
  //**//



  //if (16<=i and i<=20) i++;
  //средний
  //if (15 <= i and i <= 20) leds[i] = CHSV(counter, 255, 255);
  pixels.setBrightness(50);

  for (int i = 0; i <= 25; i++) {
    //FastLED.setBrightness(5); //5

    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //черный
    //leds[i] = CHSV(100, 0, 100); //белый //как заливка цветом, только надо везде поменять  leds[24] = CHSV(0, 0, 0); на белый
    //или можно просто убрать?
  }


  if (magnit == 0)
  {
    if (zadvijka == 1)
    {

      pixels.setPixelColor(14, pixels.Color(r, g, b));
      pixels.setPixelColor(13, pixels.Color(r, g, b));
      pixels.setPixelColor(12, pixels.Color(r, g, b));
      pixels.setPixelColor(11, pixels.Color(r, g, b));





    }


    //верхний

    if (babochka == 1 ) {
      pixels.setPixelColor(21, pixels.Color(r, g, b));
    }
    if (babochka == 2 ) {
      pixels.setPixelColor(21, pixels.Color(r, g, b));
      pixels.setPixelColor(22, pixels.Color(r, g, b));
    }
    if (babochka == 3 ) {
      pixels.setPixelColor(21, pixels.Color(r, g, b));
      pixels.setPixelColor(22, pixels.Color(r, g, b));
      pixels.setPixelColor(23, pixels.Color(r, g, b));
    }
    if (babochka == 4 ) {
      pixels.setPixelColor(21, pixels.Color(r, g, b));
      pixels.setPixelColor(22, pixels.Color(r, g, b));
      pixels.setPixelColor(23, pixels.Color(r, g, b));
      pixels.setPixelColor(24, pixels.Color(r, g, b));
    }
    //нижний



    if (ploskii == 1 ) {
      //delay(5);                 ///////////////////////////////////////////////

      pixels.setPixelColor(1, pixels.Color(r, g, b));

    }
    if (ploskii == 2 ) {
      pixels.setPixelColor(1, pixels.Color(r, g, b));

      pixels.setPixelColor(2, pixels.Color(r, g, b));

    }
    if (ploskii == 3 ) {
      pixels.setPixelColor(1, pixels.Color(r, g, b));
      pixels.setPixelColor(2, pixels.Color(r, g, b));
      pixels.setPixelColor(3, pixels.Color(r, g, b));

    }



    //полоса или три точки
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.setPixelColor(10, pixels.Color(r, g, b));
    pixels.setPixelColor(20, pixels.Color(r, g, b));
  }
  //terminal.println(brightness);
  // terminal.println(brightness1);

  /*terminal.print(ploskii);
    terminal.print(" ");
     terminal.print(zadvijka);
     terminal.print(" ");
       terminal.println(babochka);*/
  //if (counter > 200)ploskii = 0; babochka = 0; zadvijka = 0;
  //if (counter >800)ploskii = 2; babochka = 2; zadvijka = 1;
  //if(counter>500)babochka = 1;
  if (ploskii == 0 and babochka == 0 and zadvijka == 0) ////////////////////////////красный обод
  {
    //очистка
    for (int  i = 0; i < 24; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    //FastLED.setBrightness(240);

    pixels.setBrightness(255);
    //для отображения нуля на матрице
    pixels.setPixelColor(0, pixels.Color(red, 0, 0));
    pixels.setPixelColor(9, pixels.Color(red, 0, 0));
    pixels.setPixelColor(10, pixels.Color(red, 0, 0));
    pixels.setPixelColor(19, pixels.Color(red, 0, 0));
    pixels.setPixelColor(20, pixels.Color(red, 0, 0));


    pixels.setPixelColor(1, pixels.Color(red, 0, 0));
    pixels.setPixelColor(2, pixels.Color(red, 0, 0));
    pixels.setPixelColor(3, pixels.Color(red, 0, 0));
    pixels.setPixelColor(4, pixels.Color(red, 0, 0));



    pixels.setPixelColor(21, pixels.Color(red, 0, 0));
    pixels.setPixelColor(22, pixels.Color(red, 0, 0));
    pixels.setPixelColor(23, pixels.Color(red, 0, 0));
    pixels.setPixelColor(24, pixels.Color(red, 0, 0));


    pixels.setPixelColor(5, pixels.Color(red, 0, 0));
    pixels.setPixelColor(14, pixels.Color(red, 0, 0));
    pixels.setPixelColor(15, pixels.Color(red, 0, 0));
    /*  // заполнение нуля
             leds[6] = CHSV(red, 255, brightness1);
             leds[7] = CHSV(red, 255, brightness1);
             leds[8] = CHSV(red, 255, brightness1);

             leds[11] = CHSV(red, 255, brightness1);
             leds[12] = CHSV(red, 255, brightness1);
             leds[13] = CHSV(red, 255, brightness1);

             leds[16] = CHSV(red, 255, brightness1);
             leds[17] = CHSV(red, 255, brightness1);
             leds[18] = CHSV(red, 255, brightness1);
       //для мигания нутри нуля

            if (brightness_off1 == 0) {
               brightness1 = brightness1 + 5;  //плавное мигание
               if (brightness1 >= 250) brightness_off1 = 1;
             }
             else {
               brightness1 = brightness1 - 2;
               if (brightness1 <= 5)brightness_off1 = 0;
             }*/

    //для мигания
    if (brightness_off == 0) {
      red = red + 5;  //плавное мигание
      if (red >= 250) brightness_off = 1;
    }
    else {
      red = red - 2;
      if (red <= 6)brightness_off = 0; //5
    }

    delay(16);//влияет только на красны обод
  }
  //if (ploskii == 4 and babochka == 5 and zadvijka == 2 )
  if ( magnit == 1) //дверь распахнута//(ploskii == 4  or zadvijka == 2) and (ploskii != 1 and ploskii != 2 and ploskii != 3) and
    //  if (ploskii != 3 and babochka  !=  4 and zadvijka  !=  2 and  ///этот большучий if на время тестирования
    //     ploskii != 2 and babochka  !=  3 and zadvijka  !=  1 and
    //    ploskii != 1 and babochka  !=  2 and babochka != 1   )
  {
    pixels.setBrightness(255);
    for (int  i = 0; i < 25; i++) {

      pixels.setPixelColor(i, pixels.Color(80, 80, 80));
    }

    if (ploskii == 4)     pixels.setPixelColor(0, pixels.Color(90, 0, 0));

    if (babochka == 5)      pixels.setPixelColor(1, pixels.Color(90, 0, 0));

    if (zadvijka == 2)      pixels.setPixelColor(2, pixels.Color(90, 0, 0));
  }


  if (ploskii == 3 and babochka == 4 and magnit == 0) //если плоский и бабочка полностью закрыто, то значит никого нет дома, выкл подсветку, мигаем диодом для
  {

    for (int  i = 0; i < 25; i++) {

      pixels.setPixelColor(i, pixels.Color(0, 0, 0));

    }
    //FastLED.setBrightness(50);
    pixels.setBrightness(50);

    if (millis() - currentTime3 > 3000 ) {

      // pixels.setPixelColor(20, pixels.Color(50, 50, 50)); правый верхний угол
      pixels.setPixelColor(0, pixels.Color(50, 50, 50));// правый нижний угол
      currentTime3 = millis();
    }
    //leds[19] = CHSV(red, 255, brightness);
    /// leds[20] = CHSV(100, 255, brightness);
    //leds[4] = CHSV(100, 255, brightness);
    ///leds[24] = CHSV(100, 255, brightness);


  }
  /* if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
     leds[0] =  CRGB::Blue;
     wifi();
     // digitalWrite(wifi_led, LOW); digitalWrite(wifi_led, HIGH);

    }*/

  //terminal.println(rgb);
  //terminal.println(saturation);

  pixels.show();
  //delay(8);
  //counter = counter + 0.1; //0.5 //1 HUE_AQUA //
  //counter = 45.00;//96
  //saturation = 180.00;

  /* if (brightness_off1 == 0) {
     counter = counter + 0.5;  //плавное мигание
     if (counter >= 180) brightness_off1 = 1;
    }
    else {
     counter = counter -0.5;
     if (counter <= 150)brightness_off1 = 0;
    }*/
  /*
    Red (0..) "HUE_RED"
    Orange (32..) "HUE_ORANGE"
    Yellow (64..) "HUE_YELLOW"
    Green (96..) "HUE_GREEN"
    Aqua (128..) "HUE_AQUA"
    Blue (160..) "HUE_BLUE"
    Purple (192..) "HUE_PURPLE"
    Pink(224..) «HUE_PINK»
  */
  if (r_led == 1) {
    pixels.setPin(-1); //delay(100);
    pixels.setPin(PIN);
    //  pixels.begin();
    //pixels.setBrightness(255);
    //blynk_println("setledPin");
    r_led = 0;
  }

}
