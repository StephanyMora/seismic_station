#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

MPU6050 accelerometer;

int rawAx, rawAy, rawAz;

void setup() {
  Serial.begin(9600);//serial communication
  Wire.begin();//I2C
  accelerometer.initialize();//you know what this do
  if(accelerometer.testConnection()) Serial.println("Conexion establecida");
  else Serial.println("¡Error de conexion!");
}

void loop() {
  accelerometer.getAcceleration(&rawAx, &rawAy, &rawAz);//take raw values from mpu
  float Ax = rawAx * (9.81/16384.0);//convertion for acceleration on m/s2
  float Ay = rawAy * (9.81/16384.0);
  float Az = rawAz * (9.81/16384.0);
  Serial.print("Aceleracion en [x,y,z]: m/s2\t");//print and space
  Serial.print(Ax); Serial.print("\t");
  Serial.print(Ay); Serial.print("\t");
  Serial.println(Az); 
  delay(3000);//wait 3 sec
}
