 void VoltMeter(){ 
  int val = 0;
  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
  }
  else 
  
    createVNeedle();
    val = (bat);
    int angleMap = map(val, 10, 16, -43, 43);
    angleMap = constrain(angleMap, -43, 43);
    plotVGauge(angleMap);
    delay(10);
    
    }
   
void plotVGauge(int16_t angle){
  createVDial();
  need.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  }

void createVDial(){
  dial.setColorDepth(8);
  dial.createSprite(240,240);
  dial.setPivot(120,180);
  tft.setPivot(120,120);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.pushImage(0,0,240,240,volt);
}

void createVNeedle(){
  need.setColorDepth(8);
  need.createSprite(81,182);
  need.pushImage(0,0,81,182,needleRed);
  need.setPivot(40,139);
  }
