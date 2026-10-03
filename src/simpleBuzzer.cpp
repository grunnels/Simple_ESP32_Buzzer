/******************************************************************************
 *
 * SimpleBuzzer - see simpleBuzzer.h
 *
 * Written by Greg Runnels
 *
 ******************************************************************************/

#include <Arduino.h>
#include <SerialPrints.h>
#include "simpleBuzzer.h"

#ifndef BUZZER_QUEUE_LENGTH
#define BUZZER_QUEUE_LENGTH 8   // patterns waiting to play; more are dropped
#endif
#ifndef BUZZER_TASK_STACK
#define BUZZER_TASK_STACK 2048
#endif

static int buzzerPin = -1;          // -1 = setupBuzzer() not called yet: do nothing
static uint8_t onLevel = HIGH;
// Not saved anywhere, so every boot starts unmuted - unless the build has
// -D SILENCE_BUZZER (bench units), or setMuteBuzzer(true) is called, before
// or after setupBuzzer().
#ifdef SILENCE_BUZZER
static volatile bool muted = true;
#else
static volatile bool muted = false;
#endif

static void pinOff()
{
    if (buzzerPin >= 0)
        digitalWrite(buzzerPin, onLevel == HIGH ? LOW : HIGH);
}

static void pinOn()
{
    if (buzzerPin >= 0)
        digitalWrite(buzzerPin, onLevel);
}

// #m toggles, #m1 mutes, #m0 unmutes
static void muteCommand(const char *value)
{
    if (value && value[0] == '1')
        setMuteBuzzer(true);
    else if (value && value[0] == '0')
        setMuteBuzzer(false);
    else
        setMuteBuzzer(!muted);
    Serial.println(muted ? "Buzzer muted" : "Buzzer on");
}

#ifdef ESP_PLATFORM
// ---- ESP32: a small task plays the patterns -----------------------------------
struct BeepPattern
{
    uint16_t duration;
    uint16_t count;
};
static QueueHandle_t queue = nullptr;
static volatile uint32_t stopCount = 0;   // stopBuzzer() bumps it; a pattern started before stops

static void buzzerTask(void *)
{
    BeepPattern p;
    for (;;)
    {
        if (xQueueReceive(queue, &p, portMAX_DELAY) != pdTRUE)
            continue;
        uint32_t startedAt = stopCount;
        for (int i = 0; i < p.count && !muted && stopCount == startedAt; i++)
        {
            pinOn();
            vTaskDelay(pdMS_TO_TICKS(p.duration));
            pinOff();
            vTaskDelay(pdMS_TO_TICKS(p.duration));
        }
        pinOff();
    }
}

void soundTheBuzzer(int duration, int count)
{
    if (muted || buzzerPin < 0 || !queue || count <= 0 || duration <= 0)
        return;
    BeepPattern p = {(uint16_t)duration, (uint16_t)count};
    xQueueSend(queue, &p, 0);   // never wait - if 8 are already queued, skip this one
}

static void startPlayer()
{
    if (queue)
        return;
    queue = xQueueCreate(BUZZER_QUEUE_LENGTH, sizeof(BeepPattern));
    if (queue)
        xTaskCreate(buzzerTask, "buzzer", BUZZER_TASK_STACK, nullptr, 1, nullptr);
}

static void clearQueued()
{
    if (queue)
        xQueueReset(queue);
    stopCount = stopCount + 1;   // the pattern playing right now stops after its current beep
}

#else
// ---- Other boards: plays straight away (blocking), as before -------------------
void soundTheBuzzer(int duration, int count)
{
    if (muted || buzzerPin < 0)
        return;
    for (int i = 0; i < count && !muted; i++)
    {
        pinOn();
        delay(duration);
        pinOff();
        delay(duration);
    }
}
static void startPlayer() {}
static void clearQueued() {}
#endif

// ---------------------------------------------------------------------------
void setupBuzzer(int pin, bool activeHigh)
{
    buzzerPin = pin;
    onLevel = activeHigh ? HIGH : LOW;
    // (mute is left as it is - a setMuteBuzzer(true) before this still counts)
    pinMode(buzzerPin, OUTPUT);
    pinOff();
    startPlayer();
    addStandardMenuItem(SP_KEY_MUTE, muteCommand);
    soundTheBuzzerShort(7);   // "I'm alive" - plays in the background
}

void soundTheBuzzerShort(int count) { soundTheBuzzer(50, count); }
void soundTheBuzzerLong(int count) { soundTheBuzzer(150, count); }

void stopBuzzer()
{
    clearQueued();
    pinOff();
}

void setMuteBuzzer(bool mute)
{
    muted = mute;
    if (muted)
    {
        clearQueued();   // drop anything waiting; the task stops mid-pattern
        pinOff();
    }
    else
    {
        soundTheBuzzerShort(3);
    }
}

bool isBuzzerMuted() { return muted; }
