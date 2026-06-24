/******************************************************************************
 *
 * This is a library for LED's on an ESP32
 *
 *
 * Feel free to use or change it
 *
 * Please let me know if you find any bugs
 *
 * Written by Greg Runnels
 *
 *
 ******************************************************************************/

#ifndef SIMPLE_BUZZER_H
#define SIMPLE_BUZZER_H   

void setupBuzzer(int buzzerPin);
void soundTheBuzzerShort(int count = 1);
void soundTheBuzzerLong(int count = 1);
void soundTheBuzzer(int duration, int count);
void setMuteBuzzer(bool mute);
bool isBuzzerMuted();

#endif
