 void TempMeter(){ 
  int val = 0;
  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
      
  }
  else 

    createCNeedle();
    val = (clt);
    int angleMap = map(val, -10, 120, -43, 43);
    angleMap = constrain(angleMap, -43, 43);
    plotCGauge(angleMap);
    delay(10);
    
    }
   
void plotCGauge(int16_t angle){
  createCDial();
  need.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  }

void createCDial(){
  dial.setColorDepth(8);
  dial.createSprite(240,240);
  dial.setPivot(120,180);
  tft.setPivot(120,120);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.pushImage(0,0,240,170,temp);
}

void createCNeedle(){
  need.setColorDepth(8);
  need.createSprite(81,182);
  need.pushImage(0,0,81,182,needleRed);
  need.setPivot(40,139);
  }
