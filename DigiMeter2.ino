 void DigiMeter2(){
  

  if (screen == 0) {
      screen = (1);
  tft.fillScreen(TFT_BLACK);

  }
  else

  str1 = String(vss);
  str1 = str1 + " km/h      ";
  digi.setTextPadding(tft.textWidth("8888", 4));
  digi.setColorDepth(8);
  digi.createSprite(240, 240);
  digi.fillSprite(TFT_TRANSPARENT);
  kAss1();
  digi.pushSprite(0,0,TFT_TRANSPARENT);
  delay(10);
 }

void kAss1(){
  digi.setTextColor(TFT_YELLOW, TFT_BLACK);
  digi.setFreeFont(FSS18);
  digi.setTextSize(3);
  digi.drawFloat(gear,0,70,10,FONT7);
  digi.setTextSize(1);
  digi.drawString(str1, 65, 180, GFXFF);
  }
 
 
 
