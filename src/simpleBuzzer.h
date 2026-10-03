/******************************************************************************
 *
 * SimpleBuzzer - a buzzer on an ESP32
 *
 * Beeps play in the background: soundTheBuzzer...() returns at once, so the
 * task that sounds an alarm is never held up. Muting stops a pattern that is
 * already playing. Mute isn't remembered: every boot starts unmuted, except
 * with the build flag -D SILENCE_BUZZER (bench units), which starts muted.
 * setMuteBuzzer() works before or after setupBuzzer().
 *
 * setupBuzzer() also adds the standard 'M' command to the serial menu
 * (#m toggles, #m1 mutes, #m0 unmutes) - needs SerialPrints.
 *
 * Written by Greg Runnels
 *
 ******************************************************************************/

#ifndef SIMPLE_BUZZER_H
#define SIMPLE_BUZZER_H

// activeHigh = true: the buzzer sounds when the pin is HIGH (the usual wiring)
void setupBuzzer(int buzzerPin, bool activeHigh = true);
void soundTheBuzzerShort(int count = 1);          // 50 ms beeps
void soundTheBuzzerLong(int count = 1);           // 150 ms beeps
void soundTheBuzzer(int duration, int count);     // duration ms on, duration ms off, count times
void setMuteBuzzer(bool mute);                    // unmuting beeps 3 times
bool isBuzzerMuted();

#endif
