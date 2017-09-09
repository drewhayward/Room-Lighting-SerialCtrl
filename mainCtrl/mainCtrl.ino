
/* Misc Variables */
int serialRate = 9600;
char buf[24];

/* Relay Pins */
int christmasPin = 22;
int deskLampPin = 23;
int standingLampPin = 24;

/* RGB Pins */
// Sign pins
int signRedPin = 2;
int signGreenPin = 3;
int signBluePin = 4;

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
  for(int i = 0; i < 3; i++){
    buf[i] = Serial.read();
  }
  
  switch (command){
    default:
      break;
  }
}

// Writes the set values to the pins
void writeValues(){
  // Set RGB Strips
  analogWrite(signRedPin, sign.red);
  analogWrite(signGreenPin, sign.green);
  analogWrite(signBluePin, sign.blue);
  
  analogWrite(closetRedPin, closet.red);
  analogWrite(closetGreenPin, closet.green);
  analogWrite(closetBluePin, closet.blue);
  
  analogWrite(bedRedPin, bed.red);
  analogWrite(bedGreenPin, bed.green);
  analogWrite(bedBluePin, bed.blue);
}

void setup() {
  Serial.begin(serialRate);
  // Reload the previous lighting state
  
}

void loop() {
  writeValues();
  char hex[3] = {0x1a,0xe3,0x2f};
  setColor(sign,hex);
  // Process Serial Command
  if(Serial.available() > 0){
    char firstByte = Serial.read();
    Serial.print(firstByte);
    //processSerial(firstByte);
  }
}
