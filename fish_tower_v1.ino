
/* 
fish_tower_v1.ino, Vincent Gosselin 2022.

FishTower project. 

Target hardware : ArduinoMega2560

Description:

There are 10x laser_trip_circuit hooked to the arduino
to trigger the 5x Camdoo cameras. The Camdoo camera have a feedback signal.
The cameras can also be triggered by 5x PIR sensors. 


Version: 1.o

*/

//#include "arduino"

#include "ARDUINO1.h"
#include "arduinotools.h"

//From arduinotools.h
SmartWait smartWait0;

//ALL CLASSES ARE FROM ARDUINO1

//Components
Lasertrip Lasertrip1A(13); //pin13 lasertrip pcb1 with channel A.
Camdo Camdo1(8,9); //Camdo #1, pin 8 trigger , pin 9 feedback.

void setup()
{
  initiate();
}


/*
The main loop reads the status of the pushButton and writes the value
to Blink to trigger the camera. It then checks the camera feedback 
and flashes the onboard Arduino LED
accordingly.
*/

void loop()
{

  //listen to lasertrip circuits
  Lasertrip1A.listen();
  
  //Did an event happenned?
  if(Lasertrip1A.get_status() == 1){
    //a fish was detected!
    Serial.print("a fish was detected!, laser tripped!  \n\r");
    //activate the camera
    Serial.print("Activating the Camera \n\r");
    Camdo1.fire();
    //wait a bit for camera reply
    delay(1000);
    //read back the camera
    Serial.print("Sensing the Camera \n\r");
    Camdo1.listen();
    Serial.print("Camdo1 status is ");
    Serial.println(Camdo1.get_status());
    //cool down on the camera trigger
    delay(5000);
    Serial.print("Cool down over \n\r");
    Serial.print("Lasertrip sensing \n\r");
  }
}


//Every 10 secs.
//if(smartWait0.wait(10000)) {}

void initiate()
{
	//Start Serial communication for debugging.
	Serial.begin(9600);
	Serial.println("Connected");
	Serial.println("Arduino firmware 20220604");
	//Init components
	// Growlight.init();
	// BULB.init();
	// FAN_INTAKE.init();
	// FAN_OUTTAKE.init();
	//LCD uses Serial3.
	//display_welcome();	
}
