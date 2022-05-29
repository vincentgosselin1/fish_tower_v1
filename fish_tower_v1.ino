
/* 
fish_tower_v1.ino, Vincent Gosselin 2022.

FishTower project. 

Target hardware : ArduinoMega2560

Description:

There are 10x laser_trip_circuit hooked to the arduino
to trigger the 5x Camdoo cameras. The Camdoo camera have a feedback signal.
The cameras can also be triggered by 5x PIR sensors. 
hello

*/

//#include "arduino"

#include "ARDUINO1.h"
#include "arduinotools.h"


// constants used here to set pin numbers
const int ledPin =  5;            // the number of the LED pin (pre-defined)
const int cameraTriggerPin = 2;             // connected to digital pin 2
const int cameraStatusPin = 3;              // connected to digital pin 3
const int buttonPin = 7;               // pushbutton connected to digital pin 7
const long interval = 500;                  // LED flash interval (milliseconds)


//variables

int ledState = 0;                         // ledState used to set the LED
int cameraState = 0;                      // cameraState used to store camera status (on/off)
int buttonState = 0;                      // for reading the pushbutton status
unsigned long previousMillis = 0;           // will store last time LED was updated


void setup()
{
  pinMode(cameraTriggerPin, OUTPUT);        // set cameraTriggerPin as an output
  pinMode(cameraStatusPin, INPUT);          // sets cameraStatusPin as an input   
  pinMode(ledPin, OUTPUT);                  // sets ledPin as an output   
  pinMode(buttonPin, INPUT);                // sets buttonPin as an input     
  Serial.begin(9600);                       // open the serial port at 9600 bps:    
}


/*
The main loop reads the status of the pushButton and writes the value
to Blink to trigger the camera. It then checks the camera feedback 
and flashes the onboard Arduino LED
accordingly.
*/

void loop()
{


  buttonState = digitalRead(buttonPin);           // read the status of the pushbutton
  Serial.print("Button state:");       
  Serial.print("\t");                             // prints a tab
  Serial.println(buttonState);                    // print buttonState

  digitalWrite(cameraTriggerPin, buttonState);    // send the button status to Blink
  cameraState = digitalRead(cameraStatusPin);     // read the status of the camera from Blink

  Serial.print("Camera state:");       
  Serial.print("\t");                             // prints a tab
  Serial.println(cameraState);                    // print buttonState


  //check if we are going to flash the LED. ie Blink is reporting back that the camera is on.
  if (cameraState == HIGH) {

     
    // check if it's time to flash the LED; ie if the difference between the current time
    // and last time the LED flashed is bigger than the interval set above.

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
    // save the last time the LED flashed
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // write the ledState to the LED.
    digitalWrite(ledPin, ledState);

     }
  }
 
  else {
     digitalWrite (ledPin, LOW); // make sure the LED is off if camera state is LOW.
  }
}
