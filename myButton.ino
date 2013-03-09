
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
  void shiftValues(void);
  void readVal(void);
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
  this->readVal();
  if (this->buttonTurnedHigh()) {
    delay(20);
    this->readVal();
    if (this->val == HIGH) {
      this->shiftValues();
      return true;
    }
  }

  this->shiftValues();
  return false;
}

void Switch::shiftValues() {
  this->valPrevPrevPrev = this->valPrevPrev;
  this->valPrevPrev = this->valPrev;
  this->valPrev = this->val;
}

void Switch::readVal() {
  this->val = digitalRead(this->button);
  return;
}

boolean Switch::buttonTurnedHigh() {
  return this->val == HIGH && this->valPrev == LOW && this->valPrevPrev == LOW && this->valPrevPrevPrev == LOW;
}
