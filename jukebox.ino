#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int buttonPins[16] = {19,18,17,16,15,14,2,3,4,5,6,7,8,9,12,13};
int queue[2] = {0};

void setup() {
  mySoftwareSerial.begin(9600);      
  Serial.begin(115200);              

  if (!myDFPlayer.begin(mySoftwareSerial)) {  
  }
    
  myDFPlayer.volume(20);
  for (int i=0; i<16; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);   
  }
  
}


void loop() {
  if ((digitalRead(0)== HIGH) && (queue[1] != 0)){
    myDFPlayer.playMp3Folder(queue[1]);
    queue[1]=0;
    delay(200);
  }
  else {
    for (int i=0; i<8; i++) 
      if (digitalRead(buttonPins[i]) == LOW) {
        for (int j=8; j<16; j++)
          if (digitalRead(buttonPins[j]) == LOW) {
            if (digitalRead(0)== HIGH) {
              myDFPlayer.playMp3Folder(i*10+(j-7));
              delay(200);
            }
        
            else {
              queue[1]=i*10+(j-7);
              }
          }
      }  
    }
}
