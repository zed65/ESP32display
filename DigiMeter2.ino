 void DigiMeter2(){
  

  if (screen == 0) {
      screen = (1);
  tft.fillScreen(TFT_BLACK);

  }
  else

  str1 = String(vss);
  str1 = str1 + " km/h      ";
  tft.setTextPadding(tft.textWidth("8888", 4));
  dial.setColorDepth(8);
  dial.createSprite(240, 240);
  dial.fillSprite(TFT_TRANSPARENT);
  kAss1();
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  //delay(10);
 }

void kAss1(){
  dial.setTextColor(TFT_YELLOW, TFT_BLACK);
  dial.setFreeFont(FSS18);
  dial.setTextSize(3);
  dial.drawFloat(gear,0,70,10,FONT7);
  dial.setTextColor(TFT_WHITE, TFT_BLACK);
  dial.setFreeFont(FSS18);  
  dial.setTextSize(1);
  dial.drawString(str1, 65, 180, GFXFF);
  
  }
 
 
 
