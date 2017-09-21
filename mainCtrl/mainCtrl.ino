
/* Misc Variables */
int serialRate = 9600;
char buf[24];

/* Colors */
char white[3] = {255,255,255};
char off[3] = {0,0,0};

/* Relay Pins */
int christmasPin = 24;
int deskLampPin = 23;
int standingLampPin = 22;

/* RGB Pins */
// Sign pins
int signRedPin;
int signGreenPin;
int signBluePin;

// Closet Pins
int closetRedPin = 5;
int closetGreenPin = 6;
int closetBluePin = 7;

// Bed Pins
int bedRedPin = 2;
int bedGreenPin = 3;
int bedBluePin = 4;

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

// Maps the byte codes to the pins of the lights
int getLightPin(char code){
  switch(code){
    case 0x01:
      return christmasPin;
    case 0x02:
      return standingLampPin;
    case 0x03:
      return deskLampPin;
    default:
      return 0x00;
  }
}

struct RGBStrip* getStrip(char code){
  switch(code){
    case 0x11:
      return &sign;
      break;
    case 0x12:
      return &closet;
      break;
    case 0x013:
      return &bed;
      break;
    default:
      return 0x00;
  }
}

// Sets the given light to the state
void setLight(char light, bool state){
  Serial.println("setLight()");
  switch (light) {
    // Christmas Lights
    case 0x01:
      Serial.println("Christmas");
      christmasLightsOn = state;
      break;
    // Standing lamp
    case 0x02:
      Serial.println("Standing Lamp");
      standingLampOn = state;
      break;
    // Desk lamp
    case 0x03:
      Serial.println("Desk Lamp");
      deskLampOn = state;
      break;
    // Sign
    case 0x11:
      Serial.println("Sign");
      if(state){
        setColor(sign, white);
      } else {
        setColor(sign, off);
      }
      break;
    // Closet
    case 0x12:
      Serial.println("Closet");
      if(state){
        setColor(closet, white);
      } else {
        setColor(closet, off);
      }
      break;
    // Bed
    case 0x13:
      Serial.println("Bed");
      if(state){
        setColor(bed, white);
      } else {
        setColor(bed, off);
      }
      break;
    // Kill all
    case 0xff:
      setColor(bed, off);
      setColor(sign, off);
      setColor(closet, off);
      deskLampOn = false;
      christmasLightsOn = false;
      standingLampOn = false;
      break;
  }
}

// Attempts to read n bytes from the serila buffer
void serialReadBytes(int n){
  Serial.println("serialReadBytes");
  for(int i = 0; i < n; i++){
    buf[i] = Serial.read();
    Serial.println("Got item");
  }
}

// Process serial command
void processSerial(char command){
  Serial.println("processSerial()");
  switch (command){
    // Breathe LEDS
    // Turn off light
    case 0x00:
      serialReadBytes(1);
      setLight(buf[0], false);
      break;
    // Turn on light
    case 0x01:
      serialReadBytes(1);
      setLight(buf[0], true);
      break;
    // Set LED color
    case 0x02:
      serialReadBytes(4);

      // If
      setColor(*getStrip(buf[0]), buf + 1);
      break;
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
  digitalWrite(christmasPin, !christmasLightsOn);
  digitalWrite(standingLampPin, !standingLampOn);
  digitalWrite(deskLampPin, !deskLampOn);
}

void setup() {
  Serial.begin(serialRate);

  // Pin init
  pinMode(christmasPin,OUTPUT);
  pinMode(deskLampPin, OUTPUT);
  pinMode(standingLampPin, OUTPUT);
  pinMode(signRedPin, OUTPUT);
  pinMode(signBluePin, OUTPUT); 
  pinMode(signGreenPin, OUTPUT);
  pinMode(closetRedPin,OUTPUT);
  pinMode(closetBluePin, OUTPUT);
  pinMode(closetGreenPin, OUTPUT);
  pinMode(bedRedPin, OUTPUT);
  pinMode(bedGreenPin, OUTPUT);
  pinMode(bedBluePin,OUTPUT);

  Serial.println("Loaded");
  // Load last config
}

char  b;

void loop() {
  if(Serial.available() > 0){
    delay(9);
    Serial.println("Command");
    b = Serial.read();
    if(b == 0x111){
      Serial.println(b, DEC);
    }
    processSerial(b);
  }

  writeValues();
}
