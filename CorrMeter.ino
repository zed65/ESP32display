 void CorrMeter(){ 
  int val = 0;
  str2 = String(corr, 1) + "     ";
  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
  }
  else 
  tft.setTextPadding(tft.textWidth("8888", 4));
    dial.setTextColor(TFT_WHITE, TFT_BLACK);
    createCoNeedle();
    val = (corr * 10);
    int angleMap = map(val, -200, 200, -90, 90);
    angleMap = constrain(angleMap, -90, 90);
    plotCoGauge(angleMap);
    delay(10);
    //yield();
    }
   
void plotCoGauge(int16_t angle){
  createCoDial();
  needShort.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  }

void createCoDial(){
  dial.setColorDepth(8);
  dial.createSprite(240,240);
  dial.setPivot(120,120);
  tft.setPivot(120,120);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.drawString(str2,70,180,6);
  dial.pushImage(0,0,240,170,corr1); 
  
}

void createCoNeedle(){
  needShort.setColorDepth(8);
  needShort.createSprite(81,135);
  needShort.pushImage(0,0,81,135,needleRed1);
  needShort.setPivot(40,94);
  }
