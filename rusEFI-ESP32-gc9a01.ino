//Must use Partition Scheme Minimal SPIFFS or HUGE APP
//Must use Partition Scheme Minimal SPIFFS or HUGE APP
//Must use Partition Scheme Minimal SPIFFS or HUGE APP
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


TaskHandle_t Task1;
TaskHandle_t Task2;


String str1;

CAN_device_t CAN_cfg;               // CAN Config
unsigned long previousMillis = 0;   // will store last time a CAN Message was send
const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size
const int buttonPin = 13; 
#define TFT_GREY 0x5AEB

#define GIF_IMAGE rusefi

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite dial = TFT_eSprite(&tft); // Sprite object for dial
TFT_eSprite need = TFT_eSprite(&tft); // Sprite object for needle
TFT_eSprite needShort = TFT_eSprite(&tft); // Sprite object for needleShort
//TFT_eSprite digi = TFT_eSprite(&tft); // Sprite object for digi numbers
//TFT_eSprite digi2 = TFT_eSprite(&tft); // Sprite object for vss numbers

bool connected = 0, boot = 0, i;
uint16_t x, y;
int userscreen, screen, tps, kpa, vss, norm = 0, gear, du, buttonState, lastButtonState = LOW, dummy;
float bat, afr, clt, iat, rpm, rpm2, fuelp, flex, fuelt, egt, oilp;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup(){
  pinMode(buttonPin, INPUT_PULLUP);
  
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(0);
	tft.setSwapBytes(true);
  Serial.begin(115200);
	tft.fillScreen(TFT_BLACK);
  userscreen = (norm);
  
  //Serial.println("Basic Demo - ESP32-Arduino-CAN");
  CAN_cfg.speed = CAN_SPEED_500KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_22;
  CAN_cfg.rx_pin_id = GPIO_NUM_21;
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
//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
 for(;;){
  getCan();
 }
}
//Task2code: 
void Task2code( void * pvParameters ){
   
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

}
void loop(){
/*  
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
*/
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
 if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        screen = 0;
        userscreen = userscreen + 1;
        norm = norm + 1;
        }
    }
  }

lastButtonState = reading;
  
  alarms();
  screens();
 


/*

*/

}