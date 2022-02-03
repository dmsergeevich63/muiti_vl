void Task2code( void * pvParameters ) {
  //***// terminal.print("Task2 running on core ");
  //***//  terminal.println(xPortGetCoreID());

  for (;;) {
    // alarm();//напоминалка о закрытии дверидлинные писки при открытой или распахнутой двери//отключается кн на 10мин
    Serial.println ("B");
    alarm_dver_raspahnuta();
    alarm_dver_otkryta();
    pisk();//короткий писк при повороте1
  }
}

int dver_raspahnuta() {//ф для напоминалки
  int i = 0;
  if (magnit == 1)
    // if (ploskii == 4   or babochka == 5  or zadvijka == 2)
  {
    i = 1;//да
  }
  else i = 0;//нет
  return i;
}
int dver_otkryta() { //ф для напоминалки
  int i = 0;

  if ((ploskii == 0   and babochka == 0  and zadvijka == 0) and magnit == 0) {
    i = 1; //да
  }
  else i = 0;//нет
  //terminal.println(i);
  return i;
}
int zaderzhka_dver_raspahnuta = 300000; //15сек //60сек-60000 //120сек-120000 //300000-5MIN //
int zaderzhka_dver_otkryta = 600000; //15сек //60сек-60000 //120сек-120000 //600000-10MIN
void alarm_dver_raspahnuta() { //напоминалка если открыта дверь
  //if (1<=ploskii<= 3 or 1 <= babochka <= 4 or 1 <= zadvijka <= 2)
  //  terminal.println(babochka);
  if (dver_raspahnuta() == 1)
  {
    // terminal.println("raspahnuta1");

    if (millis() - currentTime > zaderzhka_dver_raspahnuta)   // сюда вроде можно кн впихнуть но хз
    {



      //двойной писк
      dual_pisk();
#ifdef MY__DEBUG
      blynk_println("ПИК dver_raspahnuta");
#endif

      zaderzhka_dver_raspahnuta = 60000;
      currentTime = millis();
    }
    //else terminal.println("пищалка скоро запищит");




  }
  else {
    //terminal.println("+++++++++++++++++++++");
    //          digitalWrite(buzer_pin, LOW);///возможно это тут понадовится
    zaderzhka_dver_raspahnuta = 300000;
    currentTime = millis();
  }


}
void alarm_dver_otkryta() { //напоминалка если не закрыты ригели


  if (dver_otkryta() == 1)
  {
    ///  terminal.println("otkryta");

    if (millis() - currentTime2 > zaderzhka_dver_otkryta )   //
    {



      //двойной писк
      dual_pisk();
#ifdef MY__DEBUG
      blynk_println("ПИК dver_otkryta");
#endif

      zaderzhka_dver_otkryta = 600000;
      currentTime2 = millis();
    }
    //else terminal.println("пищалка скоро запищит");




  }
  else {
    //terminal.println("+++++++++++++++++++++");
    //          digitalWrite(buzer_pin, LOW);///возможно это тут понадовится
    zaderzhka_dver_otkryta  = 600000;
    currentTime2 = millis();
  }


}


void pisk() {

  if ( ploskii == 3 and babochka == 2 and magnit == 0 )  //>if ( ploskii == 3 and babochka == 4 and magnit == 0 )
  {
    if (old_ploskii != 3 or old_babochka != 2) { // if (old_ploskii != 3 or old_babochka != 4)

      // if ( ploskii != old_ploskii or babochka != old_babochka)  // тут должен быть and
      {
#ifdef MY__DEBUG
        blynk_println("LONG ПИК");
#endif
        long_dual_pisk();



        old_ploskii = ploskii;
        old_babochka = babochka;
      }

    }

  }
  else {
    if (ploskii == 3 and magnit == 0)
    {
      if ( ploskii != old_ploskii)  // тут должен быть and
      {
#ifdef MY__DEBUG
        blynk_println("ПИК ploskii");
#endif
        dual_pisk();

      }
    }

    if ( babochka == 2 and magnit == 0 )// if ( babochka == 4 and magnit == 0 )
    {
      if (babochka != old_babochka)
      {
#ifdef MY__DEBUG
        blynk_println("ПИК babochka");
#endif
        dual_pisk();

      }

    }
  }


  //
  if (ploskii == 0 and babochka == 0 and magnit == 0) //
  {

    if (old_ploskii != 4 and old_babochka != 5) { // /

      if ( ploskii != old_ploskii or babochka != old_babochka)  // тут должен быть and
      {
#ifdef MY__DEBUG
        blynk_println("ПИК");
#endif
        // if (delay_ploskii - millis() > 10000)
        {
          dual_pisk();
        }




        old_ploskii = ploskii;
        old_babochka = babochka;
      }

    }
  }
  else
  {
    old_ploskii = ploskii;
    old_babochka = babochka;
  }


}

void dual_pisk() {
  // put your main code here, to run repeatedly:
  //int xx = millis() - delay_pisk;
  //terminal.println(xx);
  if ((millis() - delay_pisk) > 2000)
  {
    tone(BUZZER_PIN, 4000, 250, BUZZER_CHANNEL);
    tone(LONG_BUZZER_PIN, 4000, 250, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    noTone(LONG_BUZZER_PIN, BUZZER_CHANNEL);
    delay(100);
    tone(BUZZER_PIN, 4000, 250, BUZZER_CHANNEL);
    tone(LONG_BUZZER_PIN, 4000, 250, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    noTone(LONG_BUZZER_PIN, BUZZER_CHANNEL);
    delay_pisk = millis();
  }

}
void long_dual_pisk() {
  // put your main code here, to run repeatedly:
  tone(BUZZER_PIN, 4000, 500, BUZZER_CHANNEL);
  tone(LONG_BUZZER_PIN, 4000, 500, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  noTone(LONG_BUZZER_PIN, BUZZER_CHANNEL);


}
