
/* 
fish_tower_v1.ino, Vincent Gosselin 2022.

FishTower project. 

Target hardware : Arduino Due

Description:

There are 10x laser_trip_circuit hooked to the arduino
to trigger the 5x Camdoo cameras. The Camdoo camera have a feedback signal.
The cameras can also be triggered by 5x PIR sensors. 


Version: 1.o

*/

#include "ARDUINO1.h"
#include "arduinotools.h"

//ALL CLASSES ARE FROM ARDUINO1

//Components
Lasertrip Lasertrip1A(13); //pin13 lasertrip pcb1 with channel A.
Camdo Camdo1(8,9); //Camdo #1, pin 8 trigger , pin 9 feedback.
PIR_sensor PIR_sensor1(10);
SmartWait SmartWait1;

void setup()
{
  initiate();
}

void loop()
{

  //listen to lasertrip circuits
  Lasertrip1A.listen();
  PIR_sensor1.listen();
  
  //Did an event happenned?
  //if(Lasertrip1A.get_status() == 1){
  if((Lasertrip1A.get_status() == 1) or PIR_sensor1.get_status() == 1){
    //a fish was detected!
    Serial.print("a fish was detected!, laser tripped!  \n\r");
    //activate the camera
    Serial.print("Activating the Camera \n\r");
    Camdo1.run();
    
    int i = 0;
    while(i<1000){
      i++;
      Serial.println(i, DEC);
    }

    //while(!SmartWait1.wait(1000));
    
    //read back the camera
    Serial.print("Sensing the Camera \n\r");
    Camdo1.listen();
    Serial.print("Camdo1 status is ");
    Serial.println(Camdo1.get_status());
    //stop camera.
    Camdo1.stop();
    //cool down on the camera trigger
    Serial.print("Cool down over \n\r");
    Serial.print("Lasertrip sensing \n\r");
  }
}

void initiate()
{
	//Start Serial communication for debugging.
	Serial.begin(9600);
	Serial.println("Connected");
	Serial.println("Arduino firmware 20220705_18h41PM");
	
}
