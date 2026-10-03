# SimpleBuzzer

A buzzer on an ESP32. Beeps play in the background, so sounding an alarm never holds up
the task that asked for it.

```cpp
#include "simpleBuzzer.h"

setupBuzzer(BUZZER_PIN);          // sounds when the pin is HIGH; setupBuzzer(pin, false) for active-low
soundTheBuzzerShort(3);           // three 50 ms beeps
soundTheBuzzerLong();             // one 150 ms beep
soundTheBuzzer(300, 2);           // two 300 ms beeps
setMuteBuzzer(true);              // stops anything playing; unmuting beeps 3 times
isBuzzerMuted();
```

- Always starts unmuted after a reboot.
- Up to 8 patterns wait their turn; more than that are skipped.
- `setupBuzzer()` adds the standard **M** serial command: `#m` toggles, `#m1` mutes, `#m0` unmutes.
  Needs SerialPrints 1.0.0 in `lib_deps`.
