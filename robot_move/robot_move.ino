
#include <Wire.h>
#include <ZumoShield.h>

#include <IRLibDecodeBase.h> 
#include <IRLib_P01_NEC.h>   
#include <IRLib_P02_Sony.h>  
#include <IRLib_HashRaw.h>
#include <IRLibCombo.h>
#include <IRLibRecv.h> 


IRdecode myDecoder;
IRrecv myReceiver(2);    //create a receiver on pin number 2

#define LED_PIN 13
ZumoMotors motors;



void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
if (myReceiver.getResults()) {
    myDecoder.decode();
    //myDecoder.dumpResults(false);
    if (myDecoder.protocolNum == NEC) {
      switch(myDecoder.value) {
        case 0xFD08F7: // Forward left
          Serial.println(F("Key 1"));
          for (int speed = 0; speed <= 100; speed++) {
            motors.setRightSpeed(speed);
            delay(2);
          }

          break;
          
        case 0xFD8877: // Straight
          Serial.println(F("Key 2"));
          digitalWrite(LED_PIN, HIGH);

          for (int speed = 0; speed <= 100; speed++) {
              motors.setLeftSpeed(speed);
              motors.setRightSpeed(speed);
              delay(2);
            }
          break;
          
        case 0xFD48B7: // Forward right
          Serial.println(F("Key 3"));
          for (int speed = 0; speed <= 100; speed++) {
            motors.setLeftSpeed(speed);
            delay(2);
          }

          break;
          
        case 0xFD28D7: // Claw open
          Serial.println(F("Key 4"));         
          break;
          
        case 0xFDA857: // Stop
          Serial.println(F("Key 5"));
            motors.setLeftSpeed(0);
            motors.setRightSpeed(0);
          break;
          
        case 0xFD6897:  // Head up
          Serial.println(F("Key 6")); 
          break;
          
        case 0xFD18E7: // Claw close
          Serial.println(F("Key 7"));           
          break;
          
        case 0xFD9867:
          Serial.println(F("Key 8"));
          digitalWrite(LED_PIN, LOW);
          for (int speed = 0; speed >= -100; speed--) {
            motors.setLeftSpeed(speed);
            motors.setRightSpeed(speed);
            delay(2);
          }

          break;
        case 0xFD58A7: // Head down
          Serial.println(F("Key 9"));
          break;
          
        case 0xFD40BF:  
          Serial.println(F("Key Stop"));
          break;          
      }
    
    myReceiver.enableIRIn(); //Restart the receiver
    }
  }
}
