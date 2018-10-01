#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <DHT.h>

#define DHTPIN 13    
#define DHTTYPE DHT11  

float hum;
float temp;
String str_hum;
String str_temp;
String str_out;

RH_ASK rf_driver;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  rf_driver.init();
  dht.begin();
}

void loop()
{
  //espero a que el sensor establezca conexión
  delay(2000);
  //leo temperatura y humedad
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //convierto los datos a str
  str_hum = String(hum);
  str_temp = String(temp);
  //construyo el string a enviar, separo datos con ,
  str_out = str_hum + "," + str_temp;
  
  static char *msg = str_out.c_str();
  rf_driver.send((uint8_t*)msg, strlen(msg));
  rf_driver.waitPacketSent();
}
