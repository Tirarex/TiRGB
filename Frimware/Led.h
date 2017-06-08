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

float LigthChSpeedDefault = 0.0005;
float LigthChSpeed;
float LightLerState;



float lerp(float from, float to, float val)
{
  return from + val * (to - from);
}

//Remap rgb 0-255 to Aw 0-1023
int remap (int val) {
  return map(val, 0, 255, 0, 1023);
  //return map(val, 0, 255, 1023, 0); //reversed for - + + + rgb strip
}

int unmap (int val) {
  return map(val, 0, 1023, 0, 255);
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

  if  (LightLerState < 1.0) {
    LightLerState = LightLerState + LigthChSpeed;
  }
  ColorsReal[0] = lerp(ColorsOLD[0], ColorsNew[0], LightLerState);
  ColorsReal[1] = lerp(ColorsOLD[1], ColorsNew[1], LightLerState);
  ColorsReal[2] = lerp(ColorsOLD[2], ColorsNew[2], LightLerState);

  analogWrite(REDPIN, ColorsReal[0]*RedMult);
  analogWrite(GREENPIN, ColorsReal[1]*GreenMult);
  analogWrite(BLUEPIN, ColorsReal[2]*BlueMult);
}


void ColorLeds (int r, int g, int b) {
  analogWrite(REDPIN, remap(r)*RedMult);
  analogWrite(GREENPIN, remap(g)*GreenMult);
  analogWrite(BLUEPIN, remap(b)*BlueMult);
}


void PrepareLed () {
  analogWriteFreq(LedPWMFreq);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  int i;
  for (i = 0; i < ledscount; i = i + 1) {
    pinMode(Leds[i], OUTPUT);
  }
}
