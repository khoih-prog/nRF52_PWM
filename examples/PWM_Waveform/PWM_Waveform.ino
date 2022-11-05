/****************************************************************************************************************************
  PWM_Waveform.ino

  For nRF52-based boards usinghardware-based PWM with Adafruit_nRF52_Arduino core
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       3

// Select false to use PWM
#define USING_TIMER       false   //true

#include "nRF52_PWM.h"

// OK for Feather_nRF52840_Express   (5, 6, 9-13, 14-21/A0-A7, etc.)
// OK for ItsyBitsy_nRF52840_Express (5, 7, 9-13, 14-20/A0-A6, etc.)

#define pinToUse       5

//creates pwm instance
nRF52_PWM* PWM_Instance;

typedef struct
{
  uint16_t level;
} PWD_Data;

// Data for 0-100%
PWD_Data PWM_data[] =
{
  {   0 },
  {   5 },
  {  10 },
  {  15 },
  {  20 },
  {  25 },
  {  30 },
  {  35 },
  {  40 },
  {  45 },
  {  50 },
  {  55 },
  {  60 },
  {  65 },
  {  70 },
  {  75 },
  {  80 },
  {  85 },
  {  90 },
  {  95 },
  { 100 },
  {  95 },
  {  90 },
  {  85 },
  {  80 },
  {  75 },
  {  70 },
  {  65 },
  {  60 },
  {  55 },
  {  50 },
  {  45 },
  {  40 },
  {  35 },
  {  30 },
  {  25 },
  {  20 },
  {  15 },
  {  10 },
  {   5 },
  {   0 },
};

#define NUM_PWM_POINTS      ( sizeof(PWM_data) / sizeof(PWD_Data) )

float frequency = 2000.0f;
float dutyCycle = 0.0f;

uint8_t channel = 0;

// You can select any value
PWD_Data PWM_data_idle = PWM_data[0];

char dashLine[] = "============================================================================================";

void printPWMInfo(nRF52_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DutyCycle = ");
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

  Serial.print(F("\nStarting PWM_Waveform on "));
  Serial.println(BOARD_NAME);
  Serial.println(NRF52_PWM_VERSION);

  // Create a dummy instance
  PWM_Instance = new nRF52_PWM(pinToUse, frequency, dutyCycle);

  if ( (PWM_Instance) && PWM_Instance->isPWMEnabled() )
  {
    // setPWM_manual(uint8_t pin, uint16_t level)
    PWM_Instance->setPWM(pinToUse, frequency, 0);

    printPWMInfo(PWM_Instance);
  }
  else
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }
}

void updateDC()
{
  static uint16_t index = 0;

  // Mapping data to any other frequency from original data 0-100 to actual 16-bit Dutycycle
  PWM_Instance->setPWM_manual(pinToUse, ( (uint32_t) PWM_data[index].level * MAX_16BIT ) / 100 );

  // Use at low freq to check
  //printPWMInfo(PWM_Instance);

  index = (index + 1) % NUM_PWM_POINTS;
}

void check_status()
{
#define UPDATE_INTERVAL     100L

  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (100) milliseconds
  if (millis() > update_timeout)
  {
    updateDC();
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}

void loop()
{
  check_status();
}
