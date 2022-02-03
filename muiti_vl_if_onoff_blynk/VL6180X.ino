void italon( int num_italon_ploskii, int num_italon_babochka, int num_italon_zadvijka) { // middleArifm(среднее арифм) /массив италонных зн ригеля/длина этого массива
  // if (massiv_middleArifm[0] < 100) digitalWrite(13, HIGH); else digitalWrite(13, LOW);

  //terminal.println(massiv_middleArifm[0]);
  int abs_var0[num_italon_ploskii];
  int abs_var1[num_italon_babochka];
  int abs_var2[num_italon_zadvijka];
  //terminal.println("Отклонения ригеля от эталонных значений: ");
  for (int i = 0; i < num_italon_ploskii; ++i) {
    abs_var0[i] = abs(massiv_middleArifm[0] - italon_ploskii[i]);
    //terminal.print(i);
    //terminal.print(abs_var0[i]); terminal.print(" ");
  }


  for (int i = 0; i < num_italon_babochka; ++i) {
    abs_var1[i] = abs(massiv_middleArifm[1] - italon_babochka[i]);
    //terminal.print(abs_var1[i]); terminal.print(" ");  terminal.println(i);
  }


  for (int i = 0; i < num_italon_zadvijka; ++i) {
    abs_var2[i] = abs(massiv_middleArifm[2] - italon_zadvijka[i]);

    //terminal.print(abs_var2[i]); terminal.print(" ");  terminal.println(i);
  }
  /// terminal.println();



  int min_var0;
  int min_var1;
  int min_var2;

  int min0 = 0;
  int min1 = 0;
  int min2 = 0;

  for (int i = 0 ; i < num_italon_ploskii; ++i) {
    if (abs_var0[min0] > abs_var0[i])min0 = i;
    //terminal.print(i);

    // terminal.print(abs_var0[min0]);  terminal.print("_");    terminal.println(abs_var0[i]);

  }


  for (int i = 0; i < num_italon_babochka; ++i) {
    if (abs_var1[min1] > abs_var1[i])min1 = i;// terminal.print(i);


  }


  for (int i = 0; i < num_italon_zadvijka; ++i) {
    if (abs_var2[min2] > abs_var2[i])min2 = i;
    //terminal.print(i);
    //  terminal.print(abs_var2[min2]);  terminal.print("_");
    //terminal.println(abs_var2[i]);
    // terminal.print(min2);
  }
/*
  //для предотвращения писка при изменении ригеля с 1 на 0 или с 2 на 3 изза клюка и сразу же обратно
  //if(delay_ploskii-millis()>5000)
  if (min0 == 0 and ploskii == 1) {
    // terminal.println("ploskii start");
    delay_ploskii = millis();
  }


  if (min0 == 1 and delay_ploskii - millis() < 10000) { //тк ноль то условие выше не сработает
    // terminal.println("ploskii reset");
    delay_ploskii = 0;
  }*/


  if (min0 == 1 and abs(massiv_middleArifm[0] - italon_ploskii[1]) >= 2 ) { //увеличение границы мертвой зоны(ignor_max)
    //terminal.println("min0 and abs");
    if (ploskii_neitalon >= 2) {
      float otklonenie = massiv_middleArifm[0] - italon_ploskii[1];
      //terminal.println(otklonenie);
      otklonenie = 0.7 * otklonenie;

      // terminal.println(otklonenie);

      //if (otklonenie <= 3)
      {
        ignor_max = 51.00 + otklonenie;
        //terminal.println("if");
      }
      ploskii_neitalon = 0;
    }
  }

  blynk_print((String)ignor_max);
  //terminal.println(ignor_max);
  //////if (min0>=0  and massiv_middleArifm[2]<=55 and massiv_middleArifm[1]<=61)    //if (massiv_middleArifm[1]<=italon_babochka[0] and massiv_middleArifm[1]<=italon_babochka[0] and massiv_middleArifm[2]<=italon_zadvijka[0] )
  {
    ploskii =  min0;//min0;
    zadvijka = min2;// 0; /////
    babochka = min1;
  }
  //////else terminal.println("troinoeIF");


  // else{propysk_oprosa_posle_zaxlopivania_dveri++;}
  //terminal.print("Совершено оборотов ригеля плоского : ");
#ifdef MY__DEBUG
  blynk_print((String)ploskii);
  blynk_print("  ");
  // terminal.print("Совершено оборотов ригеля бабочки  : ");
  blynk_print((String)zadvijka);
  blynk_print("  ");
  // terminal.print("Совершено оборотов ригеля задвижка : ");
  blynk_print("  ");
  blynk_print((String)babochka);
  blynk_print("  ");
  blynk_println((String)magnit);
#endif


}








void bez_middleArifm() { //(int sensor, int num_aver)

  massiv_middleArifm[0] = sensor0.readRangeContinuousMillimeters(); //***// if (sensor0.timeoutOccurred())  blynk_print(" TIMEOUT");


  massiv_middleArifm[1] = sensor1.readRangeContinuousMillimeters();  //***//if (sensor1.timeoutOccurred())  blynk_print(" TIMEOUT");


  massiv_middleArifm[2] = sensor2.readRangeContinuousMillimeters();  //***//if (sensor2.timeoutOccurred())  blynk_print(" TIMEOUT");
}











bool middleArifm(int num_aver) { //(int sensor, int num_aver)
  int var[] = {0, 0, 0};
  int sred_aref[] = {0, 0, 0};
  bool first = 0;
  ///int x0 = sensor0.readRangeContinuousMillimeters();
  //int x1 = sensor0.readRangeContinuousMillimeters();
  int r = 0;
  for (int i = 0; i < num_aver; ++i) {
    {
      //if (first == 0)
      {
        massiv_middleArifm[0] = sensor0.readRangeContinuousMillimeters();
        massiv_middleArifm[1] = sensor1.readRangeContinuousMillimeters();
        massiv_middleArifm[2] = sensor2.readRangeContinuousMillimeters();
      }
      ///
      /*   if ( x0 == massiv_middleArifm[0]) {
          r++;
          if (r == 2) {
            blynk_println("r=");
             return 0;
            }
        }
        if ((abs(massiv_middleArifm[0] - x0) < 3)) //or (abs(massiv_middleArifm[1] - x1) < 3))
        {
          massiv_middleArifm[0] = x1;
        }
         else return 0;*/
      ///


      //massiv_middleArifm[0] = sensor0.readRangeContinuousMillimeters();
    }
    //if (sensor1.timeoutOccurred())     terminal.print(" TIMEOUT");






    sred_aref[0] =  sred_aref[0] + massiv_middleArifm[0];
    sred_aref[1] =  sred_aref[1] + massiv_middleArifm[1];
    sred_aref[2] =  sred_aref[2] + massiv_middleArifm[2];
    //Проверка если показания с датчиков расходятся больше чем на 4 пункта, то начиется выполнение функциии сначала сразу или через delay()
    //так по идее можно добиться считывания реальных(а точнее игнорирования сильно расходящихся) показаний только когда дверь закрыта и датчики не ненесут пургу от открывания двери или прикрытой двери
    // terminal.println(abs((sred_aref[0] / (i + 1)) - massiv_middleArifm[0]));
    if ( abs((sred_aref[0] / (i + 1)) - massiv_middleArifm[0]) >= 4 )
    {

      blynk_println((String)"111");
      return 0;
    }
    if ( abs((sred_aref[1] / (i + 1)) - massiv_middleArifm[1]) >= 4 )
    {
      blynk_println((String)"222");
      return 0;
    }
    if ( abs((sred_aref[2] / (i + 1)) - massiv_middleArifm[2]) >= 4 )
    {
      blynk_println((String)"333");
      return 0;
    }

    //terminal.print(var);
    //terminal.println(sred_aref[, 200]);
  }


  if ((massiv_middleArifm[0] - italon_ploskii[1]) >= 2 and ploskii == 1) //если показания отличаются от италона 1 регеля плоского замка больше 2 раз, то граница мертвой зоны между 0 и 1 регилем(ignor_max) будет увеличиваться
  {
    // terminal.println("++");
    ploskii_neitalon++;
  }
  // else ploskii_neitalon = 0;
  float sec_ploslii = sred_aref[0] / num_aver;
  blynk_println((String)ignor_max);
  if (48 <= sec_ploslii  and sec_ploslii <= ignor_max) { //переход между 1 и 0 ригелем чтобы не пищало, ignor_max постоянно меняеся через if выше
    //  terminal.println("ploskii");
    blynk_println((String)"AAA");
    return 0;
  }
  if (25 <= sec_ploslii  and sec_ploslii <= 29) { //переход между 3 и 2 ригелем чтобы не пищало
    //   terminal.println("ploskii");
    blynk_println((String)"BBB");
    return 0;
  }

  massiv_middleArifm[0] = sec_ploslii;
  massiv_middleArifm[1] = sred_aref[1] / num_aver;
  massiv_middleArifm[2] = sred_aref[2] / num_aver;


  //massiv_middleArifm[2] = massiv_middleArifm[1]; // для теста
  //terminal.println("Среднее арифметическое значение с датчика: ");
  //terminal.println(massiv_middleArifm[0]); terminal.println(massiv_middleArifm[1]); terminal.println(massiv_middleArifm[2]);
  //return *sred_aref;
  return 1;
}
