
const int LED = 13;
const int BUTTON = 7;

const int STATE_ON = 1;
const int STATE_OFF = 0;

class Switch {
private:
  int button;
  int val;
  int valPrev;
  int valPrevPrev;
  int valPrevPrevPrev;

public:
  Switch(int);
  boolean turnedOn(void);
  void shiftValues(int);
  boolean buttonIsHigh(void);
  boolean buttonTurnedHigh(void);
};

Switch *swt;
int state = STATE_OFF;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  swt = new Switch(BUTTON);
}

void loop() {
  if (swt->turnedOn()) {
    state ^= 1;
  }

  if (state == STATE_ON) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

Switch::Switch(int button) {
  this->button = button;
  this->valPrev = LOW;
  this->valPrevPrev = LOW;
  this->valPrevPrevPrev = LOW;
}

boolean Switch::turnedOn() {
  boolean flag = false;
  if (this->buttonTurnedHigh()) {
    delay(20);
    if (this->buttonIsHigh()) {
      this->shiftValues(HIGH);
      return true;
    }
  }

  this->shiftValues(LOW);
  return false;
}

void Switch::shiftValues(int val) {
  this->valPrevPrevPrev = this->valPrevPrev;
  this->valPrevPrev = this->valPrev;
  this->valPrev = val;
}

boolean Switch::buttonIsHigh() {
  return digitalRead(this->button);
}

boolean Switch::buttonTurnedHigh() {
  return this->buttonIsHigh() && this->valPrev == LOW && this->valPrevPrev == LOW && this->valPrevPrevPrev == LOW;
}
