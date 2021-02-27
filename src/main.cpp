#include"Arduino.h"
#include"HardwareTimer.h"

#define ledPin PC13
bool rise = true;

void ISR_timerNr1();

HardwareTimer *timerPWM;
HardwareTimer *timerISR;

void setup()
{
  pinMode(PB9, OUTPUT);

  timerISR = new HardwareTimer(TIM4);
  timerISR->setOverflow(2000, MICROSEC_FORMAT);
  timerISR->attachInterrupt(ISR_timerNr1);
  timerISR->resume();

  timerPWM = new HardwareTimer(TIM1);
  timerPWM->setOverflow(1000, HERTZ_FORMAT); 
  timerPWM->setMode(2, TIMER_OUTPUT_COMPARE_PWM2, PA9);
  timerPWM->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
  timerPWM->resume();
}

void loop()
{
  for (int i=0; i<=100; i++)
  {
    timerPWM->setCaptureCompare(2, i, PERCENT_COMPARE_FORMAT);
    delay(5);
  }
  for (int i=100; i>=0; i--)
  {
    timerPWM->setCaptureCompare(2, i, PERCENT_COMPARE_FORMAT);
    delay(5);
  }
}

void ISR_timerNr1(){
  if (rise){
    digitalWrite(PB9, HIGH);
    rise = false;
  }
  else{
    digitalWrite(PB9, LOW);
    rise = true;
  }
}