int motorPin = 2; // To the transistor base pin - used to control current sent to the motor
int switchPin = 3; // To the switch hot pin (switch clicked when the motor has turned 1/4 turn)
int switchState = 0;
int newSwitchState = 0;


//////////////////////////////////////////////// Functions declarations

void initializeMotorPin();
void startMotor();
void stopMotor();
void listenToSwitchPin();

//////////////////////////////////////////////// Functions declarations

void initializeMotorPin() {
  stopMotor();
}

void startMotor() {
  Serial.println("Starting motor.");
  digitalWrite(motorPin, HIGH);
}

void stopMotor() {
  Serial.println("Stopping motor.");
  digitalWrite(motorPin, LOW);
}

void listenToSwitchPin() {
    // To be called in loop method
  newSwitchState = digitalRead(switchPin);
  if ((newSwitchState == HIGH) && (switchState == LOW)) {
    Serial.println("Switch released, stopping motor.");
    // Button has been pressed then released
    // Turn off the motor
    stopMotor();
  }
  switchState = newSwitchState;
}
