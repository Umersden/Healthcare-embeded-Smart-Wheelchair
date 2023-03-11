#include <SoftwareSerial.h>
SoftwareSerial mySerial =  SoftwareSerial(10, 11);
//SoftwareSerial mySerial =  SoftwareSerial(6, 7);
int incomingByte = 0; // for incoming serial data
int x[10]={};
int i=0;int tmp=0;
int input;

void start()
{
  digitalWrite(3,LOW);
  delay(500);
  digitalWrite(3,HIGH);
  }
  
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  mySerial.begin(9600);
  pinMode(3,OUTPUT);
    digitalWrite(3,HIGH);

}

void loop() {
  // send data only when you receive data:
   if(Serial.available()){
        input = Serial.read();
        Serial.print(input);
         if(input==49)
   {start();}
   }
  
  if (mySerial.available() > 0) {
    // read the incoming byte:
    incomingByte = mySerial.read();
    tmp=incomingByte;
    if(tmp==255 || i>9)
    i=0;
    x[i]=tmp;
    i++;
    // say what you got:
    Serial.print("I received: ");
    if(x[9]!=49)
    Serial.println(x[9]);
  }
  }
