/*************************************************************
  This is an examples for the SL01 & SN01 running on RTOS
  The sensor communicates over the I2C Bus.
*************************************************************/
/*
   @brief, set up the task priorities

     long  tick_poll;
  long  tick_UART;
  long  tick_BUFFER;
  long  tick_SN01;

*/

void TaskScheduler(void) {
  if ((c.SL01_ACK & c.SI01_ACK & c.SW10_MN011_ACK & c.SW10_MN012_ACK & c.SW10_SI01_ACK & c.SW10_CC03_ACK & c.SW10_xCHIP_ACK & c.SL19_ACK) == 0) {
    if ((millis() - t.tick_LED) > 500) {
      digitalWrite(LED_BUILTIN, (state) ? HIGH : LOW);
      state = !state;
      t.tick_LED = millis();
    } 
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if ((millis() - t.tick_UART) > 100) { // 100ms
    READ_UART();
    t.tick_UART = millis();
  }
  if ((millis() - t.tick_SN01) > 100) { // 100ms
    POLL_SN01();
    t.tick_SN01 = millis();
  }

  if ((millis() - t.tick_POLL) > 250) { // 250ms
    POLL_SENSORS();
    t.tick_POLL = millis();
  }

  if ((millis() - t.tick_status) > 300) { // 300ms
    check_sensors();
    t.tick_status = millis();
  }
  if (c.OD01_ACK) {
    if ((millis() - t.tick_OLED) > 2000) { // 1000ms
      DEBUG_OD01();
      t.tick_OLED = millis();
    }
  }
}

