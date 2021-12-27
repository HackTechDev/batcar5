
#include <Wire.h>
#include <ZumoShield.h>

#include <IRLibDecodeBase.h> 
#include <IRLib_P01_NEC.h>   
#include <IRLib_P02_Sony.h>  
#include <IRLib_HashRaw.h>
#include <IRLibCombo.h>
#include <IRLibRecv.h> 

#include <Servo.h>

IRdecode myDecoder;
IRrecv myReceiver(2);    //create a receiver on pin number 2


Servo claw;
Servo head;  


int clawPos = 0;   
int headPos = 0;


void setup() {
  Serial.begin(9600);


  claw.attach(5);  
  head.attach(6);
  
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
if (myReceiver.getResults()) {
    myDecoder.decode();
    myDecoder.dumpResults(false);
    if (myDecoder.protocolNum == NEC) {
      switch(myDecoder.value) {
        case 0xFD08F7: // Forward left
          Serial.println(F("Key 1"));
          break;
          
        case 0xFD8877:
          Serial.println(F("Key 2"));
          break;
          
        case 0xFD48B7: 
          Serial.println(F("Key 3"));
          break;
          
        case 0xFD28D7: // Claw open
          Serial.println(F("Key 4"));
            for (clawPos = 0; clawPos <= 180; clawPos += 1) { 
              claw.write(clawPos);            
              delay(15);                   
            }
          break;
          
        case 0xFDA857:
          Serial.println(F("Key 5"));
          break;
          
        case 0xFD6897:  // Head up
          Serial.println(F("Key 6"));
          for (headPos = 0; headPos <= 180; headPos += 1) { 
            head.write(headPos);            
            delay(15);                   
          }
          break;
          
        case 0xFD18E7: // Claw close
          Serial.println(F("Key 7"));
          for (clawPos = 180; clawPos >= 0; clawPos -= 1) { 
            claw.write(clawPos);              
            delay(15);                    
          }
          break;
          
        case 0xFD9867:
          Serial.println(F("Key 8"));
          break;
        case 0xFD58A7: // Head down
          Serial.println(F("Key 9"));
          for (headPos = 180; headPos >= 0; headPos -= 1) { 
            head.write(headPos);              
            delay(15);                    
          }
          break;
          
        case 0xFD40BF:  
          Serial.println(F("Key Stop"));
          break;          
      }
    
    myReceiver.enableIRIn(); //Restart the receiver
    }
  }
}
