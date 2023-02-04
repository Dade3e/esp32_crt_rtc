#include <ESP_8_BIT_GFX.h>

#include <ESP32Time.h>


// Create an instance of the graphics library
ESP_8_BIT_GFX videoOut(0 /* = PAL */, 8 /* = RGB332 color */);

ESP32Time rtc(0);  // offset in seconds GMT+1

RTC_DATA_ATTR unsigned long bootCount = 0;

const int threshold = 40;

//stato: 0 = inattivo, solo rtc
//stato: 1 = mostra ora
//stato: 2 = mostra data
//stato: 3 = imposta ora
//stato: 4 = imposta data
int stato = 1;

int stato_tmp = stato;

int en_display = 26;


void callback(){
  //placeholder callback function
}

void setup() {
  if(bootCount == 0)
    rtc.setTime(0, 11, 16, 3, 2, 2023);
  ++bootCount;
  pinMode(en_display, OUTPUT);
  videoOut.begin();
  
  videoOut.setTextColor(0xFF);
  delay(500);
  stato = 1;
//Setup interrupt on Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T0, callback, threshold);
  touchAttachInterrupt(T7, callback, threshold);

  orologio();
  //spengo monitor con transistor

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();

  pinMode(en_display, INPUT);

  esp_deep_sleep_start();
}

void loop(){

}

void orologio() {
  digitalWrite(en_display, HIGH);
  while(stato != 0){

    if(stato == 1){

      printTime();

      if(touchRead(4) < threshold){
        stato_tmp = 2;
      }

      if(touchRead(27) < threshold){
        stato_tmp = 2;
      }

      if(touchRead(4) < threshold && touchRead(27) < threshold){
        stato_tmp = 3;
      }

      if(touchRead(4) > threshold && touchRead(27) > threshold){
        stato = stato_tmp;
      }
    }

    if(stato == 2){
      printDate();

      if(touchRead(4) < threshold){
        stato_tmp = 0;
      }

      if(touchRead(27) < threshold){
        stato_tmp = 0;
      }

      if(touchRead(4) < threshold && touchRead(27) < threshold){
        stato_tmp = 4;
      }
      if(touchRead(4) > threshold && touchRead(27) > threshold){
        stato = stato_tmp;
      }
    }

    if(stato == 3){
      setTime();
      stato = 1;
      stato_tmp = 1;
    }

    if(stato == 4){
      setDate();
      stato = 2;
      stato_tmp = 2;
    }
    delay(100);
  }
  digitalWrite(en_display, LOW);

}

void waitRelease(){
  while (touchRead(4) < threshold || touchRead(27) < threshold){
    delay(50);
  }
}

void spegni(){
  videoOut.waitForFrame();
  videoOut.fillScreen(0);
  videoOut.setCursor(40, 100);
  videoOut.setTextSize(4);
  videoOut.setTextWrap(false);
  videoOut.print("Spento");
}

void setTime(){
  int tmp_h = rtc.getHour(true);
  int tmp_min = rtc.getMinute();

  waitRelease();

  while(touchRead(4) > threshold || touchRead(27) > threshold ){
    videoOut.waitForFrame();
    videoOut.fillScreen(0);
    videoOut.setCursor(40, 80);
    videoOut.setTextSize(4);
    videoOut.setTextWrap(false);
    videoOut.print("Set Time");

    videoOut.setCursor(30, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print("H:");
    if(touchRead(27) < threshold){
      tmp_h++;
      if(tmp_h>23)
        tmp_h = 0;
    }

    if(touchRead(4) < threshold){
      tmp_h--;
      if(tmp_h < 0)
        tmp_h = 23;
    }

    videoOut.setCursor(140, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print(tmp_h);

    delay(200);
  }

  waitRelease();

  while(touchRead(4) > threshold || touchRead(27) > threshold ){
    videoOut.waitForFrame();
    videoOut.fillScreen(0);
    videoOut.setCursor(40, 80);
    videoOut.setTextSize(4);
    videoOut.setTextWrap(false);
    videoOut.print("Set Time");

    videoOut.setCursor(30, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print("M:");
    if(touchRead(27) < threshold){
      tmp_min++;
      if(tmp_min>59)
        tmp_min = 0;
    }

    if(touchRead(4) < threshold){
      tmp_min--;
      if(tmp_min < 0)
        tmp_min = 59;
    }

    videoOut.setCursor(140, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print(tmp_min);

    delay(200);
  }

  waitRelease();

  rtc.setTime(0, tmp_min, tmp_h, rtc.getDay(), rtc.getMonth() + 1, rtc.getYear());
}

void setDate(){
  int tmp_y = rtc.getYear();
  int tmp_m = rtc.getMonth() + 1;
  int tmp_d = rtc.getDay();

  waitRelease();

  while(touchRead(4) > threshold || touchRead(27) > threshold ){
    videoOut.waitForFrame();
    videoOut.fillScreen(0);
    videoOut.setCursor(40, 80);
    videoOut.setTextSize(4);
    videoOut.setTextWrap(false);
    videoOut.print("Set Date");

    videoOut.setCursor(30, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print("D:");
    if(touchRead(27) < threshold){
      tmp_d++;
      if(tmp_d>31)
        tmp_d = 0;
    }

    if(touchRead(4) < threshold){
      tmp_d--;
      if(tmp_d < 0)
        tmp_d = 31;
    }

    videoOut.setCursor(140, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print(tmp_d);

    delay(200);
  }

  waitRelease();

  while(touchRead(4) > threshold || touchRead(27) > threshold ){
    videoOut.waitForFrame();
    videoOut.fillScreen(0);
    videoOut.setCursor(40, 80);
    videoOut.setTextSize(4);
    videoOut.setTextWrap(false);
    videoOut.print("Set Date");

    videoOut.setCursor(30, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print("M:");
    if(touchRead(27) < threshold){
      tmp_m++;
      if(tmp_m>12)
        tmp_m = 0;
    }

    if(touchRead(4) < threshold){
      tmp_m--;
      if(tmp_m < 0)
        tmp_m = 12;
    }

    videoOut.setCursor(140, 130);
    videoOut.setTextSize(7);
    videoOut.setTextWrap(false);
    videoOut.print(tmp_m);

    delay(200);
  }

  waitRelease();

  while(touchRead(4) > threshold || touchRead(27) > threshold ){
    videoOut.waitForFrame();
    videoOut.fillScreen(0);
    videoOut.setCursor(40, 80);
    videoOut.setTextSize(4);
    videoOut.setTextWrap(false);
    videoOut.print("Set Date");

    videoOut.setCursor(20, 130);
    videoOut.setTextSize(6);
    videoOut.setTextWrap(false);
    videoOut.print("Y:");
    if(touchRead(27) < threshold){
      tmp_y++;
      if(tmp_y>2100)
        tmp_y = rtc.getYear();
    }

    if(touchRead(4) < threshold){
      tmp_y--;
      if(tmp_y < 2022)
        tmp_y = 2100;
    }

    videoOut.setCursor(110, 130);
    videoOut.setTextSize(6);
    videoOut.setTextWrap(false);
    videoOut.print(tmp_y);

    delay(200);
  }

  waitRelease();

  rtc.setTime(rtc.getSecond(), rtc.getMinute(), rtc.getHour(true), tmp_d, tmp_m, tmp_y);

}

void printTime(){
  videoOut.waitForFrame();
  videoOut.fillScreen(0);
  videoOut.setCursor(0, 100);
  videoOut.setTextSize(8);
  videoOut.setTextWrap(false);
  videoOut.print(rtc.getTime("%H:%M"));
}

void printDate(){
  videoOut.waitForFrame();
  videoOut.fillScreen(0);
  videoOut.setCursor(40, 80);
  videoOut.setTextSize(4);
  videoOut.setTextWrap(false);
  videoOut.print(rtc.getTime("%A"));

  videoOut.setCursor(10, 130);
  videoOut.setTextSize(5);
  videoOut.setTextWrap(false);
  videoOut.print(rtc.getTime("%d/%m/%y"));
}
