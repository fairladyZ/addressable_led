
//TODO: convert this over to separated
//uint32_t blankColor = strip.Color(0,0,0);

uint32_t stripColorFromColor(int* color){
  return strip.Color(color[0], color[1], color[2]);
}

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

