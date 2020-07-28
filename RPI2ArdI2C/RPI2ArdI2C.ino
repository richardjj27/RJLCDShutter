#include <Wire.h>
#define SLAVE_ADDRESS 0x08
int ShutterOpen = 0;
int Value = 0;
int CountDown;

void setup() 
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendData);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
}

void receiveEvent(int bytes)
{
  Value = Wire.read();
  if (Value==0) { ShutterOpen = 0; }
  if (Value==1) { ShutterOpen = 1; CountDown = 20; digitalWrite(13, HIGH);delay(200);digitalWrite(13, LOW);}
  if (Value==99) { ShutterOpen = 1; CountDown = 99; } 
}

void sendData()
{
  Wire.write(CountDown);
}

void loop(void)
{
  if (ShutterOpen == 0)
  {
    digitalWrite(4, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(13, HIGH);
    ShutterOpen = 2;
    delay(500);
  }
  if (ShutterOpen == 2)
  {
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);
    ShutterOpen = 0;
    delay(500);
  }
  if (ShutterOpen == 1)
  {
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    digitalWrite(13, LOW);
    if (CountDown != 99) {CountDown--;}
    if (CountDown == 0) {ShutterOpen = 0;}
    delay(1000);
  }
}
