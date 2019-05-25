/*************************************************************
  This is an examples for the SL01 & SN01 running on RTOS
  The sensor communicates over the I2C Bus.
*************************************************************/

/*
   @brief, read incoming data from UART/Serial1.
*/
void READ_UART(void) {
  c.cmd = true;
  c.ts = true;
  if (serial.available() > 2) {
    READ_INPUT();
    if (c.ts) {
      thinsat();
      if (c.OD01_ACK) {
        c.count_request += 1;
        if(c.count_request == 255) {
          c.count_request = 1;
        }
      }
    }
    if (c.cmd) {
      command();
    }
    setLED(LED_BUILTIN, LOW);
  }
}

/*
   @brief, poll connected I2C sensors for data.
*/
void POLL_SENSORS(void) {
  if (c.SW01_ACK) {
    SW01.poll();
    data.tempC = SW01.getTempC();
    data.humidity = SW01.getHumidity();
    data.pressure = SW01.getPressure();
  }
  if (c.SL01_ACK) {
    SL01.poll();
    data.lux = SL01.getLUX();
    data.uva = SL01.getUVA();
    data.uvb = SL01.getUVB();
    data.uvi = SL01.getUVIndex();
  }
  if (c.SI01_ACK) {
    SI01.poll();
    data.accex = SI01.getAX();
    data.accey = SI01.getAY();
    data.accez = SI01.getAZ();
    data.gyrox = SI01.getGX();
    data.gyroy = SI01.getGY();
    data.gyroz = SI01.getGZ();
    data.magx = SI01.getMX();
    data.magy = SI01.getMY();
    data.magz = SI01.getMZ();
    data.roll = SI01.getRoll();
    data.pitch = SI01.getPitch();
    data.yaw = SI01.getYaw();
  }

  if (c.SW10_MN011_ACK) {
    SW10_MN011.poll();
    data.SW10_MN011 = SW10_MN011.getTempC();
  }
  if (c.SW10_MN012_ACK) {
    SW10_MN012.poll();
    data.SW10_MN012 = SW10_MN012.getTempC();
  }
  if (c.SW10_SI01_ACK) {
    SW10_SI01.poll();
    data.SW10_SI01 = SW10_SI01.getTempC();
  }
  if (c.SW10_CC03_ACK) {
    SW10_CC03.poll();
    data.SW10_CC03 = SW10_CC03.getTempC();
  }
  if (c.SW10_xCHIP_ACK) {
    SW10_xCHIP.poll();
    data.SW10_xCHIP = SW10_xCHIP.getTempC();
  }
  if (c.SL19_ACK) {
    SL19.poll();
    data.SL19_ambtemp = SL19.getAmbientTempC();
    data.SL19_objtemp = SL19.getObjectTempC();
  }
}

/*
   @brief, poll SN01 if connected, requires seperate task as it
           needs to be polled often.
*/
bool POLL_SN01(void) {
  bool hdop_flag = false;
  if (c.SN01_ACK) {
    SN01.poll();
    data.altitude = SN01.getAltitude();
    data.latitude = SN01.getLatitude();
    data.longitude = SN01.getLongitude();
    data.hdop = SN01.getHDOP();

    // check for HDOP quality
    if (data.hdop > 6.0) {
      hdop_flag = false;
    } else {
      hdop_flag = true;
    }
  }
  return hdop_flag;
}

void check_sensors(void) {
  // Check OD01
  if (I2C_PING(0x3C)) {
    if (c.OD01_ACK == 0x00) {
      OLED.begin();
      OD01.clear();
      c.OD01_ACK = 0xFF;
    }
  } else {
    c.OD01_ACK = 0;
  }
  // Check SW01
  if (I2C_PING(0x76)) {
    if (c.SW01_ACK == 0x00) {
      SW01.begin();
      c.SW01_ACK = 0xFF;
    }
  } else {
    c.SW01_ACK = 0;
  }
  // Check SL01
  if ((I2C_PING(0x10) && I2C_PING(0x29)) == true) {
    if (c.SL01_ACK == 0x00) {
      SL01.begin();
      c.SL01_ACK = 0xFF;
    }
  } else {
    c.SL01_ACK = 0;
  }
  // Check SI01
  if ((I2C_PING(0x1C) && I2C_PING(0x6A)) == true) {
    if (c.SI01_ACK == 0x00) {
      c.SI01_ACK = 0xFF;
      SI01.begin();
    }
  } else {
    c.SI01_ACK = 0x00;
  }
  // Check SN01
  if (I2C_PING(0x42)) {
    if (c.SN01_ACK == 0x00) {
      c.SN01_ACK = 0xFF;
      SN01.begin();
    }
  } else {
    c.SN01_ACK = 0;
  }

  if (I2C_PING(0x49)) {
    if (c.SW10_MN011_ACK == 0) {
      c.SW10_MN011_ACK = 0xFF;
      //SW10_MN011.begin();
    }
  } else {
    c.SW10_MN011_ACK = 0;
  }

  if (I2C_PING(0x48)) {
    if (c.SW10_MN012_ACK == 0) {
      c.SW10_MN012_ACK = 0xFF;
      //SW10_MN012.begin();
    }
  } else {
    c.SW10_MN012_ACK = 0;
  }
  if (I2C_PING(0x4A)) {
    if (c.SW10_CC03_ACK == 0) {
      c.SW10_CC03_ACK = 0xFF;
      //SW10_SI01.begin();
    }
  } else {
    c.SW10_CC03_ACK = 0;
  }

  if (I2C_PING(0x4B)) {
    if (c.SW10_xCHIP_ACK == 0) {
      c.SW10_xCHIP_ACK = 0xFF;
      //SW10_CC03.begin();
    }
  } else {
    c.SW10_xCHIP_ACK = 0;
  }

  if (I2C_PING(0x4D)) {
    if (c.SW10_SI01_ACK == 0) {
      c.SW10_SI01_ACK = 0xFF;
      //SW10_xCHIP.begin();
    }
  } else {
    c.SW10_SI01_ACK = 0;
  }
  if (I2C_PING(0x5A)) {
    if (c.SL19_ACK == 0) {
      c.SL19_ACK = 0xFF;
    }
  } else {
    c.SL19_ACK = 0;
  }
}


