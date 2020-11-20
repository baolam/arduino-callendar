/*
  Check
  AddCallback
*/

#ifndef _CALLENDAR_H_
#define _CALLENDAR_H_
#define MAX_LISTENER 10
//#include <Arduino.h>
#if defined(WIRING) && WIRING >= 100
  #include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <RTClib.h>
#include <string.h>
//#define DEBUG; // Block comment if you turn on the 'DEBUG' mode
#if defined(DEBUG)
#define USE_DEBUG Serial
#endif

struct plain {
  boolean type;
  String start;
  String end;
  String time;
  void (* function)();
};

class Callendar {
  private:
  //char* buf[10] = "hh:mm:ss";
  int counter = 1;
  RTC_DS1307 rtc;
  plain *yPlainlist;

  int StringtoDec(String data) {
    return data.toInt();
  }
  
  public:
  Callendar();
  
  void begin(int b, boolean debugOutput);
  void begin();
  void add(String start, String end, void (*function)());
  void add(String time, void (*function)());
  int getData(String data, const char* stg);
  void loop();  
  
  protected:
  
};

#endif
