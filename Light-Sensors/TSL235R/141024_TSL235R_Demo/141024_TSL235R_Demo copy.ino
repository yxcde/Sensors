volatile unsigned long count = 0;
unsigned long oldcount = 0;
unsigned long temp = 0;
unsigned long lastRead;
unsigned long avg = 0;
unsigned long freq = 0;
long loopcount = 0;

void setup() {
  Serial.begin(115200);                 // Note higher baud rate
  Serial.println("Starting...");
  pinMode(2, INPUT);            // Set pin 2 to input
  digitalWrite(2, HIGH);        // Turn on pullup resistor
  attachInterrupt(0, count_inc, RISING);
}

void loop() {
  if (millis() - lastRead > 5) {
    lastRead = millis();
    temp = count;
    freq = temp - oldcount;
    avg = avg + freq;
    if (loopcount % 50) {
      Serial.println(avg / 50);
      avg = 0;
      loopcount = 0;
    }
    loopcount++;
    oldcount = temp;
  }
}

void count_inc() {
  count++;
}