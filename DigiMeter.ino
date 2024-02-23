 void DigiMeter(){
  

  if (screen == 0) {
      screen = (1);
  tft.fillScreen(TFT_BLACK);

  }
  else
  digi.setTextPadding(tft.textWidth("8888", 4));
  digi.setColorDepth(8);
  digi.createSprite(240, 240);
  digi.fillSprite(TFT_TRANSPARENT);
  kAss();
  digi.pushSprite(0,0,TFT_TRANSPARENT);
  delay(10);
 }

void kAss(){
  digi.setTextColor(TFT_WHITE, TFT_BLACK);
  digi.setFreeFont(FSS18);
  digi.drawString("IAT:", 60, 20, GFXFF);
  digi.drawString("FuelT:", 30, 60, GFXFF);
  digi.drawString("FuelP:", 30, 100, GFXFF);
  digi.drawString("Flex%:", 30, 140, GFXFF);
  digi.drawString("CLT:", 55, 180, GFXFF);
  digi.drawFloat(iat,0,140,20,GFXFF);
  digi.drawFloat(fuelt,0,140,60,GFXFF);
  digi.drawFloat(fuelp,0,140,100,GFXFF);
  digi.drawFloat(flex,0,140,140,GFXFF);
  digi.drawFloat(clt,0,140,180,GFXFF);
  }
 
 
 
