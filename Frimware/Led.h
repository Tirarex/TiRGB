//Modes

//0-JustLit
//1-flow
//2-blink
//3-fade
//4-Music
//5-reserved
//Flow
int FlowStage;
int TiMode;
#define WAIT_RAINBOW 10000
int rainbowDelay = 10000;



//fade
float FadeCLR[16];
//Store color
float ColorsReal[16];
float ColorsNew[16];
float ColorsOLD[16];

float LigthChSpeedDefault = 0.005;
float LigthChSpeed;
float LightLerState[16];



float lerp(float from, float to, float val)
{
  return from + val * (to - from);
}

//Remap rgb 0-255 to Aw 0-1023
int remap (int val) {
  return map(val, 0, 255, 0, 4094);
  //return map(val, 0, 255, 1023, 0); //reversed for - + + + rgb strip
}

int unmap (int val) {
  return map(val, 0, 4094, 0, 255);
  //return map(val, 0, 255, 1023, 0); //reversed for - + + + rgb strip
}


void Ccolor(int col, int val, int tmode) {
  LightLerState[col] = 0;
  ColorsOLD[col] = ColorsReal[col];
  ColorsNew[col] = val;
  LigthChSpeed = LigthChSpeedDefault;
  if (tmode < 1) {
    LigthChSpeed = LigthChSpeedDefault;
  }
}

void ApplyColor() {
  int i;
  for (i = 0; i < UsedCH; i = i + 1) {
    if  (LightLerState[i] < 1.0) {
      LightLerState[i] = LightLerState[i] + LigthChSpeed;
    }
    if  (LightLerState[i] > 1.0) {
      LightLerState[i] = 1;
    }
    ColorsReal[i] = lerp(ColorsOLD[i], ColorsNew[i], LightLerState[i]);
  }
}

void ColorLeds (int r, int g, int b) {
  pwm.setPWM(0, 0, remap(b));
  pwm.setPWM(1, 0, remap(r));
  pwm.setPWM(2, 0, remap(g));
}

void FillChannels () {
  int i;
  for (i = 0; i < UsedCH; i = i + 1) {
    pwm.setPWM(i, 0, ( ColorsReal[i]));
  }
}

void PrepareLed () {
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
}
