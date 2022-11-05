/****************************************************************************************************************************
  PWM_Multi.ino

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

// To select correct pins for different frequencies
uint32_t PWM_Pins[] = { 5, 7, 9, 10 };
float frequency[]   = { 2000.0f, 3000.0f, 4000.0f, 8000.0f };
float dutyCycle[]   = { 10.0f, 30.0f, 50.0f, 90.0f };

#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

nRF52_PWM* PWM_Instance[NUM_OF_PINS];

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

  Serial.print(F("\nStarting PWM_Multi on "));
  Serial.println(BOARD_NAME);
  Serial.println(NRF52_PWM_VERSION);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_Instance[index] = new nRF52_PWM(PWM_Pins[index], frequency[index], dutyCycle[index]);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();
    }
  }

  Serial.println(dashLine);
  Serial.println("Index\tPin\tPWM_freq\tDutyCycle\tActual Freq");
  Serial.println(dashLine);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    if (PWM_Instance[index])
    {
      Serial.print(index);
      Serial.print("\t");
      Serial.print(PWM_Pins[index]);
      Serial.print("\t");
      Serial.print(frequency[index]);
      Serial.print("\t\t");
      Serial.print(dutyCycle[index]);
      Serial.print("\t\t");
      Serial.println(PWM_Instance[index]->getActualFreq(), 4);
    }
    else
    {
      Serial.println();
    }
  }

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    printPWMInfo(PWM_Instance[index]);
  }
}

void loop()
{
  //Long delay has no effect on the operation of hardware-based PWM channels
  delay(1000000);
}
