#define MY__DEBUG 1 //есть закоменчино, то строки после #ifdef  не будут работать

#include <rom/rtc.h>
#include <Wire.h>
#include <VL6180X.h>

#include <Tone32.h>

#include <WiFi.h> //для прошивки по wiffi
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//#include "OneButton.h"
#include <WiFiClient.h>

#ifdef MY__DEBUG
#include <BlynkSimpleEsp32.h>
#endif

#include <Adafruit_NeoPixel.h>
#define PIN 4
#define NUMPIXELS 25
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



//OneButton button1(0, true); //gpio0 кн flash на плате
//int wifi_led = 2; //gpio2 он на плате паспаян
//int button_sec = 0;
const char* ssid  = ""; //Asus//ASUS //Enter SSID// ASUS ПЛОХО РАБОТАЕТ С esp32// Asus(xiaomi) РАБОТАЕТ ОТЛИЧНО
const char* password  = ""; //Enter Password
char auth[] = "";

#ifdef MY__DEBUG
WidgetTerminal terminal(V1);
#endif

#define long_buzer_pin 15
#define LONG_BUZZER_PIN 15
#define buzer_pin 17
#define BUZZER_PIN 17
#define BUZZER_CHANNEL 0


#define hallPin  16 // назначение пина датчика холла
int magnit; // переменная для хранения значения с датчика холла  ///0- ПРИЛОЖЕН МАГНИТ  // 1- НЕТ МАГНИТА

#define fakepin  23 // назначение fakepin

TaskHandle_t Task1;
TaskHandle_t Task2;

// Matrix size
#define NUM_ROWS 5
#define NUM_COLS 5


/////////

#define RANGE 1

/* List of adresses for each sensor - after reset the address can be configured */
#define address0 0x22//24 //29
#define address1 0x34 //29
#define address2 0x32 //32


unsigned long currentTime;   // Переменная времени для пищалки
unsigned long currentTime2;   // Переменная времени для пищалки
unsigned long currentTime3;   // Переменная времени для мигания диодом
unsigned long delay_pisk=millis();   // 
unsigned long delay_ploskii;   // 
unsigned long delay_zadvijka;   // 
unsigned long delay_babochka;   // 
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

/* These Arduino pins must be wired to the IO0 pin of VL6180x */
int enablePin0 = 19; //gpio12//io12  //12//14//35
int enablePin1 = 5; //gpio14//io14
int enablePin2 = 18; // 27проверить, тк gpio34 и gpio35 неработают


/* Create a new instance for each sensor */
VL6180X sensor0;
VL6180X sensor1;
VL6180X sensor2;
VL6180X sensor3;

bool blynk_off_on = 0;
bool blynk_or_serial = 0;
bool reboot = 0;
bool r_led = 0;

#ifdef MY__DEBUG
BLYNK_WRITE(V1)
{
  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("1") == param.asStr()) {
    blynk_off_on = 1;
    blynk_println("blynk_off_on=1") ;
  }
  if (String("0") == param.asStr()) {
    blynk_println("blynk_off_on=0") ;
    blynk_off_on = 0;
  }
  if (String("r") == param.asStr()) {
    reboot = 1;
  }
  if (String("rl") == param.asStr()) {
    r_led = !r_led;
    //blynk_println((String)(bool)r_led) ;
    terminal.println((String)r_led) ;

  }
  // Ensure everything is sent
  terminal.flush();
}
void blynk_println(String text) {
  if (blynk_off_on == 1) {
    terminal.println(text) ;
  }
  else { //serial для задержки, если пины не попадают на использкемые пины, сериал вообще работает
    //////// Serial.println(text);//опасно тк можно уйти в цил ребутесли чтото не то попадёт в  Serial.println(text); и  a не сможет это вывести и перезагрузит esp
  }
}

void blynk_print(String text) {
  if (blynk_off_on == 1) {
    terminal.print(text) ;
  }
  else { //serial для задержки, если пины не попадают на использкемые пины, сериал вообще работает
    //////// Serial.print(text);//опасно тк можно уйти в цил ребутесли чтото не то попадёт в  Serial.println(text); и  a не сможет это вывести и перезагрузит esp
  }
}
#endif
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {

}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info) {
 //Blynk.begin(auth, ssid, password);
// Blynk.run();
 /*  if (!Blynk.connected())
  {
    if (Blynk.connect())
    {               
      Serial.printf("[%8lu] ReconnectBlynk: Blynk reconnected\r\n", millis());
    }
    else
    {
      Serial.printf("[%8lu] ReconnectBlynk: Blynk not reconnected\r\n", millis());
    }
  }
  else
  {
    Serial.printf("[%8lu] ReconnectBlynk: Blynk connected\r\n", millis());
  }*/
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  WiFi.begin(ssid, password);
}
void setup()
{

  //Serial.begin(115200);


#ifdef MY__DEBUG
  WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, SYSTEM_EVENT_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
#endif

  wifi();
#ifdef MY__DEBUG
  Blynk.begin(auth, ssid, password);
#endif
  ota();
  pinMode (hallPin, INPUT);

  pinMode(buzer_pin, OUTPUT);

  pixels.begin();
  pixels.setBrightness(255);

  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    20000,       /* Stack size of task */ ///10000
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    1);


  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    20000,       /* Stack size of task *////10000
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */


  //Wire.begin();
  Wire.begin(21, 22, 100000); //16, 17, 100000

  //I2Cone.begin(21,22,100000); // SDA pin 21, SCL pin 22, 100kHz frequency
  //I2Ctwo.begin(16,17,400000); // SDA pin 16, SCL pin 17, 400kHz frequency
  // Reset all connected sensors
  pinMode(enablePin0, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);


  digitalWrite(enablePin0, LOW);
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);


  delay(100);//1000

  // Sensor0
  //***// terminal.println("Start Sensor 0");
  digitalWrite(enablePin0, HIGH);
  delay(50);
  sensor0.init();
  sensor0.configureDefault();
  sensor0.setAddress(address0);
  //***// terminal.println(sensor0.readReg(0x212), HEX); // read I2C address
  sensor0.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor0.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 10);///10

  sensor0.setTimeout(100);
  sensor0.stopContinuous();
  sensor0.setScaling(RANGE); // configure range or precision 1, 2 oder 3 mm
  delay(300);
  sensor0.startInterleavedContinuous(100);
  delay(100);

  // Sensor1
  //***//  terminal.println("Start Sensor 1");
  digitalWrite(enablePin1, HIGH);
  delay(50);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setAddress(address1);
  //***// terminal.println(sensor1.readReg(0x212), HEX);
  sensor1.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor1.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 10);// 10
  sensor1.setTimeout(100);
  sensor1.stopContinuous();
  sensor1.setScaling(RANGE);
  delay(300);
  sensor1.startInterleavedContinuous(100);
  delay(100);

  // Sensor2
  //***//  terminal.println("Start Sensor 2");
  digitalWrite(enablePin2, HIGH);
  delay(50);
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setAddress(address2);
  //***//  terminal.println(sensor2.readReg(0x212), HEX);
  sensor2.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor2.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 10);
  sensor2.setTimeout(100);
  sensor2.stopContinuous();
  sensor2.setScaling(RANGE);
  delay(300);
  sensor2.startInterleavedContinuous(100);

#ifdef MY__DEBUG
  terminal.print("Введите в терминал 1, чтобы видеть показания с датчиков!");
  terminal.flush();
#endif





 // delay(1000);//сколько было поумолчанию в том скрипте?
 /// delay(3000);
#ifdef MY__DEBUG
  Blynk.run();
#endif
}
//


//последние италонные зн ригелей(4ригель и 3 регель) выставляются самое высокое зн, те сживое средние
////когла датчик переклинивает и он выдаёт 10-20 одинаковых значений
//предпоследние италонные зн ригелей(3 и 2 ринель) выставляется тупо среднее по блинку, те на глаз по лайв данным

int massiv_middleArifm[] = {0, 0, 0};
//int italon_ploskii[] = { 55, 50, 34, 26, 80}; //


int italon_ploskii[] = { 53, 43, 34, 26, 1000}; //
//int italon_ploskii[] = { 58, 47, 34, 26, 80}; //
//int italon_ploskii[] = { 55, 47, 34, 26, 80}; //
//int italon_ploskii[] = { 53, 47, 34, 26, 1000}; //
//int italon_ploskii[] = { 58, 48, 37, 26, 1000}; //
//int italon_ploskii[] = { 58, 48, 34, 26, 1000}; //

//int italon_babochka[] = {64, 54, 45, 38, 28, 1000}; //63
int italon_babochka[] = {64, 54, 45, 38, 32, 80}; //63
//38 33-31

int italon_zadvijka[] = { 44, 26, 80}; //                          48
//0 - самое низкое значение даже если калибается между 68 и 63

//значения до запыления
//int italon_ploskii[] = { 49, 38, 27, 16, 54}; //51,,,, { 42, 27, 16, 10, 50}   50, 41, 32, 17, 80
//int italon_babochka[] = {61, 43, 37, 30, 21, 80}; //60   {52, 42, 34, 30, 21, 80}
//int italon_zadvijka[] = { 46, 16, 51 }; //49    20,10, //30  { 30, 20, 0, 80 };
int brightness = 0;
int brightness_off = 0;
int brightness1 = 250 ;
int brightness_off1 = 0;
int ploskii = 0;
int babochka = 0;
int zadvijka = 0;
int old_ploskii = 0;
int old_babochka = 0;
int old_zadvijka = 0;
int r = 25;
int g = 17;
int b = 6;
//double rgb = 80;
double counter = 63.00;
double saturation = 149;
int R = 0;
int G = 0;

int B = 0;
int red = 0;
int propysk_oprosa_posle_zaxlopivania_dveri = 0;
int ploskii_neitalon=0;
float ignor_max=52.00;

void loop()
{
  ArduinoOTA.handle();
  if ( reboot == 1) {
    blynk_off_on = 0;
    delay(1000);
    ESP.restart();
  }
  Serial.println ("L");
  //Blynk.run();
  // button1.tick();
#ifndef MY__DEBUG
  wifi_off();
#endif
#ifdef MY__DEBUG
  Blynk.run();
 // wifi_reconnect();
  blynk_println("ЗАМОК");
#endif



  //magnit = digitalRead (hallPin); // чтение значения с датчика
  if (digitalRead (hallPin) == 1) {
    delay(100);
    pinMode (hallPin, INPUT);
    magnit = digitalRead (hallPin);
  }


  /*
     //terminal.print("\tDistance0: ");
     terminal.print(sensor0.readRangeContinuousMillimeters());
    terminal.print(" ");
    //  terminal.print("\tDistance1: ");
     terminal.print(sensor1.readRangeContinuousMillimeters());
    // terminal.println();
    terminal.print(" ");
    //  terminal.print("\tDistance2: ");
     terminal.print(sensor2.readRangeContinuousMillimeters());
     terminal.println();

  */





  if (magnit == 0 ) {
    if (propysk_oprosa_posle_zaxlopivania_dveri >= 1) {

      if (middleArifm(5) == 1) { //3//5
        italon(NUMITEMS(italon_ploskii), NUMITEMS(italon_babochka), NUMITEMS(italon_zadvijka)); //3норм
      }
      else {
       /// delay(100);
       //  
      }
#ifdef MY__DEBUG
     //blynk_println((String)old_babochka);
     blynk_print((String)massiv_middleArifm[0]);
      blynk_print(" ");
      blynk_print((String)massiv_middleArifm[2]);
      blynk_print(" ");
      blynk_println((String)massiv_middleArifm[1]);
#endif
      // bez_middleArifm();
      // terminal.println("ПОДСЧЁТ");


    } else {
      //Serial.println("DELAY");
      delay(200);//400//500 БЫЛО ДО ФИКСА МАГИЧЕСКОГО СРАБАТЫВАНИЯ
      propysk_oprosa_posle_zaxlopivania_dveri++;
      //Serial.println("OFF");
    }
  }
  else {
    //if(ploskii>=1)
    { // or zadvijka==1
      propysk_oprosa_posle_zaxlopivania_dveri = 0;
      //присваиваем зн ригелей без опроси датчиков
      ploskii = 0;
      babochka = 0;
      zadvijka = 0;
/*#ifdef MY__DEBUG
      blynk_print((String)ploskii);
      blynk_print("  ");
      blynk_print((String)zadvijka);
      blynk_print("  ");
      blynk_print((String)babochka);
      blynk_print("  ");
      blynk_println((String)magnit);
#endif*/
    }
  }


}
