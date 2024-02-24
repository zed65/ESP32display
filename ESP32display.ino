//Must use Partition Scheme Minimal SPIFFS or HUGE APP with BIG bootscreens
//Must use Partition Scheme Minimal SPIFFS or HUGE APP with BIG bootscreens
//Must use Partition Scheme Minimal SPIFFS or HUGE APP with BIG bootscreens

#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include "volt.h"
#include "lambda.h"
#include "turbo.h"
#include "duty.h"
#include "temp.h"
#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>
#include "needle.h"
#include "needleshort.h"
#include <AnimatedGIF.h>
AnimatedGIF gif;
#include "rusefi.h"

String str1;

CAN_device_t CAN_cfg;               // CAN Config
unsigned long previousMillis = 0;   // will store last time a CAN Message was send
const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size
const int buttonPin = 13;           // Screenselector button on PIN13

#define TFT_GREY 0x5AEB
#define GIF_IMAGE rusefi

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite dial = TFT_eSprite(&tft); // Sprite object for dial
TFT_eSprite need = TFT_eSprite(&tft); // Sprite object for needle
TFT_eSprite needShort = TFT_eSprite(&tft); // Sprite object for needleShort
TFT_eSprite digi = TFT_eSprite(&tft); // Sprite object for digi numbers
TFT_eSprite digi2 = TFT_eSprite(&tft); // Sprite object for vss numbers

bool connected = 0, mainFilled = 0, boot = 0;
uint16_t x, y;
int userscreen, screen, tps, kpa, vss, norm = 0, gear, du, buttonState, lastButtonState = LOW, ledState = HIGH, dummy;
float bat, afr, clt, iat, egt, rpm, rpm2, fuelp, flex, fuelt, oilp;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup(){
  pinMode(buttonPin, INPUT_PULLUP);
  
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(1);
	tft.setSwapBytes(true);
  Serial.begin(115200);
	tft.fillScreen(TFT_BLACK);
  userscreen = (norm);

  CAN_cfg.speed = CAN_SPEED_500KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_22;
  CAN_cfg.rx_pin_id = GPIO_NUM_21;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  
  ESP32Can.CANInit(); // Init CAN Module

}

void loop(){

// Screen selector button

int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
 if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the state if the new button state is HIGH
      if (buttonState == LOW) {
        screen = 0;
        userscreen = userscreen + 1;
        norm = norm + 1;
        ledState = !ledState;
      }
    }
  }

lastButtonState = reading;

// Bootscreen

if (boot == 0) {

  if (gif.open((uint8_t *)GIF_IMAGE, sizeof(GIF_IMAGE), GIFDraw))
  {
    tft.startWrite();
    while (gif.playFrame(true, NULL))
    {
      yield();
    }
    gif.close();
    tft.endWrite(); 
  }

  tft.fillScreen(TFT_BLACK);
 
}
boot = 1;

  getCan();
  
 //Alarms!!
 
  if ((bat <= 12) && (rpm >=600)){
     userscreen = 3;} 
  if ((afr >=1.0) && (kpa > 110)){
     userscreen = 0;}
  if (clt >= 100){
     userscreen = 2;}
  if (du >= 90){
     userscreen = 1;
   } 

 //Screens

  if (userscreen > 6){
    userscreen = 0;}
 
  if (userscreen == 0){
      LambdaMeter();
      screen = 1;}
    else if (userscreen == 1){
      DutyMeter();
      screen = 1;}
    else if (userscreen == 2){
      TempMeter();
      screen = 1;}
		else if (userscreen == 3){
      VoltMeter();      
      screen = 1;}
		else if (userscreen == 4){
      TurboMeter();
      screen = 1;}
    else if (userscreen == 5){
      DigiMeter();
      screen = 1;}
    else if (userscreen == 6){
      DigiMeter2();
      screen = 1;}
     yield();

}