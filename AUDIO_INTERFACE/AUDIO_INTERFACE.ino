#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

const int potPin = A0;
int potValue;
int mappedVolume;
// Create the Player object
DFRobotDFPlayerMini player;

void setup() {

  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.play(1);
    player.enableLoop();
    
 
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  potValue = analogRead(potPin);
  mappedVolume = map(potValue, 0, 1023, 0, 30); // Map potentiometer range to DFPlayer volume range

  if (mappedVolume != player.readVolume()) {
    player.volume(mappedVolume);
    Serial.print("Volume: ");
    Serial.println(mappedVolume);
  }
  

   }
   