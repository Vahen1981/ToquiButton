#include <ToquiButton.h>

ToquiButton::ToquiButton(int pin) : pin(pin) {}

void ToquiButton::begin() {
  pinMode(pin, INPUT);          //Normalmente INPUT_PULLUP, excepto en los pines que no incluyen resistencias pull up, como el 34 y 35 de ESP32, en este caso solo INPUT
}

void ToquiButton::setLongClick(uint16_t clickTime){
    longClickTime = clickTime;
}

int ToquiButton::update() {
    uint8_t state = digitalRead(pin);
    if(state == prevState && state == LOW){
        if(isFunctionFirstTime){
           pressedTime = millis(); 
           isFunctionFirstTime = false;
        }
        if(digitalRead(pin) == LOW){
            if(millis() > (pressedTime + longClickTime)){
                estado = 4;
                return LongClick;
            }
            else{
                estado = 1;
                return Pressed;
            }
         }
    }
    if(state == prevState && state == HIGH){
        estado = 3;
    }

    if(state != prevState){
        if(timeFlag){
            lastEventTime = millis();
            timeFlag = false;
        }
        if(millis() > (lastEventTime + 25) ){
            timeFlag = true;
            if(state == LOW){
                prevState = state;
                estado = 0;
            }
            if(state == HIGH){
                prevState = state;
                estado = 2;
            }
        }
    }

    switch (estado) {
        case 0:
            return Falling;
            break;
      
        case 1:
            return Pressed;
            break;
      
        case 2:
            return Rising;
            break;
      
        case 3:
            isFunctionFirstTime = true;
            return Released;
            break;
        
        case 4:
            return LongClick;
            break;
    }
}



