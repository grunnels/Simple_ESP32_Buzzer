# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-10-03
- Beeps play in a background task - soundTheBuzzer...() returns at once (setup no longer waits ~1 s)
- Muting stops a pattern that's already playing and drops queued ones
- Mute isn't remembered across reboots (starts unmuted), except with -D SILENCE_BUZZER, which starts muted;
  setMuteBuzzer(true) before setupBuzzer() is kept
- setupBuzzer(pin, activeHigh) - active-low buzzers supported
- Adds the standard 'M' serial command (#m toggle, #m1 mute, #m0 unmute) - needs SerialPrints 1.0.0
- Library variables made private; does nothing if setupBuzzer() wasn't called

## [0.3.0] - 2026-04-30
- initial version
