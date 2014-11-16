

//these are separated for transistions
int blankColor[]  = {0,0,0};
int whiteColor[]  = {255, 255, 255};

int lightTealColor[] = {0, 150, 200};
int tealColor[]   = {0, 255, 255};
int purpleColor[] = {80, 0, 255};
int orangeColor[] = {255, 50, 0};

int redColor[]    = {255, 0, 0};
int greenColor[]  = {0, 255, 0};
int blueColor[]   = {0, 0, 255};

//still need tweaking
int magentaColor[] = {255, 0, 255};
int yellowColor[] = {255, 224, 0};


//helper functions
uint32_t stripColorFromColor(int* color){
  return strip.Color(color[0], color[1], color[2]);
}


uint32_t getColorBlend(int* color1, int* color2, int percent){
  if (percent > 100) percent = 200 - percent;
  
  int diffR = color2[0] - color1[0];
  int diffG = color2[1] - color1[1];
  int diffB = color2[2] - color1[2];
  
  diffR = (diffR * percent) / 100;
  diffG = (diffG * percent) / 100;
  diffB = (diffB * percent) / 100;

  return strip.Color(color1[0] + diffR, color1[1] + diffG, color1[2] + diffB);
}

