/*************************************************************
  This is an examples for the SL01 & SN01 running on RTOS
  The sensor communicates over the I2C Bus.
*************************************************************/

/*
   @brief, start connected sensors if present on I2C BUs
*/

void START_SENSORS(void) {

  // Check OD01
  if (I2C_PING(0x3C)) {
    c.OD01_ACK = 0xFF;
    OLED.begin();
    OD01.clear();
  } else {
    c.OD01_ACK = 0;
  }
  // Check SW01
  if (I2C_PING(0x76)) {
    c.SW01_ACK = 0xFF;
    SW01.begin();
  } else {
    c.SW01_ACK = 0;
  }

  // Check SL01
  if ((I2C_PING(0x10) && I2C_PING(0x29)) == true) {
    c.SL01_ACK = 0xFF;
    SL01.begin();
  } else {
    c.SL01_ACK = 0;
  }

  // Check SI01
  if ((I2C_PING(0x1C) && I2C_PING(0x6A)) == true) {
    c.SI01_ACK = 0xFF;
    SI01.begin();
  } else {
    c.SI01_ACK = 0;
  }

  // Check SN01
  if (I2C_PING(0x42)) {
    c.SN01_ACK = 0xFF;
    SN01.begin();
  } else {
    c.SN01_ACK = 0;
  }

  if (I2C_PING(0x49)) {
    c.SW10_MN011_ACK = 0xFF;
    //SW10_MN011.begin();
  } else {
    c.SW10_MN011_ACK = 0;
  }
  if (I2C_PING(0x48)) {
    c.SW10_MN012_ACK = 0xFF;
    //SW10_MN012.begin();
  } else {
    c.SW10_MN012_ACK = 0;
  }
  if (I2C_PING(0x4A)) {
    c.SW10_CC03_ACK = 0xFF;
    //SW10_SI01.begin();
  } else {
    c.SW10_CC03_ACK = 0;
  }
  if (I2C_PING(0x4B)) {
    c.SW10_xCHIP_ACK = 0xFF;
    //SW10_CC03.begin();
  } else {
    c.SW10_xCHIP_ACK = 0;
  }
  if (I2C_PING(0x4D)) {
    c.SW10_SI01_ACK = 0xFF;
    //SW10_xCHIP.begin();
  } else {
    c.SW10_SI01_ACK = 0;
  }
  if (I2C_PING(0x5A)) {
    c.SL19_ACK = 0xFF;
    //SL19.begin();
  } else {
    c.SL19_ACK = 0;
  }
}




