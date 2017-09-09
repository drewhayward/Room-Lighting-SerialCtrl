
/* Misc Variables */
int serialRate = 9600;

/* Relay Pins */
int christmasPin;
int deskLampPin;
int standingLampPin;

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

bool standinglamp;
bool deskLamp;
bool christmasLights;


void setup() {
  Serial.begin(serialRate);
  
  // Reload the previous lighting state
  
}

void loop() {
  
}
