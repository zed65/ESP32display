 void DigiMeter3(){
  
  if (screen == 0) {
      screen = (1);
  tft.fillScreen(TFT_BLACK);

  }
  else
  
  tft.setTextPadding(tft.textWidth("8888", 4));
  dial.setColorDepth(8);
  dial.createSprite(240, 240);
  dial.fillSprite(TFT_TRANSPARENT);
  kAss2();
  dial.pushSprite(0,0,TFT_TRANSPARENT);
  //delay(10);
 }

void kAss2(){

  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  dial.setFreeFont(FSS18);
  dial.drawString("IGN:", 60, 20, GFXFF);
  dial.drawString("EGT1:", 35, 60, GFXFF);
  dial.drawString("EGT2:", 35, 100, GFXFF);
  dial.drawString("DUTY:", 35, 140, GFXFF);
  dial.drawString("O2:", 50, 180, GFXFF);
  dial.drawFloat(ign,0,140,20,GFXFF);
  dial.drawFloat(egt1,0,140,60,GFXFF);
  dial.drawFloat(egt2,0,140,100,GFXFF);
  dial.drawFloat(du,1,140,140,GFXFF);
  dial.drawFloat(afr,2,110,180,GFXFF);
  }
