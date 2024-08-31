 void MercSpeed(){ 
  int val = 0;

  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
  }
  else 
    createMSNeedle();
    val = (afr * 100);
    int angleMap = map(val, 20, 260, -180, 180);
    angleMap = constrain(angleMap, -180, 180);
    plotMSGauge(angleMap);
    //delay(10);
    //yield();
    }
   
void plotMSGauge(int16_t angle){
  createMSDial();
  needLong.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(40,0,TFT_TRANSPARENT);
  }

void createMSDial(){
  dial.setColorDepth(8);
  dial.createSprite(340,309);
  dial.setPivot(170,170);
  tft.setPivot(170,170);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.pushImage(0,0,340,309,Mspeed); 
}

void createMSNeedle(){
  needLong.setColorDepth(8);
  needLong.createSprite(37,160);
  needLong.pushImage(0,0,37,160,needleLong2);
  needLong.setPivot(18,141);
  }
