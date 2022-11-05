/****************************************************************************************************************************
  PWM_DynamicDutyCycle.ino

  For nRF52-based boards usinghardware-based PWM with Adafruit_nRF52_Arduino core
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       4

// Select false to use PWM
#define USING_TIMER       false   //true

#include "nRF52_PWM.h"

// OK for Feather_nRF52840_Express (5, 6, 9, 10, 14-21/A0-A7, etc.)

#define pinToUse       6

//creates pwm instance
nRF52_PWM* PWM_Instance;

float frequency;
float dutyCycle;

char dashLine[] = "=====================================================================================";

void printPWMInfo(nRF52_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DC = ");
  Serial.print(PWM_Instance->getActualDutyCycle());
  Serial.print(", PWMPeriod = ");
  Serial.print(PWM_Instance->getPWMPeriod());
  Serial.print(", PWM Freq (Hz) = ");
  Serial.println(PWM_Instance->getActualFreq(), 4);
  Serial.println(dashLine);
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting PWM_DynamicDutyCycle on "));
  Serial.println(BOARD_NAME);
  Serial.println(NRF52_PWM_VERSION);

  frequency = 5000.0f;

  PWM_Instance = new nRF52_PWM(pinToUse, frequency, 0.0f);

  if ( (!PWM_Instance) || !PWM_Instance->isPWMEnabled())
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }

  Serial.println(dashLine);
}

void loop()
{
  dutyCycle = 90.0f;

  Serial.print(F("Change PWM DutyCycle to "));
  Serial.println(dutyCycle);
  PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);

  printPWMInfo(PWM_Instance);

  delay(5000);
  dutyCycle = 20.0f;

  Serial.print(F("Change PWM DutyCycle to "));
  Serial.println(dutyCycle);
  PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);
  printPWMInfo(PWM_Instance);

  delay(5000);
}
