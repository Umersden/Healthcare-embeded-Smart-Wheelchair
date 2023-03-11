#include <SoftwareSerial.h>
SoftwareSerial mySerial =  SoftwareSerial(10, 11);
//SoftwareSerial mySerial2 =  SoftwareSerial(8, 9);

#include <OneWire.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     100
PulseOximeter pox;

uint32_t tsLastReport = 0;
int incomingByte = 0; // for incoming serial data
int x[10]={};
int j=0;int tmp=0;
String input;
int input2;
int currentTemp;
char state[20];
int heartrate,spo2,up,down,pulse;

float dallas(int x,byte start){
    OneWire ds(x);
    byte i;
    byte data[2];
    int16_t result;
    float temperature;
    do{
        ds.reset();
        ds.write(0xCC);
        ds.write(0xBE);
        for (int i = 0; i < 2; i++) data[i] = ds.read();
        result=(data[1]<<8) |data[0];
        // Here you could print out the received bytes as binary, as requested in my comment:
        // Serial.println(result, BIN);
        int16_t whole_degree = (result & 0x07FF) >> 4; // cut out sign bits and shift
        temperature = whole_degree + 0.5*((data[0]&0x8)>>3) + 0.25*((data[0]&0x4)>>2) + 0.125*((data[0]&0x2)>>1) + 0.625*(data[0]&0x1);
        if (data[1]&128) temperature*=-1;
        ds.reset();
        ds.write(0xCC);
        ds.write(0x44, 1);
        if (start) delay(1000);
    } while (start--);
    return temperature;
}

void start()
{
  digitalWrite(5,LOW);
  delay(500);
  digitalWrite(5,HIGH);
  }

  void startpox()
{
    Serial.print("Initializing pulse oximeter..");

    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
  }

  
void setup()
{
 Serial.begin(38400); // opens serial port, sets data rate to 9600 bps
  mySerial.begin(9600);

  pinMode(5,OUTPUT);
    digitalWrite(5,HIGH);
dallas(A0,1);
    Serial.print("Initializing pulse oximeter..");

    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback for the beat detection
//    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
    // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        //Serial.print("Heart rate:");
        //Serial.print(pox.getHeartRate());
       // heartrate=pox.getHeartRate();
        //Serial.print("bpm / SpO2:");
        //Serial.print(pox.getSpO2());
        //Serial.print("% ");
      //  spo2=pox.getSpO2();
       //currentTemp = dallas(A0,0);
       //Serial.print("Temp: ");
       //Serial.println(currentTemp);
       
       
        tsLastReport = millis();
    }
       if(Serial.available()){
        input = Serial.readStringUntil('\n');
        Serial.print(input);
        input2=input.toInt();
        
         if(input2==1)
         {
         start();
         
         }
         else if(input2==2)
         {
          startpox();
          
          }
   }
     
  if (mySerial.available() > 0) {
    // read the incoming byte:
    incomingByte = mySerial.read();
    tmp=incomingByte;
    if(tmp==255 || j>9)
    j=0;
    x[j]=tmp;
    j++;
//    // say what you got:
     //Serial.print("I received: ");
    if(x[9]!=49 || x[9]!=50)
   {
    up=x[6];
    down=x[8];
    pulse=x[9];
//    Serial.print(x[6]);
//    Serial.print(",");
//    Serial.print(x[8]);
//    Serial.print(",");
  //  Serial.println(x[9]);
  }
  }
  heartrate=pox.getHeartRate();
        
        spo2=pox.getSpO2();
       currentTemp = dallas(A0,0);
  sprintf_P(state, (PGM_P)F("%03d%03d%03d%03d%03d%03d"), heartrate,spo2,currentTemp,up,down,pulse);
 
  Serial.println(state);

 delay(50);
  }
