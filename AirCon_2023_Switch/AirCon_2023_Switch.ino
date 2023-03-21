#include "myWifi.h"
myWifi myServer;


#include "OLED.h"
OLED myOled;



void setup() {
  myOled.Init();

  Serial.begin(115200);
  myServer.begin();   ///  wifi 연결

}

void loop() {

  //myServer.getData();


  myOled.displaySensorData("Hyun's Air Alarm", "Open the Window !!");

  delay(3000);

  myOled.drawMaple();

  delay(5000);
}