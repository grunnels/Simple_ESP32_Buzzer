/******************************************************************************
 *
 * This is a library for a Buzzer on an ESP32
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

#include <Arduino.h>
#include "simpleBuzzer.h"

bool muteBuzzer = false;
int BUZZER_PIN = -1;

void setupBuzzer(int buzzerPin)
{
  BUZZER_PIN = buzzerPin;
  // println(__func__);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer - pin as an output
  digitalWrite(BUZZER_PIN, LOW);
  delay(250);
  soundTheBuzzerShort(7);
  delay(250);
}

void soundTheBuzzerShort(int count)
{
  soundTheBuzzer(50, count);
}

void soundTheBuzzerLong(int count)
{
  soundTheBuzzer(150, count);
}

void setMuteBuzzer(bool mute)
{
  muteBuzzer = mute;
  if (!muteBuzzer)
  {
    soundTheBuzzerShort(3);
  }
}

bool isBuzzerMuted()
{
  return muteBuzzer;
}

void soundTheBuzzer(int duration, int count)
{
   // println("sounding buzzer");
  if (muteBuzzer)
  {
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }
  for (int i = 0; i < count; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
    delay(duration);
  }
}
