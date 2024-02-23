
void getCan(){

CAN_frame_t rx_frame;
  unsigned long currentMillis = millis();

// Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {
      yield();
    switch(rx_frame.MsgID) {
      case 1536:
      bat = (rx_frame.data.u8[0] + rx_frame.data.u8[1] / 256.00);
      afr = (rx_frame.data.u8[2] + rx_frame.data.u8[3] / 256.00);
      kpa = (rx_frame.data.u8[4]);
      clt = (rx_frame.data.u8[5]) - 100;
      du = (rx_frame.data.u8[6]);
      
      break;
      case 1537:
      rpm = (rx_frame.data.u8[1] + rx_frame.data.u8[0] * 256);
      iat = (rx_frame.data.u8[2]) - 100;
      fuelp = (rx_frame.data.u8[3]);
      flex = (rx_frame.data.u8[4]);
      fuelt = (rx_frame.data.u8[5]);
      vss = (rx_frame.data.u8[6]);
      gear = (rx_frame.data.u8[7]);
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
