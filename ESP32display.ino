//Must use Partition Scheme Minimal SPIFFS or HUGE APP
//Must use Partition Scheme Minimal SPIFFS or HUGE APP
//Must use Partition Scheme Minimal SPIFFS or HUGE APP
//Arduino on core1, Events on core 0

#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include "volt.h"
#include "lambda.h"
#include "speedO.h"
#include "turbo.h"
#include "duty.h"
#include "temp.h"
#include "corr.h"
#include "MercSpeed.h"
#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>
#include "needle.h"
#include "needleshort.h"
#include "needleLong.h"
#include <AnimatedGIF.h>
AnimatedGIF gif;

#include "VolvoLogo.h"
#include "MercLogo.h"
#include "BmwLogo.h"

TaskHandle_t Task1;
TaskHandle_t Task2;


String str1;

CAN_device_t CAN_cfg;               // CAN Config
unsigned long previousMillis = 0;   // will store last time a CAN Message was send
const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size
const int buttonPin = 13;           // 4 on LCD with intergrated ESP32
#define TFT_GREY 0x5AEB
#define GIF_IMAGE Volvo             // Volvo, Merc, Bmw


TFT_eSPI tft = TFT_eSPI();
TFT_eSPI boot = TFT_eSPI();
TFT_eSprite dial = TFT_eSprite(&tft); // Sprite object for dial
TFT_eSprite need = TFT_eSprite(&tft); // Sprite object for needle
TFT_eSprite needShort = TFT_eSprite(&tft); // Sprite object for needleShort
TFT_eSprite needLong = TFT_eSprite(&tft); // Sprite object for needleLong

bool connected = 0, bootscr = 0, i, buttonDown = false, error = 0;
uint16_t x, y;
const int keypressed = LOW;
int userscreen = 10, screen, tps, kpa, vss, gear, buttonState = 0, lastButtonState = 0, dummy, state1, state2, state3, state4, val, dim = 150, timer3 = 50, ecu;
float bat, afr, clt, iat, rpm, fuelp, flex, fuelt, egt1, egt2, oilp, du, ign, corr, Ltarget, val1, val2;
const unsigned long menuDelay = 3000;    // the debounce time; increase if the output flickers
unsigned long buttonPressTime, timer = 3000, timer2 = 5;
String str2, str3;


void setup(){
  //delay(3000);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(19, OUTPUT);
  
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  
  ecu = 0;                              //0 = RusEfi, 1 = MaxxEcu

	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(1);
	tft.setSwapBytes(true); 
  Serial.begin(115200);
	tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);    //true for GC9A01, false for 240x320  //3.5 and 3.2 inch true

  
  //Serial.println("Basic Demo - ESP32-Arduino-CAN");
  CAN_cfg.speed = CAN_SPEED_500KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_22; //var 22
  CAN_cfg.rx_pin_id = GPIO_NUM_21; //var 21
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  
  // Init CAN Module
  ESP32Can.CANInit();

 //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    100000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    500000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}
//Task1code:
void Task1code( void * pvParameters ){
 for(;;){
  if (ecu == 0){
    getCanRus();   
  }
  if (ecu == 1){
    getCanMaxx();
  }
 }
}
//Task2code: 
void Task2code( void * pvParameters ){
   
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

}
void loop(){

if (bootscr == 0) {
  analogWrite(19, 255);
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
bootscr = 1;

  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == keypressed) {
      buttonPressTime = millis();
      buttonDown = true;
      Serial.println("on");
     } else {
      // the button just got released
      buttonDown = false;
      Serial.println("off");
      screen = 0;
      userscreen = userscreen + 1;

      }
  delay(50);
}
 lastButtonState = buttonState;

   if (buttonDown == true && millis() - buttonPressTime >= menuDelay) {
    // we have a long key press
    buttonDown = false; // reset state so button has to be released
          //Serial.print("Rebooting!!");
          //delay(100);
          digitalWrite(12, HIGH);
          }

  
  //alarms();
  if (error == 1){
    timer = timer - 1;
    }
     else{
      timer = 3000;
      screens();
      analogWrite(19, dim);
      
  }
  if (timer <= 1){
    //errorScreen();
    }
    
    //screens();
}
