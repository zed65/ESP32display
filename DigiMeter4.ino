 void DigiMeter4(){
  

  if (screen == 0) {
      screen = (1);
  tft.fillScreen(TFT_BLACK);

  }
  else

  str1 = String(vss);
  str1 = str1 + "     ";
  tft.setTextPadding(tft.textWidth("8888", 4));
  dial.setColorDepth(8);
  dial.createSprite(240, 240);
  dial.fillSprite(TFT_TRANSPARENT);
  kAss3();
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  //delay(10);
 }

void kAss3(){
  dial.setTextColor(TFT_WHITE, TFT_BLACK);
  dial.setFreeFont(FSS18);
  dial.setTextSize(2);
  dial.drawString(str1, 25, 70, FONT7);
  dial.setTextSize(1);
  dial.drawString("km/h", 90, 180, GFXFF);
  }
 
