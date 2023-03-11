
char state[10];
int16_t ax, ay, az,fb,lr;


#include "I2Cdev.h"
#include "MPU6050.h"
#define OUTPUT_READABLE_ACCELGYRO
#define DUMP_REGS

#include <Wire.h>


#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro(0x68);


// Global Variables
//APDS9930 apds = APDS9930();
//uint16_t proximity_data = 0;

void setup() {
   #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

Serial.begin(38400);
pinMode(7,OUTPUT);

 accelgyro.initialize();

 Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
   
}

void loop() {
  accelgyro.getAcceleration(&ax, &ay, &az);


    lr=map(ax,-17000,18000,950,3000);
    fb=map(ay,-17000,17000,3000,950);

     //sprintf_P(state, (PGM_P)F("%03d%03d"), forearm,wrist);
     if((lr>=950 && lr<=3000) && (fb>=950 && fb<=3000))
     sprintf_P(state, (PGM_P)F("%04d%04d"), lr,fb);
      
  Serial.println(state);
delay(5);



}
