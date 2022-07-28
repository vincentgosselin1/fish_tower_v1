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
Lasertrip Lasertrip1B(12); //pin12 lasertrip pcb1 with channel B.
Lasertrip Lasertrip2A(11); 
Lasertrip Lasertrip2B(10); 
Lasertrip Lasertrip3A(9);
Lasertrip Lasertrip3B(8);
Lasertrip Lasertrip4A(7);
Lasertrip Lasertrip4B(6);
Lasertrip Lasertrip5A(5);
Lasertrip Lasertrip5B(4);

Camdo Camdo1(35,37); //Camdo #1, pin 35 trigger 3.5mm , pin 37 feedback 2.5mm.

PIR_sensor PIR_sensor1(28);
//PIR_sensor PIR_sensor2(29);
//PIR_sensor PIR_sensor3(30);
//PIR_sensor PIR_sensor4(31);

SmartWait SmartWait1;

void setup()
{
  initiate();
}

void loop()
{

  //listen to lasertrip circuits
  Lasertrip1A.listen();
  Lasertrip1B.listen();
  Lasertrip2A.listen();
  Lasertrip2B.listen();
  Lasertrip3A.listen();
  Lasertrip3B.listen();
  Lasertrip4A.listen();
  Lasertrip4B.listen();
  Lasertrip5A.listen();
  Lasertrip5B.listen();
  PIR_sensor1.listen();
  Camdo1.stop();
  
  //PIR_sensor2.listen();
  //PIR_sensor3.listen();
  //PIR_sensor4.listen();
  
  //Did an event happenned?
  //if((Lasertrip1A.get_status() == 1) or (PIR_sensor1.get_status() == 1)){
  // if(    Lasertrip1A.get_status() or Lasertrip1B.get_status() \
  //      or Lasertrip2A.get_status() or Lasertrip2B.get_status() \
  //      or Lasertrip3A.get_status() or Lasertrip3B.get_status() \
  //      or Lasertrip4A.get_status() or Lasertrip4B.get_status() \
  //      or Lasertrip5A.get_status() or Lasertrip5B.get_status() \
  // 	 //or PIR_sensor1.get_status()
  // 	 ){

    if(    Lasertrip1A.get_status() or Lasertrip1B.get_status() 
	or Lasertrip2A.get_status() or Lasertrip2B.get_status() 
	or Lasertrip3A.get_status() or Lasertrip3B.get_status()
	or Lasertrip4A.get_status() or Lasertrip4B.get_status()
	or Lasertrip5A.get_status() or Lasertrip5B.get_status()
	   //or PIR_sensor1.get_status()
         ){
    
    //a fish was detected!
    Serial.print("a fish was detected!, laser tripped!  \n\r");
    //activate the camera
    Serial.print("Activating the Camera \n\r");
    Camdo1.run();//setting it low
    
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
    Camdo1.stop();//setting it high
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
	Serial.println("Arduino firmware 20220728_16h53");
	
}
