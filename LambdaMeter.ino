 void LambdaMeter(){ 
  int val = 0;
  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
  }
  else 
  tft.setTextPadding(tft.textWidth("8888", 4));
    createLNeedle();
    val = (afr * 100);
    int angleMap = map(val, 70, 130, -90, 90);
    angleMap = constrain(angleMap, -90, 90);
    plotLGauge(angleMap);
    delay(10);
    yield();
    }
   
void plotLGauge(int16_t angle){
  createLDial();
  needShort.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  }

void createLDial(){
  dial.setColorDepth(8);
  dial.createSprite(240,240);
  dial.setPivot(120,120);
  tft.setPivot(120,120);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.drawFloat(afr,2,70,180,6);
  dial.pushImage(0,0,240,170,lambda); 
  
}

void createLNeedle(){
  needShort.setColorDepth(8);
  needShort.createSprite(81,135);
  needShort.pushImage(0,0,81,135,needleRed1);
  needShort.setPivot(40,94);
  }
