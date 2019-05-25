void DEBUG_OD01(void) {
  OD01.clear();
  OD01.println("    DEBUG PHASE 3");
  OD01.println("=======================");
  if (c.SL19_ACK) {
    OD01.print("SL19 Temp: ");
    OD01.print((float)(data.SL19_objtemp / 50.00) - 70);
    OD01.println(" C");
  } else {
    OD01.println("SL19 N/A");
  }
  if (c.SL01_ACK) {
    OD01.print("SL01 Lux : ");
    OD01.println((uint16_t)data.lux * 4);
  } else {
    OD01.println("SL01 N/A");
  }
  if (c.SW10_xCHIP_ACK) {
    OD01.print("SW10 Temp: ");
    OD01.print((0.9 * (float)data.SW10_xCHIP) - 55);
    OD01.println(" C");
  } else {
    OD01.println("SW10 N/A");
  }
  if (c.SI01_ACK) {
    OD01.print("SI01 Roll: ");
    OD01.print(data.roll);
    OD01.println(" degrees");
  } else {
    OD01.println("SI01 N/A");
  }

  if (c.count_request == 1) {
    OD01.println("Payload Packet Sent");
    OD01.print("Verifying...");
  } else if (c.count_request > 1) {
    OD01.println("Data Transmitted");
    OD01.print("EM PASS");
  } else {
    OD01.println("Awaiting request");
    OD01.print("from EM....");
  }
}


