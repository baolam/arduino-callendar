#include "Callendar.h"

Callendar::Callendar() {
  
}

void Callendar::begin(int b, boolean debugOutput) {
  #if defined(DEBUG)
  USE_DEBUG.begin(b);
  //USE_DEBUG.setebugOutput(debugOutput);
  USE_DEBUG.println("Start debugging...");
  #else 
  #error "You must define 'DEBUG' in your code!"
  #endif  

  if(! rtc.begin()) {
    #if defined(DEBUG)
    USE_DEBUG.println("Couldn't find RTC");
    #endif
    return;
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if(! rtc.isrunning()) {
    #if defined(DEBUG)
    USE_DEBUG.println("RTC is NOT running, let's set the time!");
    #endif
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
  }
}

void Callendar::begin() {
  if(! rtc.begin()) return;
  if(! rtc.isrunning()) return;  
}

void Callendar::loop() {
  DateTime now = rtc.now();
  
  char buf[] = "hh:mm:ss";
  String timeNow = now.toString(buf);
  //String timeNow = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  #if defined(DEBUG)
  USE_DEBUG.println("--------------------");
  USE_DEBUG.println(timeNow);
  USE_DEBUG.println("--------------------");
  #endif

  for(int i = 1; i <= counter; i++) {
    //USE_DEBUG.println("Running...");
    //delayMicroseconds(10);
    if(yPlainlist[i].type == false) {
      if(timeNow == yPlainlist[i].time) {
        #if defined(DEBUG)
        USE_DEBUG.println(F("Time to run event..."));
        #endif
        (* yPlainlist[i].function)();
      }  
    }
    else {
      String timeFutureStart = String(yPlainlist[i].start);
      String timeFutureEnd = String(yPlainlist[i].end);
      
      #if defined(DEBUG)
      USE_DEBUG.println("Trong true");
      USE_DEBUG.println(timeFutureStart);
      USE_DEBUG.println(timeFutureEnd);
      #endif
      
      int hourNow = getData(timeNow, "hour");
      int minuteNow = getData(timeNow, "minute");
      int secondNow = getData(timeNow, "second");

      int hourFutureStart = getData(timeFutureStart, "hour");
      int minuteFutureStart = getData(timeFutureStart, "minute");
      int secondFutureStart = getData(timeFutureStart, "second");

      int hourFutureEnd = getData(timeFutureEnd, "hour");
      int minuteFutureEnd = getData(timeFutureEnd, "minute");
      int secondFutureEnd = getData(timeFutureEnd, "second");

      if((hourFutureStart <= hourFutureEnd) && (hourNow <= hourFutureEnd)) {
        if(hourFutureStart <= hourNow < hourFutureEnd) {
          (* yPlainlist[i].function)();
          return;
        }
        if(hourNow == hourFutureEnd) {
          if(minuteFutureStart <= minuteNow < minuteFutureEnd) {
            (* yPlainlist[i].function)();
            return;
          }
          if(minuteNow == minuteFutureEnd) {
            if(secondFutureStart <= secondNow < secondFutureEnd) {
              (* yPlainlist[i].function)();
              return;
            }
          }
        }
      }
    }
  }
}

void Callendar::add(String start, String end, void (*function)()) {
  #if defined(DEBUG)
  USE_DEBUG.println("Adding plain");
  USE_DEBUG.println(counter);
  #endif

  if(counter <= MAX_LISTENER) {
    yPlainlist = (plain*) realloc(yPlainlist, (counter + 1) * sizeof(plain)); 
    yPlainlist[counter].start = start;
    yPlainlist[counter].end = end;
    yPlainlist[counter].type = true;
    yPlainlist[counter].function = function;  
    counter ++;
  }
}

void Callendar::add(String time, void (*function)()) {
  #if defined(DEBUG)
  USE_DEBUG.println("Adding plain");
  USE_DEBUG.println(counter);
  #endif
  
  if(counter <= MAX_LISTENER) {
    yPlainlist = (plain*) realloc(yPlainlist, (counter + 1) * sizeof(plain)); 
    yPlainlist[counter].time = time;
    yPlainlist[counter].type = false;
    yPlainlist[counter].function = function;  
    counter ++;
  }
}

int Callendar::getData(String data, const char* stg) {
  String h = data.substring(0, 2);
  String m = data.substring(3, 5);
  String s = data.substring(6, 8);

  int hour = StringtoDec(h);
  int minute = StringtoDec(m);
  int second = StringtoDec(s);

  #if defined(DEBUG)
  USE_DEBUG.println(hour);
  USE_DEBUG.println(minute);
  USE_DEBUG.println(second);
  #endif
  
  if(stg == "hour") {
    return hour; 
  }
  else if(stg == "minute") {
    return minute;
  }
  else {
    return second;
  }
}
