const char AddressPins[] = {
  52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22
  /*
  22,24,26,28,30,32,34,36,
  38,40,42,44,46,48,50,52
  */
};
const char DataPins[] = {
  53,51,49,47,45,43,41,39 
  // 39,41,43,45,47,49,51,53
};
#define CLOCK 2
#define READ_WRITE 3

void setup() {
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);
  for (int n=0; n < 16; n++){
    pinMode(AddressPins[n], INPUT);
  }
  for (int n=0; n < 8; n++){
    pinMode(DataPins[n], INPUT);
  }


  
  Serial.begin(9600);
}

void onClock() {
  char output[15];
  unsigned int address = 0;
  for (int n=0; n < 16; n++){
      int bit = digitalRead(AddressPins[n]) ? 1 : 0;
      Serial.print(bit);
      address = (address << 1) + bit;
  }
  Serial.print(" ");
  unsigned int data = 0;
  for (int n=0; n < 8; n++){
      int bit = digitalRead(DataPins[n]) ? 1 : 0;
      Serial.print(bit);
      data = (data << 1) + bit;
  }
  sprintf(output, "  %04x  %c %02x", address, digitalRead(READ_WRITE) ? 'r' : 'W', data);
  
  Serial.println(output); 
}

void loop() {
  
}
