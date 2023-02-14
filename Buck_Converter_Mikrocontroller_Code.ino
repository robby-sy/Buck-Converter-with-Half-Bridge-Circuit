void setup() {
TCCR1A = B10110010;
TCCR1B = B00011001;
ICR1 = 640;
DDRB = B01100000;
OCR1A = 320;
OCR1B = OCR1A + 10; 
}

void loop() {
  // put your main code here, to run repeatedly:

}
