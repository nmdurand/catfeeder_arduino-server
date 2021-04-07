/*
 Based on the SimpleWebServerWiFi example

 Compile, upload the sketch and screen Serial with the command `npm run arduino-serve`

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)
 */

#include <SPI.h>

#include "scripts/motor.h"
#include "scripts/alarms.h" // Alarm.delay() replaces delay() everywhere
#include "scripts/state.h"
#include "scripts/url.h"
#include "scripts/wifiServer.h"
#include "scripts/clock.h"

//////////////////////////////////////////////// Arduino Setup and Loop

void setup() {
  Serial.begin(9600); // initialize serial communication
  while (!Serial); // wait for Arduino Serial Monitor

  // pinMode(LED_BUILTIN, OUTPUT); // set builtin led pin mode
  // digitalWrite(LED_BUILTIN, HIGH);

  connectWiFi();

  setClockViaNTP();

  initializeSchedule();
  initializeMotorPin();

}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop() {
  runMDNS();
  listenToSwitchPin();

  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }

  handleServerClient();
  Alarm.delay(0); // Needed to trigger the alarms
}
