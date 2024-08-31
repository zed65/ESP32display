 void DutyMeter(){ 
  int val = 0;
  if (screen == 0){
      screen = 1;
      tft.fillScreen(TFT_BLACK);
  }
  else 
  tft.setTextPadding(tft.textWidth("8888", 4));
    
    createDNeedle();
    val = (du);
    int angleMap = map(val, 0, 100, -90, 110);
    angleMap = constrain(angleMap, -90, 110);
    plotDGauge(angleMap);
    delay(10);
    
    }
   
void plotDGauge(int16_t angle){
  createDDial();
  needShort.pushRotated(&dial, angle, TFT_WHITE);
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  }

void createDDial(){
  dial.setColorDepth(8);
  dial.createSprite(240,240);
  dial.setPivot(120,120);
  tft.setPivot(120,120);
  dial.fillSprite(TFT_TRANSPARENT);
  dial.pushImage(0,0,240,170,duty); 
  tft.drawFloat(du,1,70,180,6);
  }

void createDNeedle(){
  needShort.setColorDepth(8);
  needShort.createSprite(81,135);
  needShort.pushImage(0,0,81,135,needleRed1);
  needShort.setPivot(40,94);
  }
