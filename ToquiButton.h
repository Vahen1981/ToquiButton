#ifndef ToquiButton_h
#define ToquiButton_h

#include <Arduino.h>

class ToquiButton {
  private:
    const int pin;
    uint8_t prevState = HIGH;
    unsigned long lastEventTime;
    bool timeFlag = true;
    uint8_t estado = 0;
    uint16_t longClickTime = 1000;
    unsigned long pressedTime;
    bool isFunctionFirstTime = true;



  public:
    ToquiButton(int pin);
    void begin();
    void setLongClick(uint16_t clickTime);
    int update();

    enum States {
        Falling,
        Pressed,
        Rising,
        Released,
        LongClick
    };
};

#endif


