#include "Arduino.h"
#include "Wire.h"
#include "DS3232RTC.h"
#include "Streaming.h"  


void printDateTime(time_t t) {
   Serial << ((day(t)<10) ? "0" : "") << _DEC(day(t));
   Serial << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
   Serial << ((hour(t)<10) ? "0" : "") << _DEC(hour(t)) << ':';
   Serial << ((minute(t)<10) ? "0" : "") << _DEC(minute(t)) << ':';
   Serial << ((second(t)<10) ? "0" : "") << _DEC(second(t));
}


void setup() {
   Serial.begin(9600);

   // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
   RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
   RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
   RTC.alarm(ALARM_1);
   RTC.alarm(ALARM_2);
   RTC.alarmInterrupt(ALARM_1, false);
   RTC.alarmInterrupt(ALARM_2, false);
   RTC.squareWave(SQWAVE_NONE);
    
   // setSyncProvider() causes the Time library to synchronize with the
   // external RTC by calling RTC.get() every five minutes by default.
   setSyncProvider(RTC.get);
   Serial << "RTC Sync";
   if (timeStatus() != timeSet) {
      Serial << " FAIL!";
   }
   Serial << endl;

   printDateTime(RTC.get());
   Serial << " --> Current RTC time\n";
  
     // set Alarm 1 for 06:30:00
   RTC.setAlarm(ALM1_MATCH_HOURS, 0, 30, 21, 0);

   // set Alarm 2 for 06:30:00
   RTC.setAlarm(ALM2_MATCH_HOURS, 0, 35, 21, 0);

   // clear the alarm flags
   RTC.alarm(ALARM_1);
   RTC.alarm(ALARM_2);

   // configure the INT/SQW pin for "interrupt" operation (disable square wave output)   
   RTC.squareWave(SQWAVE_NONE);

   // enable interrupt output for Alarm 2 only
   RTC.alarmInterrupt(ALARM_1, true);
   RTC.alarmInterrupt(ALARM_2, true);
}

void loop() { 
   if (RTC.alarm(ALARM_1)) {
      printDateTime(RTC.get());
      Serial << " --> Alarm 1\n";
   }
   if (RTC.alarm(ALARM_2)) {
      printDateTime(RTC.get());
      Serial << " --> Alarm 2\n";
   }  
}