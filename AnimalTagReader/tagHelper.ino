  /*
  See: https://allinbest.com/blog/1342k-animal-tag-fdxb-iso11784-reader-module/
    1: 02 start number（fixed）
    2: 10 bit HEX format ASCII card number, LSB first.
    3: 4 bit HEX format ASCII country number, LSB first:
    4: Data flag, 0 or 1
    5: Animal flag, 0 or 1
    6: reserved.
    7: reserved.
    8: Checksum, all 26bit ACSII HEX XOR。
    9: Checksum Bitwise invert.
    10: 03 end number (fixed）

    ToDo: do something with checksum
  */


void processTag(unsigned char tagContent[30]) {
  bool validTag = true;


  validTag = validTag & (tagContent[0] == 0x2);
  validTag = validTag & (tagContent[tagExpectedSize-1] == 0x3);
  
  if (validTag) {
    long decCountryCode = processTagCountry(tagContent);
    Serial.print("Country: ");
    Serial.println(decCountryCode);
    long decCardNumber = processTagCardNumber(tagContent);
    Serial.print("Tag: ");
    Serial.println(decCardNumber);    
  } else {
    Serial.println("Invalid Tag.");
  }
}

char convAsciiToHexChar(char input) {
  return input;
}

unsigned long convertHexStringToNumber(String input) {
  const char * constInput = input.c_str();
  long decResult = strtol(constInput, NULL, 16);
  return decResult;
}

long processTagCardNumber(unsigned char tagContent[30]) {
  long decCardNumber = processPartialTag(tagContent, cardNumberSizeOffset, cardNumberSize);
  return decCardNumber;
}

long processTagCountry(unsigned char tagContent[30]) {
  long decCountryCode = processPartialTag(tagContent, countryNumberSizeOffset, countryNumberSize);
  return decCountryCode;
}

long processPartialTag(unsigned char tagContent[30], const int offset, const int size) {
  unsigned char tagBuffer[size];
  String resultCode = "";
  
  for (int i = 0; i < size; i++) {
    tagBuffer[i] = tagContent[offset + i];
    resultCode = convAsciiToHexChar(tagBuffer[i]) + resultCode;
  }

  long decResultCode = convertHexStringToNumber(resultCode);
  return decResultCode;
}