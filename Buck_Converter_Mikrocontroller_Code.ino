bool currentPin,lastPin;
unsigned long startDeb,endDeb;
int Dutycycle;

void setup() {
  TCCR1A = B10110010;
  TCCR1B = B00011001;
  ICR1 = 640;
  DDRB = B01100000;
  OCR1A = 320;
  OCR1B = OCR1A + 10;
  PCICR = B00000001;
  PCMSK0 = B00000111;
}

void loop() {

}

ISR(PCINT2_vect) {
  currentPin = ((1 << 0)&PINB) >> 7;
  startDeb = micros();
  if (startDeb - endDeb > 1000) {
    if (currentPin != lastPin) {
      if (((1 << 0)&PINB) >> 0 != ((1 << 1)&PINB) >> 1) {
        Dutycycle += 1;
      }
      else if (((1 << 0)&PINB) >> 0 == ((1 << 1)&PINB) >> 1) {
        Dutycycle -= 1;
      }
      if (Dutycycle >= 98) {
        Dutycycle = 98;
      }
      else if (Dutycycle <= 1) {
        Dutycycle = 1;
      }
      dutyCycle(Dutycycle);
      lastPin = currentPin;
      endDeb = startDeb;
    }
  }
}

int dutyCycle(int duty) {
  if (duty >= 98) {
    duty = 98;
  }
  else if (duty <= 1) {
    duty = 1;
  }
  OCR1A = duty * 6.3;
  OCR1B = OCR1A + 10;
  return duty;
}
