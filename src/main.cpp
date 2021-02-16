#include"Arduino.h"
#include"HardwareTimer.h"

#define ledPin PC13
bool rise = true;

void ISR_timerNr1();

void setup()
{
  pinMode(ledPin, OUTPUT);
  TIM_TypeDef *Instance = TIM4;
  HardwareTimer *timer = new HardwareTimer(Instance);
  timer->setOverflow(2000000, MICROSEC_FORMAT);
  timer->attachInterrupt(ISR_timerNr1);
  timer->resume();
}

void loop()
{
  delay(10);
}

void ISR_timerNr1(){
  if (rise){
    digitalWrite(ledPin, HIGH);
    rise = false;
  }
  else{
    digitalWrite(ledPin, LOW);
    rise = true;
  }
}