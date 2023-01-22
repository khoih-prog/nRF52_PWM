/****************************************************************************************************************************
  nRF52_PWM.h

  For nRF52-based boards usinghardware-based PWM with Adafruit_nRF52_Arduino core
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/nRF52_PWM
  Licensed under MIT license

  Version: 1.0.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      05/11/2022 Initial coding for nRF52-based boards
  1.0.1   K Hoang      22/01/2023 Add `PWM_StepperControl` example
*****************************************************************************************************************************/

#pragma once

#ifndef NRF52_PWM_H
#define NRF52_PWM_H

////////////////////////////////////////

#if !(defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
      defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || \
      defined(NRF52840_LED_GLASSES) || defined(MDBT50Q_RX) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) || \
      defined(ARDUINO_Seeed_XIAO_nRF52840) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) )
#error This code is designed to run on Adafruit or Seeed nRF52 platform! Please check your Tools->Board setting.
#endif

////////////////////////////////////////

#if !defined(BOARD_NAME)
  #if defined(ARDUINO_Seeed_XIAO_nRF52840)
    #define BOARD_NAME    "Seeed_XIAO_nRF52840"
  #elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense)
    #define BOARD_NAME    "Seeed_XIAO_nRF52840_Sense"
  #endif
#endif

////////////////////////////////////////

#if (_PWM_LOGLEVEL_ > 3)
  #warning Using nRF52 Hardware PWM
#endif

////////////////////////////////////////

#ifndef NRF52_PWM_VERSION
  #define NRF52_PWM_VERSION             "nRF52_PWM v1.0.1"

  #define NRF52_PWM_VERSION_MAJOR       1
  #define NRF52_PWM_VERSION_MINOR       0
  #define NRF52_PWM_VERSION_PATCH       1

  #define NRF52_PWM_VERSION_INT         1000001
#endif

////////////////////////////////////////

#include "Arduino.h"

#include <Adafruit_TinyUSB.h>

#include "PWM_Generic_Debug.h"

////////////////////////////////////////

/*************************************

  // From cores/nRF5/HardwarePWM.h
  #ifdef NRF52840_XXAA
  #define HWPWM_MODULE_NUM    4
  #else
  #define HWPWM_MODULE_NUM    3
  #endif

  ////////////////////////////

  // From cores/nRF5/nordic/nrfx/mdk/nrf52840.h

  typedef struct
  {
  __IOM uint32_t  PTR;                          //!< (@ 0x00000000) Description cluster: Beginning address in RAM of this sequence
  __IOM uint32_t  CNT;                          //!< (@ 0x00000004) Description cluster: Number of values (duty cycles) in this sequence
  __IOM uint32_t  REFRESH;                      //!< (@ 0x00000008) Description cluster: Number of additional PWM
                                                                    periods between samples loaded into compare register
  __IOM uint32_t  ENDDELAY;                     //!< (@ 0x0000000C) Description cluster: Time added after the sequence
  __IM  uint32_t  RESERVED[4];
  } PWM_SEQ_Type;                                 //!< Size = 32 (0x20)

  ////////////////////////////

  typedef struct                                  //!< (@ 0x4001C000) PWM0 Structure
  {
  __IM  uint32_t  RESERVED;
  __OM  uint32_t  TASKS_STOP;                   //!< (@ 0x00000004) Stops PWM pulse generation on all channels at
                                                                    the end of current PWM period, and stops
                                                                    sequence playback
  __OM  uint32_t  TASKS_SEQSTART[2];            //!< (@ 0x00000008) Description collection: Loads the first PWM value
                                                                    on all enabled channels from sequence n,
                                                                    and starts playing that sequence at the
                                                                    rate defined in SEQ[n]REFRESH and/or DECODER.MODE.
                                                                    Causes PWM generation to start if not running.
  __OM  uint32_t  TASKS_NEXTSTEP;               //!< (@ 0x00000010) Steps by one value in the current sequence on
                                                                    all enabled channels if DECODER.MODE=NextStep.
                                                                    Does not cause PWM generation to start if
                                                                    not running.
  __IM  uint32_t  RESERVED1[60];
  __IOM uint32_t  EVENTS_STOPPED;               //!< (@ 0x00000104) Response to STOP task, emitted when PWM pulses
                                                                    are no longer generated
  __IOM uint32_t  EVENTS_SEQSTARTED[2];         //!< (@ 0x00000108) Description collection: First PWM period started
                                                                    on sequence n
  __IOM uint32_t  EVENTS_SEQEND[2];             //!< (@ 0x00000110) Description collection: Emitted at end of every
                                                                    sequence n, when last value from RAM has
                                                                    been applied to wave counter
  __IOM uint32_t  EVENTS_PWMPERIODEND;          //!< (@ 0x00000118) Emitted at the end of each PWM period
  __IOM uint32_t  EVENTS_LOOPSDONE;             //!< (@ 0x0000011C) Concatenated sequences have been played the amount
                                                                    of times defined in LOOP.CNT
  __IM  uint32_t  RESERVED2[56];
  __IOM uint32_t  SHORTS;                       //!< (@ 0x00000200) Shortcuts between local events and tasks
  __IM  uint32_t  RESERVED3[63];
  __IOM uint32_t  INTEN;                        //!< (@ 0x00000300) Enable or disable interrupt
  __IOM uint32_t  INTENSET;                     //!< (@ 0x00000304) Enable interrupt
  __IOM uint32_t  INTENCLR;                     //!< (@ 0x00000308) Disable interrupt
  __IM  uint32_t  RESERVED4[125];
  __IOM uint32_t  ENABLE;                       //!< (@ 0x00000500) PWM module enable register
  __IOM uint32_t  MODE;                         //!< (@ 0x00000504) Selects operating mode of the wave counter
  __IOM uint32_t  COUNTERTOP;                   //!< (@ 0x00000508) Value up to which the pulse generator counter counts
  __IOM uint32_t  PRESCALER;                    //!< (@ 0x0000050C) Configuration for PWM_CLK
  __IOM uint32_t  DECODER;                      //!< (@ 0x00000510) Configuration of the decoder
  __IOM uint32_t  LOOP;                         //!< (@ 0x00000514) Number of playbacks of a loop
  __IM  uint32_t  RESERVED5[2];
  __IOM PWM_SEQ_Type SEQ[2];                    //!< (@ 0x00000520) Unspecified
  __IOM PWM_PSEL_Type PSEL;                     //!< (@ 0x00000560) Unspecified
  } NRF_PWM_Type;

  ////////////////

  // From cores/nRF5/nordic/nrfx/mdk/nrf52840_bitfields.h

  // Bit 0 : Selects up mode or up-and-down mode for the counter
  #define PWM_MODE_UPDOWN_Pos       (0UL)                               //!< Position of UPDOWN field.
  #define PWM_MODE_UPDOWN_Msk       (0x1UL << PWM_MODE_UPDOWN_Pos)      //!< Bit mask of UPDOWN field.
  #define PWM_MODE_UPDOWN_Up        (0UL)                               //!< Up counter, edge-aligned PWM duty cycle
  #define PWM_MODE_UPDOWN_UpAndDown (1UL)                               //!< Up and down counter, center-aligned PWM duty cycle

  // Register: PWM_COUNTERTOP
  // Description: Value up to which the pulse generator counter counts

  // Bits 14..0 : Value up to which the pulse generator counter counts.
  // This register is ignored when DECODER.MODE=WaveForm and only values from RAM are used.
  #define PWM_COUNTERTOP_COUNTERTOP_Pos (0UL)                                         //!< Position of COUNTERTOP field.
  #define PWM_COUNTERTOP_COUNTERTOP_Msk (0x7FFFUL << PWM_COUNTERTOP_COUNTERTOP_Pos)   //!< Bit mask of COUNTERTOP field.

  // Register: PWM_PRESCALER
  // Description: Configuration for PWM_CLK

  // Bits 2..0 : Prescaler of PWM_CLK
  #define PWM_PRESCALER_PRESCALER_Pos     (0UL)                                     //!< Position of PRESCALER field.
  #define PWM_PRESCALER_PRESCALER_Msk     (0x7UL << PWM_PRESCALER_PRESCALER_Pos)    //!< Bit mask of PRESCALER field.
  #define PWM_PRESCALER_PRESCALER_DIV_1   (0UL)                                     //!< Divide by 1 (16 MHz)
  #define PWM_PRESCALER_PRESCALER_DIV_2   (1UL)                                     //!< Divide by 2 (8 MHz)
  #define PWM_PRESCALER_PRESCALER_DIV_4   (2UL)                                     //!< Divide by 4 (4 MHz)
  #define PWM_PRESCALER_PRESCALER_DIV_8   (3UL)                                     //!< Divide by 8 (2 MHz)
  #define PWM_PRESCALER_PRESCALER_DIV_16  (4UL)                                     //!< Divide by 16 (1 MHz)
  #define PWM_PRESCALER_PRESCALER_DIV_32  (5UL)                                     //!< Divide by 32 (500 kHz)
  #define PWM_PRESCALER_PRESCALER_DIV_64  (6UL)                                     //!< Divide by 64 (250 kHz)
  #define PWM_PRESCALER_PRESCALER_DIV_128 (7UL)                                     //!< Divide by 128 (125 kHz)

  // Register: PWM_DECODER
  // Description: Configuration of the decoder

  // Bit 8 : Selects source for advancing the active sequence
  #define PWM_DECODER_MODE_Pos          (8UL)                               //!< Position of MODE field.
  #define PWM_DECODER_MODE_Msk          (0x1UL << PWM_DECODER_MODE_Pos)     //!< Bit mask of MODE field.
  #define PWM_DECODER_MODE_RefreshCount (0UL)                               //!< SEQ[n].REFRESH is used to determine loading internal compare registers
  #define PWM_DECODER_MODE_NextStep     (1UL)                               //!< NEXTSTEP task causes a new value to be loaded to internal compare registers

  // Bits 1..0 : How a sequence is read from RAM and spread to the compare register
  #define PWM_DECODER_LOAD_Pos          (0UL)                             //!< Position of LOAD field.
  #define PWM_DECODER_LOAD_Msk          (0x3UL << PWM_DECODER_LOAD_Pos)   //!< Bit mask of LOAD field.
  #define PWM_DECODER_LOAD_Common       (0UL)                             //!< 1st half word (16-bit) used in all PWM channels 0..3
  #define PWM_DECODER_LOAD_Grouped      (1UL)                             //!< 1st half word (16-bit) used in channel 0..1; 2nd word in channel 2..3
  #define PWM_DECODER_LOAD_Individual   (2UL)                             //!< 1st half word (16-bit) in ch.0; 2nd in ch.1; ...; 4th in ch.3
  #define PWM_DECODER_LOAD_WaveForm     (3UL)                             //!< 1st half word (16-bit) in ch.0; 2nd in ch.1; ...; 4th in COUNTERTOP

  // Register: PWM_LOOP
  // Description: Number of playbacks of a loop

  // Bits 15..0 : Number of playbacks of pattern cycles
  #define PWM_LOOP_CNT_Pos      (0UL)                           //!< Position of CNT field.
  #define PWM_LOOP_CNT_Msk      (0xFFFFUL << PWM_LOOP_CNT_Pos)  //!< Bit mask of CNT field.
  #define PWM_LOOP_CNT_Disabled (0UL)                           //!< Looping disabled (stop at the end of the sequence)

  // Register: PWM_SEQ_PTR
  // Description: Description cluster: Beginning address in RAM of this sequence

  // Bits 31..0 : Beginning address in RAM of this sequence
  #define PWM_SEQ_PTR_PTR_Pos (0UL)                                     //!< Position of PTR field.
  #define PWM_SEQ_PTR_PTR_Msk (0xFFFFFFFFUL << PWM_SEQ_PTR_PTR_Pos)     //!< Bit mask of PTR field.

  // Register: PWM_SEQ_CNT
  // Description: Description cluster: Number of values (duty cycles) in this sequence

  // Bits 14..0 : Number of values (duty cycles) in this sequence
  #define PWM_SEQ_CNT_CNT_Pos       (0UL)                               //!< Position of CNT field.
  #define PWM_SEQ_CNT_CNT_Msk       (0x7FFFUL << PWM_SEQ_CNT_CNT_Pos)   //!< Bit mask of CNT field.
  #define PWM_SEQ_CNT_CNT_Disabled  (0UL)                               //!< Sequence is disabled, and shall not be started as it is empty

  // Register: PWM_SEQ_REFRESH
  // Description: Description cluster: Number of additional PWM periods between samples loaded into compare register

  // Bits 23..0 : Number of additional PWM periods between samples loaded into compare register (load every REFRESH.CNT+1 PWM periods)
  #define PWM_SEQ_REFRESH_CNT_Pos         (0UL)                                       //!< Position of CNT field.
  #define PWM_SEQ_REFRESH_CNT_Msk         (0xFFFFFFUL << PWM_SEQ_REFRESH_CNT_Pos)     //!< Bit mask of CNT field.
  #define PWM_SEQ_REFRESH_CNT_Continuous  (0UL)                                       //!< Update every PWM period

  // Register: PWM_SEQ_ENDDELAY
  // Description: Description cluster: Time added after the sequence

  // Bits 23..0 : Time added after the sequence in PWM periods
  #define PWM_SEQ_ENDDELAY_CNT_Pos (0UL)                                      //!< Position of CNT field.
  #define PWM_SEQ_ENDDELAY_CNT_Msk (0xFFFFFFUL << PWM_SEQ_ENDDELAY_CNT_Pos)   //!< Bit mask of CNT field.

  // Register: PWM_PSEL_OUT
  // Description: Description collection: Output pin select for PWM channel n

  // Bit 31 : Connection
  #define PWM_PSEL_OUT_CONNECT_Pos          (31UL)                                //!< Position of CONNECT field.
  #define PWM_PSEL_OUT_CONNECT_Msk          (0x1UL << PWM_PSEL_OUT_CONNECT_Pos)   //!< Bit mask of CONNECT field.
  #define PWM_PSEL_OUT_CONNECT_Connected    (0UL)                                 //!< Connect
  #define PWM_PSEL_OUT_CONNECT_Disconnected (1UL)                                 //!< Disconnect

  // Bit 5 : Port number
  #define PWM_PSEL_OUT_PORT_Pos (5UL)                                 //!< Position of PORT field.
  #define PWM_PSEL_OUT_PORT_Msk (0x1UL << PWM_PSEL_OUT_PORT_Pos)      //!< Bit mask of PORT field.

  // Bits 4..0 : Pin number
  #define PWM_PSEL_OUT_PIN_Pos (0UL)                                  //!< Position of PIN field.
  #define PWM_PSEL_OUT_PIN_Msk (0x1FUL << PWM_PSEL_OUT_PIN_Pos)       //!< Bit mask of PIN field.

  ///////////////////////////

  // Get the mapped channel of a pin
  int  pin2channel(uint8_t pin) const
  {
    pin = g_ADigitalPinMap[pin];

    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      if ( _pwm->PSEL.OUT[i] == pin )
        return i;
    }

    return (-1);
  }

  // Check if pin is controlled by PWM
  bool checkPin(uint8_t pin) const
  {
    return pin2channel(pin) >= 0;
  }

*************************************/

////////////////////////////////////////

#define INVALID_NRF52_PIN         255

////////////////////////////////////////

#define MAX_COUNT_16BIT           65536UL

#define MAX_16BIT                 65535UL
#define MAX_15BIT                 32768UL

////////////////////////////////////////
////////////////////////////////////////

class nRF52_PWM
{
  public:

    // dutycycle = 0.0f - 100.0f => 0-65535
    nRF52_PWM(const uint32_t& pin, const float& frequency, const float& dutycycle)
    {
      _dutycycle  = round(map(dutycycle, 0, 100.0f, 0, MAX_COUNT_16BIT));

      // create new unique token based on micros()
      NRF52_PWM_TOKEN = (uint32_t) micros();

      PWM_HEXLOGDEBUG1("nRF52_PWM: NRF52_PWM_TOKEN =", NRF52_PWM_TOKEN);

      // input DC is 16-bit
      _PWMEnabled = setupPWM(pin, (uint32_t) frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    ~nRF52_PWM()
    {
      // Release ownership.
      // TODO: how to differentiate we're true owner => using unique token with micros()
      for (int i = 0; i < HWPWM_MODULE_NUM; i++)
      {
        if (HwPWMx[i]->takeOwnership(NRF52_PWM_TOKEN))
        {
          HwPWMx[i]->releaseOwnership(NRF52_PWM_TOKEN);

          return;
        }
      }
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////

  private:

    ///////////////////////////////////////////

    uint32_t calcPrescaler(const float& frequency)
    {
      uint32_t period = 1000000 / frequency;

      // PWM clock is 16MHz
      uint32_t countTOP = 16000000 / frequency;

      //Prescaller : 1, 2, 4, 8, 16, 32, 64, 128 for min 125KHz
      if ( countTOP < MAX_15BIT  )
      {
        // Set prescaler to 1 for 16,000KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_1;
        _prescaler = 1;
      }
      else if ( countTOP < MAX_15BIT * 2 )
      {
        // Set prescaler to 2 for 8,000KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_2;
        _prescaler = 2;
      }
      else if ( countTOP < MAX_15BIT * 4 )
      {
        // Set prescaler to 4 for 4,000KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_4;
        _prescaler = 4;
      }
      else if ( countTOP < MAX_15BIT * 8 )
      {
        // Set prescaler to 8 for 2,000KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_8;
        _prescaler = 8;
      }
      else if ( countTOP < MAX_15BIT * 16 )
      {
        // Set prescaler to 16 for 1,000KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_16;
        _prescaler = 16;
      }
      else if ( countTOP < MAX_15BIT * 32 )
      {
        // Set prescaler to 32 for 500KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_32;
        _prescaler = 32;
      }
      else if ( countTOP < MAX_15BIT * 64 )
      {
        // Set prescaler to 64 for 250KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_64;
        _prescaler = 64;
      }
      else if ( countTOP < MAX_15BIT * 128 )
      {
        // Set prescaler to 128 for 250KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_128;
        _prescaler = 128;
      }
      else
      {
        // Set prescaler to 128 for 250KHz
        _prescalerConfigBits = PWM_PRESCALER_PRESCALER_DIV_128;
        _prescaler = 128;
      }

      _compareValue = ( countTOP / _prescaler ) - 1;

      PWM_LOGDEBUG5(F("calcPrescaler: OK  period ="), period, F(", _prescaler ="), _prescaler,
                    F(", countTOP ="), countTOP);

      PWM_LOGDEBUG7(F("calcPrescaler: _dutycycle ="), _dutycycle, F(", frequency ="), frequency,
                    F(", _prescalerConfigBits ="), _prescalerConfigBits, F(", _compareValue ="), _compareValue);

      return _compareValue;
    }

    ///////////////////////////////////////////

    // input dutycycle is 16-bit. To be mapped to 15 bit
    // TODO: set frequency by calc period + TOP

    // Bad design of HardwarePWM class
    // Must call setMaxValue() to set COUNTERTOP for frequency
    // Never call setResolution() after setMaxValue(), as it will reset COUNTERTOP to max resolution => wrong freq
    // Calculate Prescaler according to freq. Also calculate and call setClockDiv(_prescalerConfigBits)
    bool setupPWM(uint32_t pin, uint32_t frequency, uint16_t dutycycle)
    {
      if (_frequency != frequency)
      {
        // only for new Freq
        calcPrescaler(frequency);
      }

      // Map dutycycle to _compareValue
      uint16_t newDC = round(map(dutycycle, 0, MAX_COUNT_16BIT, 0, _compareValue));

      // Check all PWM modules if pin is the same to use
      for (int i = 0; i < HWPWM_MODULE_NUM; i++)
      {
        if (HwPWMx[i]->isOwner(NRF52_PWM_TOKEN))
        {
          int const ch = HwPWMx[i]->pin2channel(pin);

          if (ch >= 0)
          {
            // KH set 15-bit, then mapped DC to 15-bit
            //HwPWMx[i]->setResolution(_resolution - 1);
            if (_frequency != frequency)
            {
              HwPWMx[i]->setClockDiv(_prescalerConfigBits);
              _frequency = frequency;
            }

            HwPWMx[i]->setMaxValue(_compareValue);

            HwPWMx[i]->writeChannel(ch, newDC);

            PWM_LOGDEBUG5(F("setupPWM: Same _pin ="), _pin, F("to PWM module ="), i, F(", ch ="), ch);
            PWM_LOGDEBUG5(F("setupPWM: dutycycle ="), dutycycle >> 1, F(", frequency ="), frequency, F(", _resolution ="),
                          _resolution - 1);

            return true;
          }
        }
      }

      // Assign a new pin to currently owned PWM module
      for (int i = 0; i < HWPWM_MODULE_NUM; i++)
      {
        if ( HwPWMx[i]->isOwner(NRF52_PWM_TOKEN) && HwPWMx[i]->addPin(pin) )
        {
          // KH set 15-bit, then mapped DC to 15-bit
          //HwPWMx[i]->setResolution(_resolution - 1);
          if (_frequency != frequency)
          {
            HwPWMx[i]->setClockDiv(_prescalerConfigBits);
            _frequency = frequency;
          }

          HwPWMx[i]->setMaxValue(_compareValue);

          _pin = pin;

          HwPWMx[i]->writePin(pin, newDC);

          PWM_LOGDEBUG3(F("setupPWM: Added new pin ="), pin, F("to PWM module ="), i);
          PWM_LOGDEBUG5(F("setupPWM: dutycycle ="), dutycycle >> 1, F(", frequency ="), frequency, F(", _resolution ="),
                        _resolution - 1);

          return true;
        }
      }

      // Try getting and takeOwnership of new HwPWMx instance of PWM module
      // a) Check if no PWM channel has a pin
      // b) the owner token is nullptr
      for (int i = 0; i < HWPWM_MODULE_NUM; i++)
      {
        if (HwPWMx[i]->takeOwnership(NRF52_PWM_TOKEN))
        {
          // apply the current resolution if new ownership
          // KH set 15-bit, then mapped DC to 15-bit
          HwPWMx[i]->setResolution(_resolution - 1);
          HwPWMx[i]->setClockDiv(_prescalerConfigBits);
          HwPWMx[i]->setMaxValue(_compareValue);

          _frequency = frequency;
          _pin       = pin;

          HwPWMx[i]->addPin(pin);
          HwPWMx[i]->writePin(pin, newDC);

          PWM_LOGDEBUG3("setupPWM: pin =", pin, "assigned to new PWM module =", i);
          PWM_LOGDEBUG5(F("setupPWM: dutycycle ="), dutycycle >> 1, F(", frequency ="), frequency, F(", _resolution ="),
                        _resolution - 1);

          return true;
        }
      }

      PWM_LOGDEBUG("setupPWM: No free PWM module");

      return false;
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////

  public:

    // dutycycle from 0-65535 for 0%-100%
    bool setPWM_Int(const uint8_t& pin, const float& frequency, const uint16_t& dutycycle)
    {
      if (pin != _pin)
        return false;

      PWM_LOGINFO3(F("setPWM_Int: dutycycle ="), dutycycle, F(", frequency ="), frequency);

      return setupPWM(pin, (uint32_t) frequency, dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM()
    {
      return setPWM_Int(_pin, _frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM(const uint8_t& pin, const float& frequency, const float& dutycycle)
    {
      _dutycycle = round(map(dutycycle, 0, 100.0f, 0, MAX_COUNT_16BIT));

      PWM_LOGDEBUG3(F("setPWM: _dutycycle ="), _dutycycle, F(", frequency ="), frequency);

      return setPWM_Int(pin, frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM_Period(const uint8_t& pin, const float& period_us, const float& dutycycle)
    {
      _dutycycle = round(map(dutycycle, 0, 100.0f, 0, MAX_COUNT_16BIT));

      PWM_LOGDEBUG3(F("setPWM_Period: _dutycycle ="), _dutycycle, F(", period_us ="), period_us);

      return setPWM_Int(pin, round(1000000.0f / period_us), _dutycycle);
    }

    ///////////////////////////////////////////

    // Must have same frequency
    bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue)
    {
      // Not the same pin or overvalue
      if (_pin != pin)
        return false;

      _dutycycle = DCValue;

      PWM_LOGINFO3(F("setPWM_manual: _dutycycle ="), _dutycycle, F(", frequency ="), _frequency);

      return setupPWM(pin, _frequency, DCValue);
    }

    ///////////////////////////////////////////

    inline float getActualDutyCycle()
    {
      return ( ( (float) _dutycycle + 1 ) * 100 / MAX_16BIT );
    }

    ///////////////////////////////////////////

    inline float getActualFreq()
    {
      return _frequency;
    }

    ///////////////////////////////////////////

    inline float getPWMPeriod()
    {
      return (1000000.0f / _frequency);
    }

    ///////////////////////////////////////////

    inline uint32_t get_freq_CPU()
    {
      return F_CPU;
    }

    ///////////////////////////////////////////

    inline uint32_t getPin()
    {
      return _pin;
    }

    ///////////////////////////////////////////

    void setResolution(const uint8_t& resolution)
    {
      // Must be <= 16-bit and >= 8-bit
      if ( (resolution <= 16) && (resolution >= 8) )
      {
        _resolution = resolution;
      }
    }

    ///////////////////////////////////////////

    bool isPWMEnabled()
    {
      return _PWMEnabled;
    }

    ///////////////////////////////////////////////////////////////////

  private:

    float         _frequency;

    // For PWM frequency COUNTERTOP register
    uint32_t      _compareValue;

    uint32_t      NRF52_PWM_TOKEN = 0;

    uint32_t      _prescalerConfigBits;
    uint16_t      _prescaler = 1;

    // dutycycle from 0-65535 for 0%-100%
    uint16_t       _dutycycle;

    uint8_t       _pin = INVALID_NRF52_PIN;

    // In number of bits
    uint8_t       _resolution = 16;

    bool          _PWMEnabled = false;

    ///////////////////////////////////////////
};

///////////////////////////////////////////


#endif    // NRF52_PWM_H

