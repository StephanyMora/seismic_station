#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <DHT.h>

#define DHTPIN 13    
#define DHTTYPE DHT11  

float humidity;
float temperature;
long rawAx;
int rawAy;
int rawAz;
String strHumidity;
String strTemperature;
String strAx;
String strAy;
String strAz;
String strOut;

RH_ASK rf_driver;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  rf_driver.init();
  dht.begin();
}

void sendData(){
  delay(2000);
  //leo temperatura y humedad
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  //convierto los datos a str
  strHumidity = String(humidity);
  strTemperature = String(temperature);
  rawAx = random(-100,100);
  rawAy = random(-100,100);
  rawAz = random(-100,100);
  strAx = String(rawAx);
  strAy = String(rawAy);
  strAz = String(rawAz);
  //construyo el string a enviar, separo datos con ,
  strOut = strHumidity + ',' + strTemperature + ',' + strAx + ',' + strAy + ',' + strAz;
  static char *msg = strOut.c_str();
  rf_driver.send((uint8_t*)msg, strlen(msg));
  rf_driver.waitPacketSent();
}

void loop()
{
  sendData();
}
