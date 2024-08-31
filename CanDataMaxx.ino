
void getCanMaxx(){
//Serial.print("Task1 running on core ");
//Serial.println(xPortGetCoreID());

CAN_frame_t rx_frame;
  unsigned long currentMillis = millis();
  
// Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {
      //yield();
    switch(rx_frame.MsgID) {
      case 0x520:
      rpm = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]);                  //RPM
      tps = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 10;             //TPS
      kpa = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]) / 10;             //MAP
      afr = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]) / 1000.00;        //Wideband Overall
      //Serial.println(rpm);
      //Serial.println(kpa);
      //Serial.println(tps);
      error = 0;
      timer = 3000;
      break;
      case 0x521:
      dummy = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]) / 1000.00;      //Lambda A
      dummy = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 1000.00;      //Lambda B
      ign = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]) / 10.0;           //Ignition angle
      dummy = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]);                //Ign cut
      //Serial.println(fuelp);
      //Serial.println(oilp);
      break;
      case 0x522:
      dummy = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]) / 10.0;         //Pulsewidth
      du = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 10.0;            //Duty cycle
      dummy = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]);                //Fuel cut
      vss = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]) / 10.0;           //VSS
      //Serial.print("DUT: ");
      //Serial.println(du);
      break;
      case 0x524:
      dummy = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]) / 10.0;         //Traction Ctrl Power limit
      corr = ((rx_frame.data.u8[2]) - rx_frame.data.u8[3]) / 10.0;          //Lambda Corr A
      dummy = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]) / 10.0;         //Lambda Corr B
      dummy = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]) / 1000.00;      //Firmware ver
      //Serial.print("Corr: ");
      //Serial.println(corr);
      //Serial.print("  ");
      break;
      case 0x530:
      bat = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]) / 100.0;          //Battery volt
      dummy = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 1000;         //Baro
      val1 = (rx_frame.data.u8[4]);
      val2 = (rx_frame.data.u8[5]);                                               //IAT
      if (val2 >= 250){
        iat = (val1 - ((256 - val2) * 256)) / 10.0;
      }
        else{
          iat = ((val2 * 256) + (val1)) /10.0;
        }
      val1 = (rx_frame.data.u8[6]);
      val2 = (rx_frame.data.u8[7]);                                               //CLT
      if (val2 >= 250){
        clt = (val1 - ((256 - val2) * 256)) / 10.0;
      }
        else{
          clt = ((val2 * 256) + (val1)) /10.0;
        }
      /*Serial.print("Val1: ");
      Serial.print(val1);
      Serial.print("  ");
      Serial.print(val2);
      Serial.print("  ");
      Serial.println(iat); */
      break;
      case 0x531:
      dummy = ((rx_frame.data.u8[1] *256) + rx_frame.data.u8[0]) / 10.0;           //Total Fuel Trim
      flex = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 10.0;          //Flex
      dummy = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]) / 1000;         //Ign comp
      egt1 = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]);                 //EGT #1
      //Serial.print("Corr: ");
      //Serial.print(corr);
      break;
      case 0x532:
      egt2 = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]);                //EGT #2
      dummy = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]);                //EGT #2
      dummy = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]);                //EGT #3
      dummy = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]);                //EGT #4
      //Serial.print("EGT: ");
      //Serial.println(egt);
      break;
      case 0x536:
      gear = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]);                 //Gear
      dummy = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 10.0;         //Boost duty
      dummy = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]) / 10.0;         //Oil pressure
      dummy = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]) / 10.0;         //Oil Temp
      //Serial.print("FuelT: ");
      //Serial.println(fuelt);
      break;
      case 0x537:
      fuelp = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]) / 10.0;         //Fuelpressure1
      dummy = ((rx_frame.data.u8[3] * 256) + rx_frame.data.u8[2]) / 10.0;         //Wategate pressure
      dummy = ((rx_frame.data.u8[5] * 256) + rx_frame.data.u8[4]) / 10.0;         //Coolant pressure
      dummy = ((rx_frame.data.u8[7] * 256) + rx_frame.data.u8[6]) / 10.0;         //Boost target
      //Serial.print("FuelT: ");
      //Serial.println(fuelt);
      break;
      case 0x538:
      fuelt = ((rx_frame.data.u8[1] * 256) + rx_frame.data.u8[0]) / 10.0;         //User1
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]);                //User2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //User3
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //User4
      //Serial.print("Flex: ");
      //Serial.println(flex);
      break;
      /*case 0x3E3:
      corr = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10;            //Fueltrim1
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10;           //Fueltrim2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //Fueltrim3
      dummy = ((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 10;           //Fueltrim4
      //Serial.print("Corr: ");
      //Serial.println(corr);
      break;
      case 0x3E4:
      dummy = (rx_frame.data.u8[0]);
      state1 = (rx_frame.data.u8[1]);                                             //State1
      state2 = (rx_frame.data.u8[2]);                                             //State2
      state3 = (rx_frame.data.u8[3]);                                             //State3
      state4 = (rx_frame.data.u8[7]);                                             //State4
      Serial.print("State1: ");
      Serial.println(state1, BIN);
      Serial.print("State2: ");
      Serial.println(state2, BIN);
      Serial.print("State3: ");
      Serial.println(state3, BIN);
      Serial.print("State4: ");
      Serial.println(state4, BIN);
      break;
      case 0x3E9:
      dummy = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10;           //Generic Sensor 9
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10;           //Generic Sensor 10
      Ltarget = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;       //Target Lambda
      dummy = (rx_frame.data.u8[6]);                                              //Nitous Stage Output
      dummy = (rx_frame.data.u8[7]);                                              //Torque Management Knob
      //Serial.print("Lambda target: ");
      //Serial.println(Ltarget);
      break;
      case 0x470:
      dummy = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 1000;        //Wideband Overall 
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000;         //Wideband Bank 1
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Wideband Bank 2
      dummy = (rx_frame.data.u8[6]);                                              //Gear Selector Position
      gear = (rx_frame.data.u8[7]);                                               //Gear
      //Serial.print("Gear: ");
      //Serial.println(gear);
      break;*/
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
  else {
    error = 0;
  }
}
