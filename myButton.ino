
const int LED = 13;
const int BUTTON = 7;
const int DUR = 500;

const int STATE_ON = 1;
const int STATE_OFF = 0;

int val = LOW;
int prevVal = LOW;
int prevPrevVal = LOW;
int prevPrevPrevVal = LOW;
int state = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  val = digitalRead(BUTTON);
  
  if (val == HIGH && prevVal == LOW && prevPrevVal == LOW  && prevPrevPrevVal == LOW) {
    delay(20);
    val = digitalRead(BUTTON);
    if (val == HIGH) {
      state ^= 1;
    }
  }
  
  if (state == STATE_ON) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  
  prevPrevPrevVal = prevPrevVal;
  prevPrevVal = prevVal;
  prevVal = val;
}
