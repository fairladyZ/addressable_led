#include <Adafruit_NeoPixel.h>

#define PIN 6 //This is for the sealed box 
//#define PIN 12  //This is for the pill bottle mode

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_RGB + NEO_KHZ800);

int delayval = 500; // delay for half a second

const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

int purpleColor[] = {80, 0, 255};
int orangeColor[] = {255, 50, 0};

int startColor[] = {255, 0, 0};
int endColor[] = {0, 255, 0};

void setColors(int selection){
  startColor[0] = 0;
  startColor[1] = 0;
  startColor[2] = 0;

  endColor[0] = 0;
  endColor[1] = 0;
  endColor[2] = 0;
  
  switch(selection) {
    case 1:
      startColor[0] = purpleColor[0];
      startColor[1] = purpleColor[1];
      startColor[2] = purpleColor[2];

      endColor[0] = orangeColor[0];
      endColor[1] = orangeColor[1];
      endColor[2] = orangeColor[2];
    break;
    case 2:
      startColor[0] = 255;
      endColor[2] = 255;
    break;
    case 3:
    break;
    
    default:
    case 0:
      startColor[0] = 255;
      endColor[1] = 255;
    break;
  }  
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start LED strip");
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  //Choose color theme
  //0 is debug/christmas
  //1 is halloween
  //2 is 4th of july but only two colors
  setColors(2);
}

void loop() {
  
  //Normal mode
  uint32_t color = strip.Color(0, 255, 255);
  uint32_t blank = strip.Color(0,0,0);
  colorWipe(color, 400);
  delay(55*1000);
  colorWipe(blank, 400);
  delay(100);

  //Halloween
  //hallowCycle(1000);


  /*testing
  colorHalf(0, strip.Color(0, 0, 255));
  colorHalf(1, strip.Color(80, 0, 255));
  strip.show();
  while(1);
  /**/

  
  
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    
    // if it's a capital B go crazy blinky
    if (incomingByte == 'B') {
      Serial.println("cRaZy BlInKy MoDe");
      theaterChase(strip.Color(127, 127, 127), 100); // White
      Serial.println("Mode Done  READY");
    } 
    // if it's an T set the Teal Color
    if (incomingByte == 'T') {
      Serial.println("Teal Mode");
      colorWipe(strip.Color(0, 150, 200), 50); // Red
      Serial.println("Mode Done  READY");
    }
    // if it's an R do the rainbow chase
    if (incomingByte == 'R') {
      Serial.println("Chasy Rainbow Mode");
      theaterChaseRainbow(50);
      Serial.println("Mode Done  READY");
    }
    // if it's an A do the rainbow 
    if (incomingByte == 'A') {
      Serial.println("Just Rainbow Mode");
      rainbow(20);
      Serial.println("Mode Done  READY");
    }
    // if it's an T do the rainbow cycle
    if (incomingByte == 'T') {
      Serial.println("Rainbow Cycle Mode");
      rainbowCycle(20);
      Serial.println("Mode Done  READY");
    }
    // if it's an H do the Halloweel
    if (incomingByte == 'H') {
      Serial.println("Halloweel Mode");
      hallowCycle(1000);
      Serial.println("Mode Done  READY");
    }
    // if it's an 4 do the 4th ofjuly
    if (incomingByte == '4') {
      Serial.println("Stars and Stripes Mode");
      rainbowCycle(20);
      Serial.println("Mode Done  READY");
    }
    // if it's an C do the Christmas
    if (incomingByte == 'C') {
      Serial.println("Christmas Mode");
      rainbowCycle(20);
      Serial.println("Mode Done  READY");
    }
    // if it's an E do the Easter
    if (incomingByte == 'E') {
      Serial.println("Easter Mode");
      rainbowCycle(20);
      Serial.println("Mode Done  READY");
    }
  }
  
}

uint32_t getColorForLoop(int percent){
  if (percent > 100) percent = 200 - percent;
  
  int diffR = endColor[0] - startColor[0];
  int diffG = endColor[1] - startColor[1];
  int diffB = endColor[2] - startColor[2];
  
  diffR = (diffR * percent) / 100;
  diffG = (diffG * percent) / 100;
  diffB = (diffB * percent) / 100;

  return strip.Color(startColor[0] + diffR, startColor[1] + diffG, startColor[2] + diffB);
}

void hallowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      //strip.setPixelColor(i, halloWheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip.setPixelColor(i, halloWheel(i+j));
    }
    strip.show();
    delay(wait);
  }
}


uint32_t halloWheel2(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  
  uint32_t color;
  
  int fade[] = {15,0,0,0,0,0,15,50,
                85,100,100,100,100,100,85,50};
  
  int fadeIndex = wheelPos % 16;

  color = getColorForLoop(fade[fadeIndex]);
  
  return color;
}

uint32_t halloWheel(byte wheelPos) {
  
  wheelPos = 255 - wheelPos;
  
  uint32_t color;
  
  int fade[] = {0,0,0,0,0,1,1,1,
                1,1,2,2,2,2,2,0};
  
  //int fade[] = {0,0,0,0,0,1,1,1,
  //              2,2,2,2,2,1,1,1};
  
  int fadeIndex = wheelPos % 16;

  switch(fade[fadeIndex]) {
    case 0:
      color = strip.Color(purpleColor[0], purpleColor[1], purpleColor[2]);
      //color = strip.Color(255, 0, 0);
    break;
    case 1:
      color = strip.Color(orangeColor[0], orangeColor[1], orangeColor[2]);
      //color = strip.Color(255, 255, 255);
    break;
    case 2:
      color = strip.Color(0, 255, 0);
      //color = strip.Color(0, 0, 255);
    break;
  }
  
  return color;
}
 

//For debug, color half of the strip 
void colorHalf(int whichHalf, uint32_t c)
{
  int start = 0;
  int end = strip.numPixels()/2;
  
  if(whichHalf != 0)
  {
    start = end;
    end = strip.numPixels();
  }
  
  for(uint16_t i=start; i<end; i++) {
      strip.setPixelColor(i, c);
  }
}

