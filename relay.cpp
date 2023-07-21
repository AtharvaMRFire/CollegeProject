#include "relay.h"

relay::relay(int R1, int R2, int R3, int R4)
{
    relay1pin = R1;
    relay2pin = R2;
    relay3pin = R3;
    relay4pin = R4;
    relaySENTRY;
    pinMode(relay1pin, OUTPUT);
    pinMode(relay2pin, OUTPUT);
    pinMode(relay3pin, OUTPUT);
    pinMode(relay4pin, OUTPUT);
}

void relay::ignitionturnon()
{
  bikestatus = true;
  digitalWrite(relay1pin, LOW);
}

bool relay::returnbikestatus()
{
  return bikestatus;
}

void relay::startbutton()
{
  digitalWrite(relay2pin, LOW);
}

void relay::turnonrelay3()
{
  digitalWrite(relay3pin, LOW);
}

void relay::activatesentrymode()
{
  relaySENTRY = 1;
}

void relay::deactivatesentrymode()
{
  relaySENTRY = 0;
}

void relay::turnonbuzzer()
{
  digitalWrite(relay4pin, LOW);
}

void relay::turnoffbuzzer()
{
  digitalWrite(relay4pin, HIGH);
}

void relay::ignitionturnoff()
{
  digitalWrite(relay1pin, HIGH);
  bikestatus = false;
}

void relay::stopbutton()
{
  digitalWrite(relay2pin, HIGH);
}

void relay::turnoffrelay3()
{
  digitalWrite(relay3pin, HIGH);
}

void relay::turnoffrelay4()
{
  digitalWrite(relay4pin, HIGH);
}

int relay:: returnsentryvalue()
{
  return relaySENTRY;
}
