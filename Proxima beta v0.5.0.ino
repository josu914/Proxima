// Include NewPing Library
#include "NewPing.h"

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400	

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;

// Setting Arduino Pins
int ledPin = 13;                                  //LED PIN.
int buttonPin = 3;                         //Push Button for mode switching
int mode1Pin = 4;                           //green LED for Social Distancing Mode
int mode2Pin = 5;                          //blue LED for Temp Scan Mode
int mode3Pin = 6;                           //red LED for SOS Mode
int tempPin = 2;                             //relay VIN for switching TempScanner on/off
int buzzerPin = 7;                          //BUZZER INPUT PIN.
int pirPin = 8;                            //MOTION SENSOR INPUT PIN.

// Setting default value
int PsensorValue = LOW;                      //DEFAULT PIR SENSOR STATE
int buttonOld=1;
int buttonNew;
int detected=LOW;
int mode=1;

// Setting SOS morse code duration
int dit = 100; // Setting Value of dit as 150
int dah = 300; // settiing Value of dah as 500
int longWait = 500; // setting value of longW as 1000

// Setting the PIR scanner duration
unsigned long previousMillis = 0;  //will store last time LED was blinked
const long period = 2000;         // period at which to blink in ms

void setup() {                              //INITIAL SETTINGS FOR ARDUINO PINS
Serial.begin(9600);
  pinMode(pirPin, INPUT);                   
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);               
  pinMode(ledPin, OUTPUT);                 
  pinMode(mode1Pin, OUTPUT);
  pinMode(mode2Pin, OUTPUT);
  pinMode(mode3Pin, OUTPUT);
  pinMode(tempPin, OUTPUT);
}

void loop()                                 //COMMAND TO BE REPEATED.
{   
  // MODE SWITCHING PROGRAM  
   buttonOld = digitalRead(buttonPin);
  Serial.println(mode);
  if (buttonOld == 1 && buttonNew==0) 
    {
  
    } 
  else 
    {
      if(mode==4)
        {
          delay(300);
          mode=1;
          
        }
      else
        {
          delay(1000);
          mode++; 
        }
       buttonNew=buttonOld;
       delay(100);
    }


  switch(mode){
  
    case 1: // MODE 1: SOCIAL DISTANCING DEVICE
    {
      // TURNING OFF THE COMPONENTS USED IN MODE 3
      digitalWrite(mode3Pin, LOW);

      // MODE 1 MAIN CODE
      digitalWrite(mode1Pin, HIGH);
      unsigned long currentMillis = millis(); // store the current time
      distance = sonar.ping_cm();
      // Serial.print("Distance = ");              // Send results to Serial Monitor

      PsensorValue = digitalRead(pirPin);        //READ PIR INPUT PIN.
      // Serial.println(PsensorValue);
      if(PsensorValue>0)
      {
        if (currentMillis - previousMillis >= period) { // check if ?ms passed
          previousMillis = currentMillis;   // save the last time you blinked the LED
          if(detected==LOW)
          {
            detected=HIGH;
          }
          else
          {
            detected=LOW;
          }
        }
      }
      // Serial.println(detected);
      digitalWrite(ledPin, detected);

      if (detected==HIGH && distance <= 102 && distance >= 0)
      {               
        digitalWrite(buzzerPin, HIGH);           //BUZZ THE BUZZER. 
        digitalWrite(ledPin, HIGH);             //ON LED.
        
      }

      else                                      //IF NO MOTION IS DETECTED.
        {                                
        digitalWrite(buzzerPin, LOW);           //SILENT THE BUZZER.
        digitalWrite(ledPin, LOW);              //OFF LED.
        }

      if (distance >= 400 && distance <= 2) 
      {
        // Serial.println("Out of range");
        delay(100);
      }
      else 
      {
        // Serial.print(distance);
        // Serial.println(" cm");
        // delay (100);
      }
      break; 
    }       

    case 2: // MODE 2: TEMPERATURE SCANNER
    {
      // TURNING OFF THE COMPONENTS USED IN MODE 1
      digitalWrite(buzzerPin, LOW);           
      digitalWrite(ledPin, LOW);             
      digitalWrite(mode1Pin, LOW);
      // MODE 2 MAIN CODE
      digitalWrite(mode2Pin, HIGH);
      digitalWrite (tempPin, HIGH);

      break;
    }

     case 3: // MODE 3: SOS MODE
    {
      // TURNING OFF THE COMPONENTS USED IN MODE 2
      digitalWrite(buzzerPin, LOW);           
      digitalWrite(ledPin, LOW);              
      digitalWrite(mode2Pin, LOW);
      digitalWrite (tempPin, LOW);
      digitalWrite(mode3Pin, HIGH);

      // MODE 3 MAIN CODE    

        // DIT

        digitalWrite (ledPin,HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(dit);
        digitalWrite(ledPin, LOW); 
        digitalWrite(buzzerPin, LOW);
        delay(dit);

        //DIT

        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(dit);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(dit);

        //DIT

        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(dit);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(dah);

        //DAH


        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH); 
        delay(dah);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(dah);

        //DAH

        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH); 
        delay(dah);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(dah);

        //DAH

        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH); 
        delay(dah);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(dah);
        
        // DIT

        digitalWrite (ledPin,HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(dit);
        digitalWrite(ledPin, LOW); 
        digitalWrite(buzzerPin, LOW);
        delay(dit);

        //DIT

        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(dit);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(dit);

        //DIT

        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(dit);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(dit);
        
        
        //Giving a Gap before restarting

        delay(longWait);
      
        break;
    }

  }
  
}