#include <TimeAlarms.h>
#include <ArduinoJson.h>

AlarmId allAlarmIds[6];

//////////////////////////////////////////////// Functions declarations

AlarmId setAlarm(JsonObject);
void blinkBuiltinLed();
void clearAllAlarms();
void setAllAlarms(JsonArray);

//////////////////////////////////////////////// Alarms

AlarmId setAlarm(JsonObject obj) {
  int h = obj["h"].as<int>();
  int m = obj["m"].as<int>();
  int q = obj["q"].as<int>();
  int s = obj["s"].as<int>();

  Serial.println(String("Setting new alarm: ")+h+String(":")+m);

  AlarmId alarm_id = Alarm.alarmRepeat(h,m,0,startMotor);  // Set alarm every day
  if (s==1) {
    Serial.println(String("New alarm set with ID: ")+alarm_id);
  } else {
    Serial.println(String("New alarm set in deactivated state with Id:")+alarm_id);
    Alarm.disable(alarm_id);
  }
  return alarm_id;
}

void blinkBuiltinLed() {
  Serial.println("New call to scheduled function.");
  if(digitalRead(LED_BUILTIN) == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void clearAllAlarms() {
  Serial.println("Clearing up all alarms, IDs:");
  int i;
  // Array of 6 ids
  for (i=0;i<6;i++) {
    Serial.print(allAlarmIds[i]+String(" ; "));
    Serial.println();
    Alarm.disable(allAlarmIds[i]);
    Alarm.free(allAlarmIds[i]);
    allAlarmIds[i] = NULL;
  }
}

void setAllAlarms(JsonArray arr) {
  clearAllAlarms();
  Serial.println("Setting all alarms");
  // Iterate over schedule items
  int i = 0;
  for (JsonVariant value : arr) {
    JsonObject obj = value.as<JsonObject>();
    AlarmId alarm_id = setAlarm(obj);

    allAlarmIds[i] = alarm_id; //Register alarm id to be able to clear it up
    i++;
  }
}
