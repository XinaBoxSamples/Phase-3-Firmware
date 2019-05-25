/*************************************************************
  This is an examples for the SL01 & SN01 running on RTOS
  The sensor communicates over the I2C Bus.
*************************************************************/

/*
   @brief, data to be sent to ThinSAT CPU
*/
void send_data() {
  uint8_t pop_buffer = POPULATE_ID_BUFFER();
  ptr = &data;
  uint8_t ID[pop_buffer];
  for (int k = 0; k < pop_buffer; k++) {
    ID[k] = xCHIP_ID[k];
  }
  if (c.last_id_flag) {
    c.ptr_id = ID;
    c.count = 0;
    c.last_id_flag = false;
  }
  for (i = 0; i < DATABUFSIZE; i++) {
    data_buf[i] = *c.ptr_id;
    // //OD01 prints for testing purposes
    switch (*c.ptr_id) { // pointer to IDs
      case 1:
        unsig_byte_data(ptr->tempC);
        //OD01.print(byte(((5 * data_buf[i]) / 8) - 40));
        //OD01.print(",");
        break;
      case 2:
        unsig_byte_data(ptr->humidity);
        //OD01.print(byte((data_buf[i]) / 2));
        //OD01.print(",");
        break;
      case 3:
        convert_unsig_data(ptr->pressure);
        //OD01.println(float((8 * (float((data_buf[i] << 8) | data_buf[i - 1])) / 100) + 30));
        break;
      case 4:
        convert_unsig_data(ptr->lux);
        SERIAL.println("****SL01****");
        SERIAL.print(" 4. Lux : ");
        SERIAL.println(uint16_t(uint16_t((data_buf[i] << 8) | data_buf[i - 1])) * 4);
        break;
      case 5:
        convert_unsig_data(ptr->uva);
        SERIAL.print(" 5. UVA : ");
        SERIAL.println((uint16_t)(data_buf[i] << 8) | data_buf[i - 1]);
        break;
      case 6:
        convert_unsig_data(ptr->uvb);
        SERIAL.print(" 6. UVB : ");
        SERIAL.println((uint16_t)(data_buf[i] << 8) | data_buf[i - 1]);
        break;
      case 7:
        unsig_byte_data(ptr->uvi);
        //OD01.println(uint8_t(data_buf[i]));
        break;
      case 8:
        convert_sig_data(ptr->accex);
        SERIAL.println("****SI01****");
        SERIAL.print(" 8. Accelx : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.000061));
        break;
      case 9:
        convert_sig_data(ptr->accey);
        SERIAL.print(" 9. Accely : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.000061));
        break;
      case 10:
        convert_sig_data(ptr->accez);
        SERIAL.print("10. Accelz : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.000141));
        break;
      case 11:
        convert_sig_data(ptr->gyrox);
        SERIAL.print("11. Gyrox  : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.00014));
        break;
      case 12:
        convert_sig_data(ptr->gyroy);
        //OD01.print(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.000141));
        //OD01.print(",");
        break;
      case 13:
        convert_sig_data(ptr->gyroz);
        SERIAL.print("13. Gyroz  : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.00014));
        break;
      case 14:
        convert_sig_data(ptr->magx);
        SERIAL.print("14. Magx   : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.00875));
        break;
      case 15:
        convert_sig_data(ptr->magy);
        SERIAL.print("15. Magy   : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.00875));
        break;
      case 16:
        convert_sig_data(ptr->magz);
        SERIAL.print("16. Magz   : ");
        SERIAL.println(float(float((data_buf[i] << 8) | data_buf[i - 1]) * 0.00875));
        break;
      case 17:
        sig_byte_data(ptr->roll);
        SERIAL.print("17. Roll  : ");
        SERIAL.println((int8_t)data_buf[i]);
        break;
      case 18:
        sig_byte_data(ptr->pitch);
        SERIAL.print("18. Pitch : ");
        SERIAL.println((int8_t)data_buf[i]);
        break;
      case 19:
        sig_byte_data(ptr->yaw);
        SERIAL.print("19. Yaw   : ");
        SERIAL.println((int8_t)data_buf[i]);
        break;
      case 20:
        convert_sig_data(ptr->altitude);
        //OD01.print(float(float((data_buf[i] << 8) | data_buf[i - 1])));
        //OD01.print(",");
        break;
      case 21:
        convert_sig32_data(ptr->latitude);
        //OD01.print((float)((data_buf[i - 3] << 24) | (data_buf[i - 2] << 16) | (data_buf[i - 1] << 8) | (data_buf[i])) / 10000000);
        //OD01.print(",");
        break;
      case 22:
        convert_sig32_data(ptr->longitude);
        //OD01.println((float)((data_buf[i - 3] << 24) | (data_buf[i - 2] << 16) | (data_buf[i - 1] << 8) | (data_buf[i])) / 10000000);
        break;

      case 28:
        sig_byte_data(ptr->SL19_ambtemp);
        break;
      case 29:
        convert_unsig_data(ptr->SL19_objtemp);
        SERIAL.println("****SL19****");
        SERIAL.print("29. Temp : ");
        SERIAL.println((float)((data_buf[i] << 8) |( data_buf[i - 1]))/50.00 - 70);
        break;
      case 32:
        unsig_byte_data(ptr->SW10_MN011);
        SERIAL.println("****SW10****");
        SERIAL.print("32. Temp : ");
        SERIAL.println((0.9 * (float)data_buf[i]) - 55);
        break;
      case 33:
        unsig_byte_data(ptr->SW10_MN012);
        SERIAL.print("33. Temp : ");
        SERIAL.println((0.9 * (float)data_buf[i]) - 55);
        break;
      case 34:
        unsig_byte_data(ptr->SW10_CC03);
        SERIAL.print("34. Temp : ");
        SERIAL.println((0.9 * (float)data_buf[i]) - 55);
        break;
      case 35:
        unsig_byte_data(ptr->SW10_xCHIP);
        SERIAL.print("35. Temp : ");
        SERIAL.println((0.9 * (float)data_buf[i]) - 55);
        break;
      case 36:
        unsig_byte_data(ptr->SW10_SI01);
        SERIAL.print("36. Temp : ");
        SERIAL.println((0.9 * (float)data_buf[i]) - 55);
        break;
      default:
        break;
    }
    c.ptr_id++; // pointer arithmetic to cycle through selected IDs

    // test whether final ID has been reached
    if (ID[sizeof(ID)] == *c.ptr_id) {
      c.last_id_flag = true;
      // populate the rest of the data buffer with 0x00
      for (i; i < DATABUFSIZE;) {
        data_buf[++i] = 0x00;
      }
      c.ptr_id = ID; // restart pointer arithmetic cycling
    }
  }
  if (ID == NULL) {
    c.count = 0;
  } else {
    c.count += 1;
  }

  // populate preamble and sequence count
  pre_buf[0] = 0x50;
  pre_buf[1] = 0x50;
  pre_buf[2] = 0x50;
  pre_buf[3] = c.count;

  // send pre_buf over uart
  for (int k = 0; k < PREBUFSIZE; k++) {
    serial.print(pre_buf[k]);
  }
  // send data_buf over uart
  for (int k = 0; k < DATABUFSIZE; k++) {
    serial.print(data_buf[k]);
  }

  //SERIAL.println();
  // clear buffers
  memset(data_buf, '0', DATABUFSIZE);
  memset(pre_buf, '0', PREBUFSIZE);
  memset(ID, '0', sizeof(ID));

  // store sequence count in flash
  count_store.write(c.count);
  last_id_flag_store.write(c.last_id_flag);
  id_store.write(c.ptr_id);
}


