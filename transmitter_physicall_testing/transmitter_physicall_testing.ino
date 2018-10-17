#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <SPI.h> // Not actually used but needed to compile
#include <DHT.h>
#include <RH_ASK.h>

#define DHTPIN 13    
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

MPU6050 accelerometer;

RH_ASK rf_driver;

int humidity, temperature;
int rawAx, rawAy, rawAz;
String strHumidity;
String strTemperature;
String strAx;
String strAy;
String strAz;
String strOut;
float Ax, Ay, Az;

void setup() {
  Serial.begin(9600);//serial communication
  Wire.begin();//I2C
  dht.begin();
  rf_driver.init();
  accelerometer.initialize();//you know what this do
  if(accelerometer.testConnection()) Serial.println("Conexion establecida");
  else Serial.println("¡Error de conexion!");
}

void readDHT(){
  delay(2000);
  //leo temperatura y humedad
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Humedad(%) - Temperatura(*C): ");
  Serial.print(humidity); Serial.print("\t");
  Serial.println(temperature); Serial.print("\t");
}

void readAccelerometer(){
  accelerometer.getAcceleration(&rawAx, &rawAy, &rawAz);//take raw values from mpu
  Ax = rawAx * (9.81/16384.0);//convertion for acceleration on m/s2
  Ay = rawAy * (9.81/16384.0);
  Az = rawAz * (9.81/16384.0);
  Serial.print("Aceleracion en [x,y,z]: m/s2\t");//print and space
  Serial.print(Ax); Serial.print("\t");
  Serial.print(Ay); Serial.print("\t");
  Serial.println(Az); 
}

void sendData(int humidity, int temperature, int rawAx, int rawAy, int rawAz){
  strHumidity = String(humidity);
  strTemperature = String(temperature);
  strAx = String(Ax);
  strAy = String(Ay);
  strAz = String(Az);
  //construyo el string a enviar, separo datos con ,
  strOut = strHumidity + ',' + strTemperature + ',' + strAx + ',' + strAy + ',' + strAz;
  static char *msg = strOut.c_str();
  rf_driver.send((uint8_t*)msg, strlen(msg));
  rf_driver.waitPacketSent();
}

void loop() {
  readDHT();
  readAccelerometer();
  sendData(humidity, temperature, rawAx, rawAy, rawAz);
  delay(3000);//wait 3 sec
 
}
