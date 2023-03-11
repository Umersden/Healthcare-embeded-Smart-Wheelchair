
char state[10];
int16_t ax, ay, az,fb,lr;
#include "Filter.h"
// Create a new exponential filter with a weight of 5 and an initial value of 0. 
ExponentialFilter<long> ADCFilter(5, 0);
ExponentialFilter<long> ADCFilter2(5, 0);

#include "I2Cdev.h"
#include "MPU6050.h"
#define OUTPUT_READABLE_ACCELGYRO
#define DUMP_REGS

#include <Wire.h>
#include <APDS9930.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro(0x68);


// Global Variables
APDS9930 apds = APDS9930();
uint16_t proximity_data = 0;

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
   
    


if ( apds.init() ) {
    Serial.println(F("APDS-9930 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9930 init!"));
  }

   if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }

#ifdef DUMP_REGS
  /* Register dump */
  uint8_t reg;
  uint8_t val;

  for(reg = 0x00; reg <= 0x19; reg++) {
    if( (reg != 0x10) && \
        (reg != 0x11) )
    {
      apds.wireReadDataByte(reg, val);
      Serial.print(reg, HEX);
      Serial.print(": 0x");
      Serial.println(val, HEX);
    }
  }
  apds.wireReadDataByte(0x1E, val);
  Serial.print(0x1E, HEX);
  Serial.print(": 0x");
  Serial.println(val, HEX);
#endif

}

void loop() {
  accelgyro.getAcceleration(&ax, &ay, &az);


    lr=map(ax,-17000,18000,950,3000);
    fb=map(ay,-17000,17000,3000,950);

    ADCFilter.Filter(lr);
    ADCFilter2.Filter(fb);
  Serial.print(lr);
  Serial.print(",");
  Serial.println(fb);
delay(50);



}
