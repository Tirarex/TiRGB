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
float FadeCLR[3];


//Store color
float ColorsReal[3];
float ColorsNew[3];
float ColorsOLD[3];

float LigthChSpeedDefault = 0.005;
float LigthChSpeed;
float LightLerState;



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
  TiMode = tmode;
  ColorsNew[col] = remap(val);
  LightLerState = 0;
  ColorsOLD[0] = ColorsReal[0];
  ColorsOLD[1] = ColorsReal[1];
  ColorsOLD[2] = ColorsReal[2];
  if (tmode < 1) {
    LigthChSpeed = LigthChSpeedDefault;
  }
}

void ApplyColor() {

  if  (LightLerState < 0.99) {
    LightLerState = LightLerState + LigthChSpeed;
  }
  ColorsReal[0] = lerp(ColorsOLD[0], ColorsNew[0], LightLerState);
  ColorsReal[1] = lerp(ColorsOLD[1], ColorsNew[1], LightLerState);
  ColorsReal[2] = lerp(ColorsOLD[2], ColorsNew[2], LightLerState);

  pwm.setPWM(1, 0, ( ColorsReal[0]));
  pwm.setPWM(2, 0, ( ColorsReal[1]));
  pwm.setPWM(0, 0, ( ColorsReal[2]));
}


void ColorLeds (int r, int g, int b) {
  pwm.setPWM(0, 0, remap(b));
  pwm.setPWM(1, 0, remap(r));
  pwm.setPWM(2, 0, remap(g));


}



void PrepareLed () {

  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
  
  int i;
  for (i = 0; i < ledscount; i = i + 1) {
    pinMode(Leds[i], OUTPUT);
  }
}
