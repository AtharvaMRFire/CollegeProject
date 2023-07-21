#include "relay.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <math.h>


char input;
float x_value, y_value, z_value;
float x_value_temp, y_value_temp, z_value_temp;

SoftwareSerial mySerial(13,12); // Bluetooth pins. 13 -> TX, 12-> RX
relay RELAY (2, 4, 7, 8);// relay pins 2 -> Ignition On, 3-> Engine On, 8-> Buzzer
Adafruit_ADXL345_Unified accelerometer = Adafruit_ADXL345_Unified();
sensors_event_t event; 

void setup()
{
      RELAY.turnoffrelay3();
      RELAY.turnoffbuzzer();
      RELAY.ignitionturnoff();
      RELAY.stopbutton();
      Serial.begin(9600);
      mySerial.begin(9600);
      accelerometer.begin();
      accelerometer.getEvent(&event);
      x_value_temp = event.acceleration.x;
      y_value_temp = event.acceleration.y;
      z_value_temp = event.acceleration.z;
      RELAY.deactivatesentrymode();
}

void loop()
{
  Serial.println("-------------");
  accelerometer.getEvent(&event);
  if (mySerial.available() > 0) // checks if data has been sent by the bluetooth module to arduino, that is it has received data from the app. If there is data, mySerial.available() is greater than 0
  {
    input = mySerial.read();// captures the data that has been sent
    Serial.print("Data Received. Value = ");
    Serial.println(input); // above and below statements print the data that has been sent
    if(input == '0')// if data is 0, bike is turned off, and sentry mode is deactivated
    {
      RELAY.ignitionturnoff();
      RELAY.stopbutton();
      RELAY.deactivatesentrymode();
    }
    else if(input == '1')// bike ignition is on
    {
      RELAY.ignitionturnon();
    }
    else if(input== '2') // bike engine is started. for 500 milliseconds the self start button will be held
    {
      RELAY.startbutton();
      delay(500);
      RELAY.stopbutton();
    }
    else if(input == '3')// if sentry mode is activated bike shaking will turn on the buzzer
    {
      RELAY.activatesentrymode();
    }
    else if(input == '4')//if sentry mode is deactivated bike shaking will not turn on the buzzer
    {
      RELAY.deactivatesentrymode();
    }
  }
  if (mySerial.available()>0)// statement used while debugging which shows data after the if-else statement. Ignore
    Serial.write(mySerial.read());//Ignore

  x_value_temp = abs(x_value - event.acceleration.x);
  y_value_temp = abs(y_value - event.acceleration.y);
  z_value_temp = abs(z_value - event.acceleration.z);

  
  Serial.print(RELAY.returnsentryvalue());
  if( ((abs(x_value_temp) > 0.2) || (abs(x_value_temp) > 0.2) || (abs(x_value_temp) > 0.2)) && (RELAY.returnsentryvalue() == 1) && (RELAY.returnbikestatus() == false))
  {
    Serial.println("Turned On");
    RELAY.turnonbuzzer();
  }
  else if(RELAY.returnsentryvalue() == 0)
  {
    RELAY.turnoffbuzzer();
  }
    
  displayaccvalue();

  x_value = event.acceleration.x;
  y_value = event.acceleration.y;
  z_value = event.acceleration.z; 
  delay(1500);
}

void displayaccvalue()
{
   Serial.println("-------------");
   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  "); Serial.println("m/s^2 "); 
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  "); Serial.println("m/s^2 ");
   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  "); Serial.println("m/s^2 ");
   Serial.println("-------------");
}
