#ifndef relay_H
#define relay_H

#include <Arduino.h>

class relay {
  
  private:
    int relay1pin;
    int relay2pin;
    int relay3pin;
    int relay4pin;
    int relaySENTRY;
    bool bikestatus;
  public:
    relay(int R1, int R2, int R3, int R4);
    void ignitionturnon();
    void startbutton();
    void turnonrelay3();
    void turnonbuzzer();
    bool returnbikestatus();
    void turnoffbuzzer();
    void ignitionturnoff();
    void activatesentrymode();
    void deactivatesentrymode();
    int returnsentryvalue();
    void stopbutton();
    void turnoffrelay3();
    void turnoffrelay4();
};
#endif
