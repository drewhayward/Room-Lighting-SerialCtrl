
/* Misc Variables */
int serialRate = 9600;
char buf[24];

/* Colors */
char[3] white = {255,255,255};
char[3] off = {0,0,0};

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

bool standingLampOn = true;
bool deskLampOn = true;
bool christmasLightsOn = true;

// Sets the given strip to the hex value
void setColor(struct RGBStrip& strip, char hex[3]){
  strip.red = hex[0];
  strip.green = hex[1];
  strip.blue = hex[2];
}

void setLight(char light, bool state){
  switch (light) {
    // Christmas Lights
    case 0x01:
      christmasLightsOn = state;
      break;
    // Standing lamp
    case 0x02:
      standingLampOn = state;
      break;
    // Desk lamp
    case 0x03:
      deskLampOn = state;
      break;
    // Sign
    case 0x11:
      if(state){
        setColor(sign, white);
      } else {
        setColor(sign, off);
      }
      break;
    // Closet
    case 0x12:
      if(state){
        setColor(closet, white);
      } else {
        setColor(closet, off);
      }
      break;
    // Bed
      if(state){
        setColor(bed, white);
      } else {
        setColor(bed, off);
      }
      break;
    // Kill all
    case 0xff:
  }
}
// Attempts to read n bytes from the serila buffer
void serialReadBytes(n){
  for(int i = 0; i < n; i++){
    buf[i] = Serial.read();
  }
}

// Process serial command
void processSerial(char command){
  switch (command){
    // Breathe LEDS
    // Fade LEDS
    // Turn off light
    // Set LED Color
    // Turn off light
    case 0x00:
      serialReadBytes(1);
      turnOff(b[1]);
      break;
    // Turn on light
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

  // Set outlet relay
  digitalWrite(christmasPin, christmasLightsOn);
  digitalWrite(standingLampPin, standingLampOn);
  digitalWrite(deskLampPin, deskLampOn);
}

char b;
void setup() {
  Serial.begin(serialRate);
  // Reload the previous lighting state
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    b = Serial.read();
    if(b == 0xb){
      digitalWrite(LED_BUILTIN,HIGH);
    } else if (b == 0xa){
      digitalWrite(LED_BUILTIN,LOW);
    }
  }
}
