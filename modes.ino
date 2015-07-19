

void (*modeFuntions[])() = {0, runNormalMode, runHalloween, runChristmas, runEaster, runForthOfJuly};
void (*demoFuntions[])() = {runCrazyBlinky, runChaseRainbow, runRainbow, runRainbowCycle};

void runMode(int modeNumber) {
  uint32_t blank = stripColorFromColor(blankColor);
  static int oldMode = -1;
  
  switch (modeNumber) {
    default:
    case 0: //off
      //only run once
      if(oldMode != modeNumber){
        colorWipe(blank, 0);
        delay(1000);
      } else {
        delay(400);  
      }
    break;
    case 1: //default
      runNormalMode();
    break;    
    case 2: //Halloween
    case 3: //Christmas
    case 4: //Easter
    case 5: //4th of July
      Serial.println("calling normal function");
      (*modeFuntions[modeNumber])();  //call appropriate demo function
    break;
    case -1:
      Serial.println("calling demo function");
      (*demoFuntions[demoMode])();  //call appropriate demo function
      //runDemoMode();
    break;
  }
  oldMode = modeNumber;
}

void runLightTealWipe()
{
  uint32_t color = stripColorFromColor(lightTealColor);
  uint32_t blank = stripColorFromColor(blankColor);
  
  colorWipe(color, 400);
  delaySeconds(66);
  colorWipe(blank, 400);
  delay(100);  
}

void runNormalMode(){
  runLightTealWipe();
}



void runCrazyBlinky()
{
  Serial.println("cRaZy BlInKy MoDe");
  theaterChase(strip.Color(127, 127, 127), 100); // White
  Serial.println("Mode Done  READY");  
}

void runChaseRainbow()
{
  Serial.println("Chasy Rainbow Mode");
  theaterChaseRainbow(50);
  Serial.println("Mode Done  READY");
}

void runRainbow()
{
  Serial.println("Just Rainbow Mode");
  rainbow(20);
  Serial.println("Mode Done  READY");
}

void runRainbowCycle()
{
  Serial.println("Rainbow Cycle Mode");
  rainbowCycle(20);
  Serial.println("Mode Done  READY");
}

void runHalloween()
{
  Serial.println("Halloweel Mode");
  hallowCycle(1000);
  Serial.println("Mode Done  READY");
}

void runForthOfJuly()
{
  Serial.println("Stars and Stripes Mode");
  colorWipe(strip.Color(255, 0, 0), strip.Color(255, 255, 255), strip.Color(0, 0, 255), 100);
  Serial.println("Mode Done  READY");
}

void runChristmas()
{
  Serial.println("Christmas Mode");
  colorWipe(strip.Color(255, 0, 0), strip.Color(0, 255, 0), 100);
  Serial.println("Mode Done  READY");
}

void runEaster()
{
  Serial.println("Easter Mode");
  colorWipe(stripColorFromColor(magentaColor), stripColorFromColor(yellowColor), stripColorFromColor(tealColor), 100);
  Serial.println("Mode Done  READY");
}


