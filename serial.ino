

void runTests(){
  Serial.println("Running tests");
  /*
  colorFill(strip.Color(255, 0, 0));
  delay(2000);    
  colorFill(strip.Color(0, 255, 0));
  delay(2000);    
  colorFill(strip.Color(0, 0, 255));
  delay(2000);    
  colorFill(strip.Color(255, 255, 255));
  delay(2000);    
  colorFill(strip.Color(0, 0, 0));
    */
}

void checkSerial(){
  static char command[10];
  static int commandIndex = 0;
  
  byte nextByte;  
  
  while (Serial.available() > 0) {
    nextByte = Serial.read();
    if(nextByte == '\n' || nextByte == '.'){
      command[commandIndex] = '\0';
      processCommand(command, commandIndex);
      commandIndex = 0;
    } else {
      command[commandIndex] = nextByte;
      commandIndex++;      
      if(commandIndex > 9) commandIndex = 9;
    }
  }
}

void processCommand(char *command, int length)
{
  uint32_t color = 0;
  static char response[10];
  
  int index = 0;
  int red = 0;
  int green = 0;
  int blue = 0;
        
  //Serial.println(length);
  Serial.print("cmd(");
  Serial.print(length);
  Serial.print("): ");
  Serial.println(command);
  
  switch(command[0]) {
    //TODO: remove johns old ones
    case 'T':
      mode = 1;
      colorFill(strip.Color(0,0,0));
    break;
    case 'H':
      mode = 2;
      colorFill(strip.Color(0,0,0));
    break;
    case 'C':
      mode = 3;
      colorFill(strip.Color(0,0,0));
    break;
    case 'E':
      mode = 4;
      colorFill(strip.Color(0,0,0));
    break;
    case '4':
      mode = 5;
      colorFill(strip.Color(0,0,0));
    break;
    
    case 'p':
      if(length == 1) {
        Serial.println(paused);
      } else if (length == 2) {
        paused = command[1] - '0';
      }
    break;
    
    case 'm': //mode  "m8f"
      if(length == 1) {
        Serial.println(mode);
      } else if (length == 2) {
        mode = atoi('0', command[1]);
      } else if (length == 3) {
        mode = atoi(command[1], command[2]);
      }    
    break;
    case 'd': //demo  "d93"
      if(length == 1) {
        Serial.println(demoMode);
      } else if (length == 2) {
        mode = -1;
        demoMode = atoi('0', command[1]);
      } else if (length == 3) {
        mode = -1;
        demoMode = atoi(command[1], command[2]);
      }    
    break;
    case 'n': //next  "n"
      mode++;
      if(mode > 5) mode = 0;
    break;
    case 'r': //raw   "r01ff00ff"
      if(length == 1) {
        strip.show();
      }
      if(length == 2) {
        command[2] = command[1];
        command[1] = '0';
      }
      
      if(length == 3) {
        index = atoi(command[1], command[2]);
        color = strip.getPixelColor(index);
        sprintf(response, "r%02d%06lX", index, color);
        Serial.println(response);
      } else 
      if (length == 7) {
        red   = ahtoi(command[1], command[2]);
        green = ahtoi(command[3], command[4]);
        blue  = ahtoi(command[5], command[6]);
        
        color = strip.Color(red, green, blue);
        colorWipe(color, 0);
      } else
      if(length == 9) {
        index = atoi(command[1], command[2]);
        red   = ahtoi(command[3], command[4]);
        green = ahtoi(command[5], command[6]);
        blue  = ahtoi(command[7], command[8]);
        
        color = strip.Color(red, green, blue);
        strip.setPixelColor(index, color);
        strip.show(); //TODO: should we separate this?
      }
    break;
    case 't': //run tests
      runTests();
    break;
    
  }
  
}

int atoi(char tensDigit, char onesDigit)
{
  int tens = tensDigit - '0';
  int ones = onesDigit - '0';
  
  return tens*10+ones;
}

int ahtoi(char sixteensDigit, char onesDigit)
{
  if (sixteensDigit >= 'a') sixteensDigit -= 0x20;
  if (onesDigit >= 'a') onesDigit -= 0x20;
  
  //Serial.print(sixteensDigit);
  //Serial.println(onesDigit);

  if (sixteensDigit >= 'A') sixteensDigit -= 7;
  if (onesDigit >= 'A') onesDigit -= 7;
  
  if (sixteensDigit <= '0') sixteensDigit = '0';
  if (onesDigit <= '0') onesDigit = '0';
  
  int sixteens = sixteensDigit - '0';
  int ones = onesDigit - '0';
  
  
  //Serial.println(sixteens*16+ones);
  return sixteens*16+ones;
}
