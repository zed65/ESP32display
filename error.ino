void errorScreen(){
  if (timer2 >= 6){
    timer2 = 5;
  }
//tft.fillScreen(TFT_GREY);
tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(3);
tft.setCursor(40, 50, 2);
tft.println("canError");
tft.setCursor(30, 100, 2);
tft.println("Rebooting");
tft.setCursor(50, 150, 2);
tft.print("In: ");
tft.print(timer2);
tft.println("  ");
//Serial.println("Error");
  timer2 = timer2 - 1;
  timer = 3000;
  delay(500);
  if (timer2 < 1){
    //Serial.print("Rebooting!!");
    //digitalWrite(12, HIGH);
    
    delay(50);
  }
}
