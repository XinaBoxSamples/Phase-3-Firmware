/*************************************************************
  This is an examples for the SL01 & SN01 running on RTOS
  The sensor communicates over the I2C Bus.
*************************************************************/

uint8_t POPULATE_ID_BUFFER(void) {
  uint8_t buf_idx = 0;
  // Allocate SW01 to buffer
  if (I2C_PING(0x76)) {
    if (c.SW01_ACK) {
      for (uint8_t j = 0; j < sizeof(SW01_ID); j++) {
        if (SW01_ID[j] != NULL) {
          xCHIP_ID[buf_idx] = SW01_ID[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SW01_ACK = 0;
  }
  // Allocate SL01 to buffer
  if ((I2C_PING(0x10) && I2C_PING(0x29)) == true) {
    if (c.SL01_ACK) {
      for (uint8_t j = 0; j < sizeof(SL01_ID); j++) {
        if (SL01_ID[j] != NULL) {
          xCHIP_ID[buf_idx] = SL01_ID[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SL01_ACK = 0;
  }
  // Allocate SI01 to buffer
  if ((I2C_PING(0x1C) && I2C_PING(0x6A)) == true) {
    if (c.SI01_ACK) {
      for (uint8_t j = 0; j < sizeof(SI01_ID); j++) {
        if (SI01_ID[j] != NULL) {
          xCHIP_ID[buf_idx] = SI01_ID[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SI01_ACK = 0;
  }
  // Allocate SN01 to buffer
  if (I2C_PING(0x42)) {
    if (c.SN01_ACK && POLL_SN01()) {
      for (uint8_t j = 0; j < sizeof(SN01_ID); j++) {
        if (SN01_ID[j] != NULL) {
          xCHIP_ID[buf_idx] = SN01_ID[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SN01_ACK = 0;
  }

  // Allocate SW10 MN011 library
      // Allocate SW10 xCHIP to buffer
  if (I2C_PING(0x5A)) {
    if (c.SL19_ACK) {
      for (uint8_t j = 0; j < sizeof(SL19_ID); j++) {
        if (SL19_ID[j] != NULL) {
          xCHIP_ID[buf_idx] = SL19_ID[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SL19_ACK = 0;
  }

  if (I2C_PING(0x49)) {
    if (c.SW10_MN011_ACK) {
      for (uint8_t j = 0; j < sizeof(SW10_ID1); j++) {
        if (SW10_ID1[j] != NULL) {
          xCHIP_ID[buf_idx] = SW10_ID1[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SW10_MN011_ACK = 0;
  }
  // Allocate SW10 MN012 to buffer
  if (I2C_PING(0x48)) {
    if (c.SW10_MN012_ACK) {
      for (uint8_t j = 0; j < sizeof(SW10_ID2); j++) {
        if (SW10_ID2[j] != NULL) {
          xCHIP_ID[buf_idx] = SW10_ID2[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SW10_MN012_ACK = 0;
  }
  // Allocate SW10 SI01 to buffer
  if (I2C_PING(0x4A)) {
    if (c.SW10_CC03_ACK) {
      for (uint8_t j = 0; j < sizeof(SW10_ID3); j++) {
        if (SW10_ID3[j] != NULL) {
          xCHIP_ID[buf_idx] = SW10_ID3[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SW10_CC03_ACK = 0;
  }
  // Allocate SW10 CC03 to buffer
  if (I2C_PING(0x4B)) {
    if (c.SW10_xCHIP_ACK) {
      for (uint8_t j = 0; j < sizeof(SW10_ID4); j++) {
        if (SW10_ID4[j] != NULL) {
          xCHIP_ID[buf_idx] = SW10_ID4[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SW10_xCHIP_ACK = 0;
  }

  // Allocate SW10 xCHIP to buffer
  if (I2C_PING(0x4D)) {
    if (c.SW10_SI01_ACK) {
      for (uint8_t j = 0; j < sizeof(SW10_ID5); j++) {
        if (SW10_ID5[j] != NULL) {
          xCHIP_ID[buf_idx] = SW10_ID5[j];
          buf_idx++;
        }
      }
    }
  } else {
    c.SW10_SI01_ACK = 0;
  }
  
  return buf_idx;
}

