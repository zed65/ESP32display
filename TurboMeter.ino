 void TurboMeter(){ 
  int val = 0;

  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
  }
  else 
    createNeedle();
    val = (kpa);
    int angleMap = map(val, 0, 220, -110, 130);
    angleMap = constrain(angleMap, -110, 130);
    plotGauge(angleMap);
    //delay(10);
    //yield();
    }
   
void plotGauge(int16_t angle){
  createDial();
  needShort.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  }

void createDial(){
  dial.setColorDepth(8);
  dial.createSprite(240,240);
  dial.setPivot(120,120);
  tft.setPivot(120,120);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.pushImage(0,0,240,240,turbo); 
}

void createNeedle(){
  needShort.setColorDepth(8);
  needShort.createSprite(81,135);
  needShort.pushImage(0,0,81,135,needleRed1);
  needShort.setPivot(40,94);
  }
