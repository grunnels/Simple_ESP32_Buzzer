# SimpleBuzzer

A buzzer on an ESP32. Beeps play in the background, so sounding an alarm never holds up
the task that asked for it.

```cpp
#include "simpleBuzzer.h"

setupBuzzer(BUZZER_PIN);          // sounds when the pin is HIGH; setupBuzzer(pin, false) for active-low
soundTheBuzzerShort(3);           // three 50 ms beeps
soundTheBuzzerLong();             // one 150 ms beep
soundTheBuzzer(300, 2);           // two 300 ms beeps
stopBuzzer();                     // stop what's playing now - mute is NOT changed
setMuteBuzzer(true);              // mute (a setting): stops anything playing; unmuting beeps 3 times
isBuzzerMuted();
```

- Mute isn't remembered: every boot starts unmuted. Build with `-D SILENCE_BUZZER` (bench units) to start muted,
  or call `setMuteBuzzer(true)` - before or after `setupBuzzer()`, either works.
- Up to 8 patterns wait their turn; more than that are skipped.
- `setupBuzzer()` adds the standard **M** serial command: `#m` toggles, `#m1` mutes, `#m0` unmutes.
  Needs SerialPrints 1.0.0 in `lib_deps`.

Acknowledging an alarm should call `stopBuzzer()`, not mute: mute is a setting you choose (`#m`),
not something alarm states change.
