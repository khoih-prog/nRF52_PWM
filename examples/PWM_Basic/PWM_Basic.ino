/****************************************************************************************************************************
  PWM_Basic.ino

  For nRF52-based boards usinghardware-based PWM with Adafruit_nRF52_Arduino core
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       4

// Select false to use PWM
#define USING_TIMER       false   //true

#include "nRF52_PWM.h"

// OK for Feather_nRF52840_Express   (5, 6, 9-13, 14-21/A0-A7, etc.)
// OK for ItsyBitsy_nRF52840_Express (5, 7, 9-13, 14-20/A0-A6, etc.)

#define pinToUse       5

//creates pwm instance
nRF52_PWM* PWM_Instance;

float frequency = 1000.0f;

float dutyCycle = 0.0f;

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting PWM_Basic using PWM on "));
  Serial.println(BOARD_NAME);
  Serial.println(NRF52_PWM_VERSION);

  //assigns PWM frequency of 1.0 KHz and a duty cycle of 0%
  PWM_Instance = new nRF52_PWM(pinToUse, frequency, dutyCycle);

  if ( (!PWM_Instance) || !PWM_Instance->isPWMEnabled())
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }
}

void loop()
{
  // You can change frequency here, anytime
  frequency = 2000.0f;
  //frequency = 20.0f;
  dutyCycle = 20.0f;

  PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);

  delay(10000);

  // You can change frequency here, anytime
  frequency = 5000.0f;
  //frequency = 50.0f;
  dutyCycle = 90.0f;

  PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);

  //while (1)
  delay(10000);
}
