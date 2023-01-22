# nRF52_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/nRF52_PWM.svg?)](https://www.ardu-badge.com/nRF52_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/nRF52_PWM.svg)](https://github.com/khoih-prog/nRF52_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/nRF52_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/nRF52_PWM.svg)](http://github.com/khoih-prog/nRF52_PWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Why do we need this nRF52_PWM library](#why-do-we-need-this-nRF52_PWM-library)
  * [Features](#features)
  * [Why using hardware-based PWM is better](#why-using-hardware-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Seeeduino nRF52840 boards](#2-for-Seeeduino-nRF52840-boards)
* [Usage](#usage)
  * [1. Create PWM Instance with Pin, Frequency, dutycycle](#1-create-pwm-instance-with-pin-frequency-dutycycle)
  * [2. Initialize PWM Instance](#2-Initialize-PWM-Instance)
  * [3. Set or change PWM frequency or dutyCycle](#3-set-or-change-PWM-frequency-or-dutyCycle)
  * [4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation](#4-Set-or-change-PWM-frequency-and-dutyCycle-manually-and-efficiently-in-waveform-creation)
* [Examples](#examples)
  * [ 1. PWM_Basic](examples/PWM_Basic)
  * [ 2. PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle) 
  * [ 3. PWM_DynamicDutyCycle_Int](examples/PWM_DynamicDutyCycle_Int)
  * [ 4. PWM_DynamicFreq](examples/PWM_DynamicFreq)
  * [ 5. PWM_Multi](examples/PWM_Multi)
  * [ 6. PWM_MultiChannel](examples/PWM_MultiChannel)
  * [ 7. PWM_Waveform](examples/PWM_Waveform)
  * [ 8. PWM_StepperControl](examples/PWM_StepperControl) **New**
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. PWM_DynamicDutyCycle on NRF52840_FEATHER](#1-PWM_DynamicDutyCycle-on-NRF52840_FEATHER)
  * [2. PWM_Multi on NRF52840_FEATHER](#2-PWM_Multi-on-NRF52840_FEATHER)
  * [3. PWM_DynamicFreq on NRF52840_FEATHER](#3-PWM_DynamicFreq-on-NRF52840_FEATHER)
  * [4. PWM_Waveform on NRF52840_FEATHER](#4-PWM_Waveform-on-NRF52840_FEATHER)
  * [5. PWM_Waveform on NRF52840_ITSYBITSY](#5-PWM_Waveform-on-NRF52840_ITSYBITSY)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---


### Why do we need this [nRF52_PWM library](https://github.com/khoih-prog/nRF52_PWM)

### Features

This hardware-based PWM library enables you to use Hardware-PWM on **nRF52-based boards, such as AdaFruit Itsy-Bitsy nRF52840, Feather nRF52840 Express, Seeed XIAO nRF52840, Seeed XIAO nRF52840 Sense**, to create and output PWM. These purely hardware-based PWM channels can generate very high PWM frequencies, depending on CPU clock and acceptable accuracy. The maximum and default resolution is **16-bit** resolution.

This library is using the **same or similar functions** as other FastPWM libraries, as follows, to enable you to **port your PWM code easily between platforms**

 1. [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM)
 2. [**AVR_PWM**](https://github.com/khoih-prog/AVR_PWM)
 3. [**megaAVR_PWM**](https://github.com/khoih-prog/megaAVR_PWM)
 4. [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM)
 5. [**SAMD_PWM**](https://github.com/khoih-prog/SAMD_PWM)
 6. [**SAMDUE_PWM**](https://github.com/khoih-prog/SAMDUE_PWM)
 7. [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM)
 8. [**Teensy_PWM**](https://github.com/khoih-prog/Teensy_PWM)
 9. [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM)
10. [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM)
11. [**Portenta_H7_PWM**](https://github.com/khoih-prog/Portenta_H7_PWM)
12. [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM)
13. [**nRF52_MBED_PWM**](https://github.com/khoih-prog/nRF52_MBED_PWM)
14. [**STM32_PWM**](https://github.com/khoih-prog/STM32_PWM)

---

The most important feature is they're purely hardware-based PWM channels. Therefore, their operations are **not blocked by bad-behaving software functions / tasks**.

This important feature is absolutely necessary for mission-critical tasks. These hardware PWM-channels, still work even if other software functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software timers using `millis()` or `micros()`. That's necessary if you need to control external systems (Servo, etc.) requiring better accuracy.

New efficient `setPWM_manual()` function enables waveform creation using PWM.

The [**PWM_Multi**](examples/PWM_Multi) example will demonstrate the usage of multichannel PWM using multiple Hardware-PWM blocks (Timer & Channel). The 4 independent Hardware-PWM channels are used **to control 4 different PWM outputs**, with totally independent frequencies and dutycycles on `nRF52`.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

---

### Why using hardware-based PWM is better

Imagine you have a system with a **mission-critical** function, controlling a robot or doing something much more important. You normally use a software timer to poll, or even place the function in `loop()`. But what if another function is **blocking** the `loop()` or `setup()`.

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use `hardware-based PWM`.

These hardware-based PWM channels still work even if other software functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software-based PWMs, using `millis()` or `micros()`.

Functions using normal software-based PWMs, relying on `loop()` and calling `millis()`, won't work if the `loop()` or `setup()` is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

---

### Currently supported Boards

1. **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox etc.**
2. **Sparkfun Pro nRF52840 Mini**
3. **Seeeduino nRF52840-based boards such as SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeeduino `nRF52` core


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 3. [`Seeeduino nRF52 core 1.1.0+`](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino) for Seeeduino nRF52840-based boards such as **Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE**. [![GitHub release](https://img.shields.io/github/release/Seeed-Studio/Adafruit_nRF52_Arduino.svg)](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino/releases/latest)

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/nRF52_PWM.svg?)](https://www.ardu-badge.com/nRF52_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM) page.
2. Download the latest release `nRF52_PWM-main.zip`.
3. Extract the zip file to `nRF52_PWM-main` directory 
4. Copy whole `nRF52_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**nRF52_PWM** library](https://registry.platformio.org/libraries/khoih-prog/nRF52_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/nRF52_PWM/installation). Search for **nRF52_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 1.3.0](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

---

#### 2. For Seeeduino nRF52840 boards

**To be able to compile and run on Xiao nRF52840 boards**, you have to copy the whole [nRF52 1.0.0](Packages_Patches/Seeeduino/hardware/nrf52/1.0.0) directory into Seeeduino nRF52 directory (~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0). 

Supposing the Seeeduino nRF52 version is 1.0.0. These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**


---

To use `Sparkfun Pro nRF52840 Mini`, you must install `Packages_Patches` and use Adafruit nrf52 core v1.0.0+

---
---


## Usage

Before using any PWM `Timer` and `channel`, you have to make sure the `Timer` and `channel` has not been used by any other purpose.

```cpp
// OK for Feather_nRF52840_Express   (5, 6, 9-13, 14-21/A0-A7, etc.)
// OK for ItsyBitsy_nRF52840_Express (5, 7, 9-13, 14-20/A0-A6, etc.)
```

#### 1. Create PWM Instance with Pin, Frequency, dutycycle

```cpp
nRF52_PWM* PWM_Instance;

PWM_Instance = new nRF52_PWM(pinToUse, frequency, dutyCycle, channel, PWM_resolution);
```

#### 2. Initialize PWM Instance

```cpp
if (PWM_Instance)
{
  PWM_Instance->setPWM();
}
```

#### 3. Set or change PWM frequency or dutyCycle

To use `float new_dutyCycle`

```cpp
PWM_Instance->setPWM(PWM_Pins, new_frequency, new_dutyCycle);
```

such as 

```cpp
dutyCycle = 10.0f;
  
Serial.print(F("Change PWM DutyCycle to ")); Serial.println(dutyCycle);
PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);
```

---

To use `uint32_t new_dutyCycle` = `(real_dutyCycle * 65536) / 100`


```cpp
PWM_Instance->setPWM_Int(PWM_Pins, new_frequency, new_dutyCycle);
```

such as for `real_dutyCycle = 50%`

```cpp
// 50% dutyCycle = (real_dutyCycle * 65536) / 100
dutyCycle = 32768;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

for `real_dutyCycle = 50%`

```cpp
// 20% dutyCycle = (real_dutyCycle * 65536) / 100
dutyCycle = 13107;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

#### 4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation

Function prototype

```cpp
bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue);
```

Need to call only once for each pin


```cpp
PWM_Instance->setPWM(PWM_Pins, frequency, dutyCycle);
```

after that, if just changing `dutyCycle` / `level`, use 

```cpp
PWM_Instance->setPWM_manual(PWM_Pins, new_level);
```

---
---

### Examples: 

 1. [PWM_Basic](examples/PWM_Basic)
 2. [PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle)
 3. [PWM_DynamicDutyCycle_Int](examples/PWM_DynamicDutyCycle_Int)
 4. [PWM_DynamicFreq](examples/PWM_DynamicFreq)
 5. [PWM_Multi](examples/PWM_Multi)
 6. [PWM_MultiChannel](examples/PWM_MultiChannel)
 7. [PWM_Waveform](examples/PWM_Waveform)
 8. [PWM_StepperControl](examples/PWM_StepperControl) **New**

 
---
---

### Example [PWM_Multi](examples/PWM_Multi)

https://github.com/khoih-prog/nRF52_PWM/blob/2384153e52548f3af06b71bfd996fa96bb338ee0/examples/PWM_Multi/PWM_Multi.ino#L1-L102


---
---

### Debug Terminal Output Samples

### 1. PWM_DynamicDutyCycle on NRF52840_FEATHER

The following is the sample terminal output when running example [PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle) on **NRF52840_FEATHER**, to demonstrate the ability to provide high PWM frequencies and ability to change DutyCycle `on-the-fly`


```cpp
Starting PWM_DynamicDutyCycle on NRF52840_FEATHER
nRF52_PWM v1.0.1
[PWM] nRF52_PWM: NRF52_PWM_TOKEN = 0x345CD8
[PWM] calcPrescaler: OK  period = 200 , _prescaler = 1 , countTOP = 3200
[PWM] calcPrescaler: _dutycycle = 0 , frequency = 5000.00 , _prescalerConfigBits = 0 , _compareValue = 3199
[PWM] setupPWM: pin = 6 assigned to new PWM module = 0
[PWM] setupPWM: dutycycle = 0 , frequency = 5000 , _resolution = 15
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58982 , frequency = 5000.00
[PWM] setPWM_Int: dutycycle = 58982 , frequency = 5000.00
[PWM] setupPWM: Same _pin = 6 to PWM module = 0 , ch = 0
[PWM] setupPWM: dutycycle = 29491 , frequency = 5000 , _resolution = 15
=====================================================================================
Actual data: pin = 6, PWM DC = 90.00, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 20.00
[PWM] setPWM: _dutycycle = 13107 , frequency = 5000.00
[PWM] setPWM_Int: dutycycle = 13107 , frequency = 5000.00
[PWM] setupPWM: Same _pin = 6 to PWM module = 0 , ch = 0
[PWM] setupPWM: dutycycle = 6553 , frequency = 5000 , _resolution = 15
=====================================================================================
Actual data: pin = 6, PWM DC = 20.00, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58982 , frequency = 5000.00
[PWM] setPWM_Int: dutycycle = 58982 , frequency = 5000.00
[PWM] setupPWM: Same _pin = 6 to PWM module = 0 , ch = 0
[PWM] setupPWM: dutycycle = 29491 , frequency = 5000 , _resolution = 15
=====================================================================================
Actual data: pin = 6, PWM DC = 90.00, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
```

---

### 2. PWM_Multi on NRF52840_FEATHER

The following is the sample terminal output when running example [**PWM_Multi**](examples/PWM_Multi) on **NRF52840_FEATHER**, to demonstrate the ability to provide high PWM frequencies on multiple `PWM-capable` pins

```cpp
Starting PWM_Multi on NRF52840_FEATHER
nRF52_PWM v1.0.1
[PWM] nRF52_PWM: NRF52_PWM_TOKEN = 0x389838
[PWM] calcPrescaler: OK  period = 500 , _prescaler = 1 , countTOP = 8000
[PWM] calcPrescaler: _dutycycle = 6553 , frequency = 2000.00 , _prescalerConfigBits = 0 , _compareValue = 7999
[PWM] setupPWM: pin = 5 assigned to new PWM module = 0
[PWM] setupPWM: dutycycle = 3276 , frequency = 2000 , _resolution = 15
[PWM] setPWM_Int: dutycycle = 6553 , frequency = 2000.00
[PWM] setupPWM: Same _pin = 5 to PWM module = 0 , ch = 0
[PWM] setupPWM: dutycycle = 3276 , frequency = 2000 , _resolution = 15
[PWM] nRF52_PWM: NRF52_PWM_TOKEN = 0x389FD9
[PWM] calcPrescaler: OK  period = 333 , _prescaler = 1 , countTOP = 5333
[PWM] calcPrescaler: _dutycycle = 19660 , frequency = 3000.00 , _prescalerConfigBits = 0 , _compareValue = 5332
[PWM] setupPWM: pin = 6 assigned to new PWM module = 1
[PWM] setupPWM: dutycycle = 9830 , frequency = 3000 , _resolution = 15
[PWM] setPWM_Int: dutycycle = 19660 , frequency = 3000.00
[PWM] setupPWM: Same _pin = 6 to PWM module = 1 , ch = 0
[PWM] setupPWM: dutycycle = 9830 , frequency = 3000 , _resolution = 15
[PWM] nRF52_PWM: NRF52_PWM_TOKEN = 0x38A77A
[PWM] calcPrescaler: OK  period = 250 , _prescaler = 1 , countTOP = 4000
[PWM] calcPrescaler: _dutycycle = 32768 , frequency = 4000.00 , _prescalerConfigBits = 0 , _compareValue = 3999
[PWM] setupPWM: pin = 9 assigned to new PWM module = 2
[PWM] setupPWM: dutycycle = 16384 , frequency = 4000 , _resolution = 15
[PWM] setPWM_Int: dutycycle = 32768 , frequency = 4000.00
[PWM] setupPWM: Same _pin = 9 to PWM module = 2 , ch = 0
[PWM] setupPWM: dutycycle = 16384 , frequency = 4000 , _resolution = 15
[PWM] nRF52_PWM: NRF52_PWM_TOKEN = 0x38B2EC
[PWM] calcPrescaler: OK  period = 125 , _prescaler = 1 , countTOP = 2000
[PWM] calcPrescaler: _dutycycle = 58982 , frequency = 8000.00 , _prescalerConfigBits = 0 , _compareValue = 1999
[PWM] setupPWM: pin = 10 assigned to new PWM module = 3
[PWM] setupPWM: dutycycle = 29491 , frequency = 8000 , _resolution = 15
[PWM] setPWM_Int: dutycycle = 58982 , frequency = 8000.00
[PWM] setupPWM: Same _pin = 10 to PWM module = 3 , ch = 0
[PWM] setupPWM: dutycycle = 29491 , frequency = 8000 , _resolution = 15
=====================================================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=====================================================================================
0	5	2000.00		10.00		2000.0000
1	6	3000.00		30.00		3000.0000
2	9	4000.00		50.00		4000.0000
3	10	8000.00		90.00		8000.0000
=====================================================================================
Actual data: pin = 5, PWM DC = 10.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 6, PWM DC = 30.00, PWMPeriod = 333.33, PWM Freq (Hz) = 3000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 9, PWM DC = 50.00, PWMPeriod = 250.00, PWM Freq (Hz) = 4000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 10, PWM DC = 90.00, PWMPeriod = 125.00, PWM Freq (Hz) = 8000.0000
=====================================================================================
```

---

### 3. PWM_DynamicFreq on NRF52840_FEATHER

The following is the sample terminal output when running example [**PWM_DynamicFreq**](examples/PWM_DynamicFreq) on **NRF52840_FEATHER**, to demonstrate the ability to change dynamically PWM frequencies

```cpp
Starting PWM_DynamicFreq on NRF52840_FEATHER
nRF52_PWM v1.0.1
[PWM] nRF52_PWM: NRF52_PWM_TOKEN = 0x2B8A8B
[PWM] calcPrescaler: OK  period = 100 , _prescaler = 1 , countTOP = 1600
[PWM] calcPrescaler: _dutycycle = 32768 , frequency = 10000.00 , _prescalerConfigBits = 0 , _compareValue = 1599
[PWM] setupPWM: pin = 6 assigned to new PWM module = 0
[PWM] setupPWM: dutycycle = 16384 , frequency = 10000 , _resolution = 15
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 20000.00
[PWM] setPWM_Int: dutycycle = 32768 , frequency = 20000.00
[PWM] calcPrescaler: OK  period = 50 , _prescaler = 1 , countTOP = 800
[PWM] calcPrescaler: _dutycycle = 32768 , frequency = 20000.00 , _prescalerConfigBits = 0 , _compareValue = 799
[PWM] setupPWM: Same _pin = 6 to PWM module = 0 , ch = 0
[PWM] setupPWM: dutycycle = 16384 , frequency = 20000 , _resolution = 15
=====================================================================================
Actual data: pin = 6, PWM DC = 50.00, PWMPeriod = 50.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
Change PWM Freq to 10000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 10000.00
[PWM] setPWM_Int: dutycycle = 32768 , frequency = 10000.00
[PWM] calcPrescaler: OK  period = 100 , _prescaler = 1 , countTOP = 1600
[PWM] calcPrescaler: _dutycycle = 32768 , frequency = 10000.00 , _prescalerConfigBits = 0 , _compareValue = 1599
[PWM] setupPWM: Same _pin = 6 to PWM module = 0 , ch = 0
[PWM] setupPWM: dutycycle = 16384 , frequency = 10000 , _resolution = 15
=====================================================================================
Actual data: pin = 6, PWM DC = 50.00, PWMPeriod = 100.00, PWM Freq (Hz) = 10000.0000
=====================================================================================
```

---


### 4. PWM_Waveform on NRF52840_FEATHER

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **NRF52840_FEATHER**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on NRF52840_FEATHER
nRF52_PWM v1.0.1
[PWM] setPWM_Int: dutycycle = 0 , frequency = 2000.00
============================================================================================
Actual data: pin = 6, PWM DutyCycle = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
============================================================================================
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 65535 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
```


---

### 5. PWM_Waveform on NRF52840_ITSYBITSY

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **NRF52840_ITSYBITSY**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on NRF52840_ITSYBITSY
nRF52_PWM v1.0.1
[PWM] setPWM_Int: dutycycle = 0 , frequency = 2000.00
============================================================================================
Actual data: pin = 7, PWM DutyCycle = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
============================================================================================
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 65535 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [nRF52_PWM issues](https://github.com/khoih-prog/nRF52_PWM/issues)

---
---

## TO DO

1. Search for bug and improvement.
2. Similar features for remaining Arduino boards

---

## DONE

 1. Basic hardware PWM-channels for **nRF52-based boards, such as AdaFruit Itsy-Bitsy nRF52840, Feather nRF52840 Express, Seeed XIAO nRF52840, Seeed XIAO nRF52840 Sense**, etc. using 
 - [`Adafruit nRF52 core`](https://github.com/adafruit/Adafruit_nRF52_Arduino) or 
 - [`Seeeduino nRF52 core`](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino)
 2. Add example [PWM_StepperControl](https://github.com/khoih-prog/nRF52_PWM/tree/main/examples/PWM_StepperControl) to demo how to control Stepper Motor using PWM
 
 
---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [Paul van Dinther](https://github.com/dinther) for proposing new way to use PWM to drive Stepper-Motor in [Using PWM to step a stepper driver #16](https://github.com/khoih-prog/RP2040_PWM/issues/16), leading to v2.0.3


<table>
  <tr>
    <td align="center"><a href="https://github.com/dinther"><img src="https://github.com/dinther.png" width="100px;" alt="dinther"/><br /><sub><b>Paul van Dinther</b></sub></a><br /></td>
  </tr>
</table>


---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/nRF52_PWM/blob/main/LICENSE)

---

## Copyright

Copyright (c) 2022- Khoi Hoang


