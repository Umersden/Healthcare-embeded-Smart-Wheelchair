char state;
String s1,s2,s3,s4,s5,s6,s7,s8;
String incommingStr;
String incommingStr2;
int fb,lr,active,i4,i5,i6,i7,i8;
String testbyte;

#include <Wire.h>
#define TCAADDR 0x70
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 forward;
Adafruit_MCP4725 back;
Adafruit_MCP4725 right;
Adafruit_MCP4725 left;

void TCAChannel(uint8_t i) {
  Wire.beginTransmission(0x70);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void voltage(int channel,Adafruit_MCP4725 &DAC, long value) {
  TCAChannel(channel);
  DAC.setVoltage(value,false);

}


void setup() {
 Serial.begin(38400);
 Serial1.begin(38400);
 Serial2.begin(38400);
 Serial3.begin(9600);
 
pinMode(7,OUTPUT);
  forward.begin(0x60);
  back.begin(0x60);
  right.begin(0x60);
  left.begin(0x60);
  voltage(0,forward,2048);
  voltage(1,back,2048);
  voltage(2,right,2048);
  voltage(3,left,2048);
 
// Serial.setTimeout(200);

}

void loop() {

//while(!Serial2.available());{
if(Serial3.available()>0){

int s1 = Serial3.read();// s1 is String type variable.
     if(s1==1)
     {
      Serial1.println("1");
     
    }
     if(s1==2)
     {Serial1.println("2");
      }


}

if(Serial2.available()>0){
  incommingStr = Serial2.readStringUntil('\n');
     if(incommingStr.length()==10)
     {
      
       s1=incommingStr.substring(0,4);
      s2=incommingStr.substring(4,8);
      s3=incommingStr.substring(8,9);
      fb=s1.toInt();
      lr=s2.toInt();
      active=s3.toInt();
      }


  }

  if(Serial1.available()>0){
  incommingStr2 = Serial1.readStringUntil('\n');
  if(incommingStr2.length()==19)
  {
    s4=incommingStr2.substring(0,3);
  s5=incommingStr2.substring(3,6);
  s6=incommingStr2.substring(6,9);
  s7=incommingStr2.substring(9,12);
  s8=incommingStr2.substring(12,15);
      i4=s4.toInt();
      i5=s5.toInt();
      i6=s6.toInt();
      i7=s7.toInt();
      i8=s8.toInt();
    }



  }

   Serial3.print("n0.val=");              //We print the variable we want to cahnge on the screen
  Serial3.print(i4);                        //Print the value we want to be displayed
  Serial3.write(0xff);                         //Always add 3 full bytes after...       
  Serial3.write(0xff);
  Serial3.write(0xff);

   Serial3.print("n1.val=");              //We print the variable we want to cahnge on the screen
  Serial3.print(i5);                        //Print the value we want to be displayed
  Serial3.write(0xff);                         //Always add 3 full bytes after...       
  Serial3.write(0xff);
  Serial3.write(0xff);

   Serial3.print("n2.val=");              //We print the variable we want to cahnge on the screen
  Serial3.print(i6);                        //Print the value we want to be displayed
  Serial3.write(0xff);                         //Always add 3 full bytes after...       
  Serial3.write(0xff);
  Serial3.write(0xff);

   Serial3.print("n3.val=");              //We print the variable we want to cahnge on the screen
  Serial3.print(i7);                        //Print the value we want to be displayed
  Serial3.write(0xff);                         //Always add 3 full bytes after...       
  Serial3.write(0xff);
  Serial3.write(0xff);

   Serial3.print("n4.val=");              //We print the variable we want to cahnge on the screen
  Serial3.print(i8);                        //Print the value we want to be displayed
  Serial3.write(0xff);                         //Always add 3 full bytes after...       
  Serial3.write(0xff);
  Serial3.write(0xff);
  

delay(10);

//Serial.println(s1+s2+s3);
//Serial.println(incommingStr2);


//Serial.print("Pulse: ");
//Serial.println(s4);
//Serial.print("OXY: ");
//Serial.println(s5);
//Serial.print("Temperature: ");
//Serial.println(s6);
//Serial.print("Dia: ");
//Serial.println(s7);
//Serial.print("Systolic: ");
//Serial.println(s8);

 Serial.print(lr);
  Serial.print(",");
  Serial.println(fb);
    
    if(active==1)
    {
      voltage(0,forward,lr);
          voltage(1,back,lr);
           voltage(2,right,fb);
            voltage(3,left,fb);
    }
    else
    {
      voltage(0,forward,2095);
          voltage(1,back,2095);
           voltage(2,right,2095);
            voltage(3,left,2095);
      }
      
 delay(0);
 state=0;

}
