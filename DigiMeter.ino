 void DigiMeter(){
  
  str2 = String(iat, 0) + "     "; 
  str3 = String(clt, 0) + "     ";

  if (screen == 0) {
      screen = (1);
  tft.fillScreen(TFT_BLACK);

  }
  else
  tft.setTextPadding(tft.textWidth("8888", 4));
  dial.setColorDepth(8);
  dial.createSprite(240, 240);
  dial.fillSprite(TFT_TRANSPARENT);
  kAss();
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  //delay(10);
 }

void kAss(){


  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  dial.setFreeFont(FSS18);
  dial.setTextSize(1);
  dial.drawString("IAT:", 60, 20, GFXFF);
  dial.drawString("FuelT:", 30, 60, GFXFF);
  dial.drawString("FuelP:", 30, 100, GFXFF);
  dial.drawString("Flex%:", 30, 140, GFXFF);
  dial.drawString("CLT:", 55, 180, GFXFF);
  dial.drawString(str2,140,20,GFXFF);
  dial.drawFloat(fuelt,0,140,60,GFXFF);
  dial.drawFloat(fuelp,0,140,100,GFXFF);
  dial.drawFloat(flex,0,140,140,GFXFF);
  dial.drawString(str3,140,180,GFXFF);
  }
 
 
 
