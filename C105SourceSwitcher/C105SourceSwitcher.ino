const int  iButtonPin1 = 6;
const int  iButtonPin2 = 7;
const int  iButtonPin3 = 8;
const int iRelayPin1 = 9;
const int iRelayPin2 = 10;
const int iIndicator1 = 2;
const int iIndicator2 = 3;
const int iIndicator3 = 4;

int iPreviousButton = -1;
int iLatestButton = 1;
int iButtonState1 = 1;
int iButtonState2 = 1;
int iButtonState3 = 1;
int iState = -1;

int iDebounceDelay = 2000;

void setup() {
  // initialize the button pins as inputs
  pinMode(iButtonPin1, INPUT_PULLUP);
  pinMode(iButtonPin2, INPUT_PULLUP);
  pinMode(iButtonPin3, INPUT_PULLUP);
  // initialize the relays as outputs
  pinMode(iRelayPin1, OUTPUT);
  pinMode(iRelayPin2, OUTPUT);
  // initialise the indicator pins as outputs (to the Pi)
  pinMode(iIndicator1, OUTPUT);
  pinMode(iIndicator2, OUTPUT);
  pinMode(iIndicator3, OUTPUT);
}


void loop() {
  if (debouncedReadWaitingForRelease(iButtonPin1)) {
    iLatestButton = 1;
  } else if (debouncedReadWaitingForRelease(iButtonPin2)) {
    iLatestButton = 2;
  } else if (debouncedReadWaitingForRelease(iButtonPin3)) {
    iLatestButton = 3;
  }
  
  if (iLatestButton != iPreviousButton) {
    iPreviousButton = iLatestButton;
    switch(iLatestButton) {
      case 1:
        digitalWrite(iRelayPin1, LOW);
        digitalWrite(iRelayPin2, LOW);
        digitalWrite(iIndicator1, HIGH);
        digitalWrite(iIndicator2, LOW);
        digitalWrite(iIndicator3, LOW);
        break;
      case 2:
        digitalWrite(iRelayPin1, HIGH);
        digitalWrite(iRelayPin2, LOW);
        digitalWrite(iIndicator1, LOW);
        digitalWrite(iIndicator2, HIGH);
        digitalWrite(iIndicator3, LOW);
        break;
      case 3:
        digitalWrite(iRelayPin1, LOW);
        digitalWrite(iRelayPin2, HIGH);
        digitalWrite(iIndicator1, LOW);
        digitalWrite(iIndicator2, LOW);
        digitalWrite(iIndicator3, HIGH);
        break;
      default:
        break;
    }
  }
}

bool debouncedReadWaitingForRelease(int pin) {
  int initialState = digitalRead(pin);

  // If it's low to start with, return false.
  if (initialState == LOW) {
    return false;
  }
  
  // If it's high, make sure it stays high for the debounce period...
  delay(iDebounceDelay);
  if (digitalRead(pin) != HIGH) {
    return false;
  }
  
  // Wait for it to go low to actually trigger the transition
  while (digitalRead(pin) == LOW) {
    ;
  }
  
  return true;
}
