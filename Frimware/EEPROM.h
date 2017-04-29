/*
   Writen by Tirarex 2017
*/


void CleanEEPROM(int ending) {
  for (int i = 0; i < ending; ++i) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

void InitEEPROM(int esize) {
  EEPROM.begin(esize);
}

String ReadEEPROM(int from, int to) {
  String output;
  for (int i = from; i < to; ++i)
  {
    output += char(EEPROM.read(i));
  }
  return output;
}




