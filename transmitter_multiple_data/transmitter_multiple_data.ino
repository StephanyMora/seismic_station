#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <DHT.h>

#define DHTPIN 13    
#define DHTTYPE DHT11  

float humedad;
float temperatura;
String strHumedad;
String strTemperatura;
String strHello = "Hello";
String strPrincess = "princess";
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
  humedad = dht.readHumidity();
  temperatura = dht.readTemperature();
  //convierto los datos a str
  strHumedad = String(humedad);
  strTemperatura = String(temperatura);
  //construyo el string a enviar, separo datos con ,
  strOut = strHumedad + "," + strTemperatura + "," + strHello + "," + strPrincess;
  static char *msg = strOut.c_str();
  delay(2000);
  rf_driver.send((uint8_t*)msg, strlen(msg));
  rf_driver.waitPacketSent();
}

void loop()
{
  sendData();
  
}
