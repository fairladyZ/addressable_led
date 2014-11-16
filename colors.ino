

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


