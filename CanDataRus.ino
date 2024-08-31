
void getCanRus(){
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
      error = 0;
      timer = 3000;
      break;
      case 0x361:
      fuelp = (((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10) - 101.3; //Fuel pressure
      oilp = (((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10) - 101.3;  //Oil pressure
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //Engine demand
      dummy = (((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 10) - 101.3; //Wastegate pressure
      //Serial.println(fuelp);
      //Serial.println(oilp);
      break;
      case 0x362:
      du = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10.00;           //Duty cycle
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10;           //Duty2
      ign = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10;           //Ignition angle (leading)
      //Serial.print("DUT: ");
      //Serial.println(du);
      break;
      case 0x368:
      afr = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 1000.00;        //Wideband #1
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000.00;      //Wideband #2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000.00;      //Wideband #3
      dummy = ((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 1000.00;      //Wideband #4
      //Serial.print("O2: ");
      //Serial.println(afr);
      break;
      case 0x370:
      vss = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]);         //VSS
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000;         //empty
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Intake cam angle1
      dummy = ((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 1000;         //Intake cam angle2
      //Serial.print("VSS: ");
      //Serial.println(vss);
      break;
      case 0x372:
      bat = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10.00;         //Battery
      dummy = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 1000;         //empty
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 1000;         //Target Boost
      dummy = ((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 1000;         //Baro
      //Serial.print("BAT: ");
      //Serial.println(bat);
      break;
      case 0x373:
      egt1 = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10 - 273;        //EGT #1
      egt2 = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10 - 273;        //EGT #2
      dummy = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10 - 273;       //EGT #3
      dummy = ((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 10 - 273;       //EGT #4
      //Serial.print("EGT: ");
      //Serial.println(egt);
      break;
      case 0x3E0:
      clt = ((rx_frame.data.u8[0] * 256) + rx_frame.data.u8[1]) / 10 - 273;       //CLT
      iat = ((rx_frame.data.u8[2] * 256) + rx_frame.data.u8[3]) / 10 - 273;       //IAT
      fuelt = ((rx_frame.data.u8[4] * 256) + rx_frame.data.u8[5]) / 10 - 273;     //Fuel temp
      dummy = ((rx_frame.data.u8[6] * 256) + rx_frame.data.u8[7]) / 1000;         //Oil temp
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
      case 0x3E3:
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
      /*Serial.print("State1: ");
      Serial.println(state1, BIN);
      Serial.print("State2: ");
      Serial.println(state2, BIN);
      Serial.print("State3: ");
      Serial.println(state3, BIN);
      Serial.print("State4: ");
      Serial.println(state4, BIN);*/
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
  else {
    error = 1;
  }
}
