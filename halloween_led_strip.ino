#include <Adafruit_NeoPixel.h>
#include "colors.h"

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

const int ledPin = 13; // the pin that the LED is attached to

int mode = 1;
int demoMode; //set mode to -1 for these
int paused = 0;




void setup() {
  Serial.begin(9600);
  Serial.println("Start LED strip");
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {
  
  /*testing
  colorWipe(strip.Color(0, 0, 0), 0);
  
  
  colorHalf(0, strip.Color(255, 255, 0));
  colorHalf(1, strip.Color(255, 224, 0));
  strip.show();
  while(1);
  /**/

  checkSerial();
  if (!paused) {
    runMode(mode);
  } else {
    delay(400);
  }
  
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

uint32_t halloWheel(byte wheelPos) {
  
  wheelPos = 255 - wheelPos;
  
  uint32_t color;
  
  int fade[] = {0,0,0,0,0,1,1,1,
                1,1,2,2,2,2,2,0};
    
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

