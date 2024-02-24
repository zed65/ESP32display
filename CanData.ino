
void getCan(){
//Serial.print("Task1 running on core ");
//Serial.println(xPortGetCoreID());

CAN_frame_t rx_frame;
  unsigned long currentMillis = millis();

// Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {
      //yield();
    switch(rx_frame.MsgID) {
      case 0x360:
      rpm = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]);                  //RPM
      kpa = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10;             //MAP
      tps = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;             //TPS
      dummy = (((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 10) - 101.3; //Coolant pressure
      //Serial.println(rpm);
      //Serial.println(kpa);
      //Serial.println(tps);
      break;
      case 0x361:
      fuelp = (((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10) - 101.3;//Fuel pressure
      oilp = (((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10) - 101.3; //Oil pressure
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //Engine demand
      dummy = (((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 10) - 101.3; //Wastegate pressure
      //Serial.println(fuelp);
      break;
      case 0x362:
      du = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10.0;              //Duty cycle
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10;           //Duty2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //Ignition angle (leading)
      //Serial.print("DUT: ");
      //Serial.println(du);
      break;
      case 0x368:
      afr = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 1000.00;         //Wideband #1
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000.00;       //Wideband #2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000.00;       //Wideband #3
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000.00;       //Wideband #4
      //Serial.print("AFR: ");
      //Serial.println(afr);
      break;
      case 0x370:
      vss = (((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10.0);           //VSS
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000;         //empty
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Intake cam angle1
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Intake cam angle2
      Serial.print("VSS: ");
      Serial.println(vss);
      break;
      case 0x372:
      bat = ((rx_frame.data.u8[0] * 256) + (rx_frame.data.u8[1] / 10.0));         //Battery
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000;         //empty
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Target Boost
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Baro
      //Serial.print("BAT: ");
      //Serial.println(bat);
      break;
      case 0x373:
      egt = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10 - 273;       //EGT #1
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000;         //EGT #2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //EGT #3
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //EGT #4
      //Serial.print("EGT: ");
      //Serial.println(egt);
      break;
      case 0x3E0:
      clt = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10 - 273;       //CLT
      iat = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10 - 273;       //IAT
      fuelt = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10 - 273;     //Fuel temp
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Oil temp
      //Serial.print("FuelT: ");
      //Serial.println(fuelt);
      break;
      case 0x3E1:
      dummy = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]);                //Gearbox temp
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]);                //Diff temp
      flex = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;            //Flex%
      //Serial.print("Flex: ");
      //Serial.println(flex);
      break;
  }
    // Send CAN Message
  if (currentMillis - previousMillis >= interval) {
   previousMillis = currentMillis;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = 0x001;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0x00;
    tx_frame.data.u8[1] = 0x01;
    tx_frame.data.u8[2] = 0x02;
    tx_frame.data.u8[3] = 0x03;
    tx_frame.data.u8[4] = 0x04;
    tx_frame.data.u8[5] = 0x05;
    tx_frame.data.u8[6] = 0x06;
    tx_frame.data.u8[7] = 0x07;
    ESP32Can.CANWriteFrame(&tx_frame);
  
  }

  }
 
}