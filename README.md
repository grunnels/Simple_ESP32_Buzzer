

# SimpleBuzzer

Library for Buzzer control on ESP32.


## Description

### Initial setup

Assumes that the buzzer will sound when the GPIO pin is pulled high


## Interface

#include "simpleBuzzer.h"


### Constructor

- **void setupBuzzer(int buzzerPin)** Initializes the buzzer with the given GPIO pin
mandatory GPIO pin

### Buzzer Control


- **vvoid soundTheBuzzerShort(int count = 1)** Sounds buzzer for 50ms count times, default is 1
- **vvoid soundTheBuzzerLong(int count = 1)** Sound the buzzer for 150ms count times, default is 1
- **vvoid soundTheBuzzer(int duration, int count)** Sound the buzzer for duration ms count times
- **vvoid setMuteBuzzer(bool mute)** mute or unmute the buzzer
- **vbool isBuzzerMuted()** checks current status of buzzer mute


## Future

#### Must

- update documentation

#### Should


#### Wont (for now).

- support platforms other than ESP32


## Support

If you have questions or suggestions, please reach out to me.

Thank you
# Simple_ESP32_Buzzer
