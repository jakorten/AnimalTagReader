Uart mySerial (&sercom0, 5, 6, SERCOM_RX_PAD_1, UART_TX_PAD_0);
 
// Attach the interrupt handler to the SERCOM
void SERCOM0_Handler()
{
  mySerial.IrqHandler();
}

void initSerial() {
  // Reassign pins 5 and 6 to SERCOM alt
  pinPeripheral(5, PIO_SERCOM_ALT);
  pinPeripheral(6, PIO_SERCOM_ALT);
  
  // Start my new hardware serial
  mySerial.begin(9600);
  Serial.begin(115200);
}

void processSerial() {
  int i = 0;
  while (mySerial.available() > 0) {
    // read the incoming byte:
    incomingByte = mySerial.read();
    tagbuffer[i] = incomingByte;
    i++;
    if (i > 30) {
      Serial.println("Error reading tag.");
      return;
    }
    delay(10); // slow serial so allow some time for the next byte to come in...
  }
  if (i == tagExpectedSize) {
    processTag(tagbuffer);
  } 
}