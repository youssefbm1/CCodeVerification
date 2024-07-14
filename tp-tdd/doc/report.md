# Report for TDD Exercise

This is the place where you can put your test lists, as well as any additional
explanation or discussion with respect to your implementation.
## TestLightScheduler:
### General Setup and Teardown:

- setUp: Initializes TimeService, LightScheduler, and LightControl.
- tearDown: Destroys LightControl, LightScheduler, and TimeService.
### Scheduling and Event Tests:

- testLightSchedulerWeeklyOnEvent: Schedules a light to turn on every week on a specific day and time, and verifies it turns on at the specified time.
- testLightSchedulerWeeklyOffEvent: Schedules a light to turn off every week on a specific day and time, and verifies it turns off at the specified time.
- testLightSchedulerPreEventState: Schedules a light to turn on at a specific weekly time, and ensures the light state is unchanged before the event occurs.
- testLightSchedulerLightIDWithinRange: Schedules a light to turn on or off with a valid ID (0-255) and checks that the schedule is successfully created.
- testLightSchedulerLightIDBelowRange: Tests the function LightScheduler_scheduleTurnOff with a light ID below the acceptable range and verifies the expected return value.
- testLightSchedulerLightIDOutOfRange: Attempts to schedule a light with an invalid ID (outside 0-255) and ensures the schedule fails.
- testLightSchedulerDailyEvent: Schedules a light to switch on or off every day at a specific time and verifies the TimeService response.
- testLightSchedulerOverlappingEvents: Schedules a light to switch on or off at a precise time and Check that the light is turned off, as off should override on in case of overlap.
- testLightSchedulerMultipleEvents: Schedules events for two different lights and ensures both execute as expected.
- testLightSchedulerWeeklyEvent: Schedules a light to switch on or off every day of the week and checks the TimeService response.
- testLightSchedulerWeekendEvents: Schedules lights to switch on or off during the weekend and verifies the response from TimeService.
- testLightSchedulerCancelSchedule: Tests the cancellation of a scheduled light event and verifies that no operation occurs after cancellation.
- testLightSchedulerRetainLightState: Schedules an event and checks that the light remains in the expected state after some time has passed.
- testLightSchedulerStateAcrossMultipleDays: Schedules a light to turn on on Monday and checks that it remains on when time progresses to Tuesday and Wednesday.

