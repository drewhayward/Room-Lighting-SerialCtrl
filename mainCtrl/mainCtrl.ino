
/* Misc Variables */
int serialRate = 9600;
char buf[24]

/* Relay Pins */
int christmasPin = 22;
int deskLampPin = 23;
int standingLampPin = 24;

/* RGB Pins */
// Sign pins
int signRedPin;
int signGreenPin;
int signBluePin;

// Closet Pins
int closetRedPin;
int closetGreenPin;
int closetBluePin;

// Bed Pins 
int bedRedPin;
int bedGreenPin;
int bedBluePin;

/* RGB Strips */
struct RGBStrip {
  char red;
  char green;
  char blue;
};

struct RGBStrip sign;
struct RGBStrip closet;
struct RGBStrip bed;



bool standinglamp = true;
bool deskLamp = true;
bool christmasLights = true;

// Sets the given strip to the hex value
void setColor(struct RGBStrip& strip, char hex[3]){
  strip.red = hex[0];
  strip.green = hex[1];
  strip.blue = hex[2];
}

// Process serial command
void processSerial(char command){
  switch (command){
    default:
      return;
      break;
  }
}

// Writes the set values to the pins
void writeValues(){
  
}

void setup() {
  Serial.begin(serialRate);

  

  
  // Reload the previous lighting state
  
}

void loop() {
  // Process Serial Command
  if(Serial.available()){
    char firstByte = Serial.read();
    processSerial(firstByte);
  }
}
