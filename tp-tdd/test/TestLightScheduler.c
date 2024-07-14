/**
 * @file TestLightScheduler.c
 * @brief Unit tests for the LightScheduler module.
 *
 * This file contains the unit tests for the LightScheduler module.
 * It tests the functionality of scheduling turn-on and turn-off events for lights
 * at specific times and days of the week.
 */

#include "LightScheduler.h"
#include "MockTimeService.h"
#include "LightControlSpy.h"
#include "unity.h"

static int schedulerID;

void setUp(void)
{
    TimeService_init_Expect();
    TimeService_destroy_Expect();
    TimeService_startPeriodicAlarm_ExpectAndReturn(60, LightScheduler_trigger, 0);
    TimeService_stopPeriodicAlarm_Expect(0);
    TimeService_init();
    LightControl_init();
    schedulerID = LightScheduler_initialize();
}

void tearDown(void)
{
    LightScheduler_terminate(schedulerID);
    LightControl_destroy();
    TimeService_destroy();
}

void testLightSchedulerWeeklyOnEvent(void)
{
    // Define the time for the event (Friday at 11:40 AM)
    Time time = { .dayOfWeek = FRIDAY, .minuteOfDay = 700 };

    // Schedule the turn-on event for light ID 6 at the specified time
    LightScheduler_scheduleTurnOn(6, time);

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);

    // Trigger the LightScheduler to process scheduled events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Assert that the last controlled light ID is 6 and it is turned on
    TEST_ASSERT_EQUAL_INT(6, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);
}

void testLightSchedulerWeeklyOffEvent(void)
{
    // Define the time for the event (Tuesday at 3:20 AM)
    Time time = { .dayOfWeek = TUESDAY, .minuteOfDay = 200 };

    // Schedule the turn-off event for light ID 5 at the specified time
    LightScheduler_scheduleTurnOff(5, time);

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);

    // Trigger the LightScheduler to process scheduled events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Assert that the last controlled light ID is 5 and it is turned off
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, state);
}

void testLightSchedulerPreEventState(void)
{
    // Define the time for the scheduled event (Monday at 12:00 PM)
    Time time = { .dayOfWeek = MONDAY, .minuteOfDay = 1200 };

    // Schedule the turn-on event for light ID 3 at the specified time
    LightScheduler_scheduleTurnOn(3, time);

    // Set time to just before the scheduled event (Monday at 11:00 AM)
    time.minuteOfDay = 1100;

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);

    // Trigger the LightScheduler to process scheduled events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Assert that the last controlled light ID and state are unknown
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, state);
}

void testLightSchedulerLightIDWithinRange(void)
{
    // Define the initial time for scheduling events (Monday at 12:00 PM)
    Time time = { .dayOfWeek = MONDAY, .minuteOfDay = 1200 };

    // Iterate over light IDs from 0 to 255
    for (int i = 0; i < 256; i++)
    {
        // Set the minuteOfDay field of time to 1200 + i for each iteration
        time.minuteOfDay = 1200 + i;

        // Schedule a turn-off event for the current light ID at the current time
        TEST_ASSERT_EQUAL_INT(0, LightScheduler_scheduleTurnOff(i, time));
    }
}

void testLightSchedulerLightIDBelowRange(void){
    // Define the time for the event (Monday at 12:00 PM)
    Time time = { .dayOfWeek = MONDAY, .minuteOfDay = 1200 };

    // Attempt to schedule a turn-off event with a light ID below the valid range (-1)
    TEST_ASSERT_EQUAL_INT(-1, LightScheduler_scheduleTurnOff(-1, time));
}

void testLightSchedulerLightIDOutOfRange(void)
{
    // Define the time for the event (Monday at 12:00 PM)
    Time time = { .dayOfWeek = MONDAY, .minuteOfDay = 1200 };

    // Attempt to schedule turn-off events with out-of-range light IDs
    TEST_ASSERT_EQUAL_INT(-1, LightScheduler_scheduleTurnOff(257, time)); // Should fail for ID 257
    TEST_ASSERT_EQUAL_INT(-1, LightScheduler_scheduleTurnOn(-10, time));  // Should fail for ID -10

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);

    // Trigger the LightScheduler to process scheduled events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Assert that the last controlled light ID and state are unknown
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, state);
}

void testLightSchedulerDailyEvent(void)
{
    // Define the time for scheduling events (every day at 12:00 PM)
    Time time = { .dayOfWeek = EVERYDAY, .minuteOfDay = 1200 };

    // Schedule turn-on event for light ID 10 at 12:00 PM every day
    LightScheduler_scheduleTurnOn(10, time);

    // Update time for scheduling turn-off event at 3:00 PM every day
    time.minuteOfDay = 1500;
    LightScheduler_scheduleTurnOff(10, time);

    int id;
    int state;

    // Iterate through each day of the week (Monday to Sunday)
    for (int day = MONDAY; day <= SUNDAY; day++){
        // Set the day of the week in the time structure
        time.dayOfWeek = day;
        // Set the time to 12:00 PM for the current day
        time.minuteOfDay = 1200;

        // Mock TimeService to expect any arguments and return the specified time
        TimeService_getTime_ExpectAnyArgs();
        TimeService_getTime_ReturnThruPtr_time(&time);

        // Trigger the LightScheduler to process scheduled events
        LightScheduler_trigger();

        // Retrieve the ID and state of the last controlled light from LightControlSpy
        id = LightControlSpy_getLastLightId();
        state = LightControlSpy_getLastState();

        // Assert that the last controlled light is ID 10 and it is turned on
        TEST_ASSERT_EQUAL_INT(10, id);
        TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);

        // Set the time to 3:00 PM for the current day
        time.minuteOfDay = 1500;

        // Mock TimeService again for the turn-off event
        TimeService_getTime_ExpectAnyArgs();
        TimeService_getTime_ReturnThruPtr_time(&time);

        // Trigger LightScheduler for the turn-off event
        LightScheduler_trigger();

        // Retrieve the ID and state of the last controlled light again
        id = LightControlSpy_getLastLightId();
        state = LightControlSpy_getLastState();

        // Assert that the last controlled light is still ID 10 and it is turned off
        TEST_ASSERT_EQUAL_INT(10, id);
        TEST_ASSERT_EQUAL_INT(LIGHT_OFF, state);
    }
}

void testLightSchedulerOverlappingEvents(void) 
{
    Time time = { .dayOfWeek = TUESDAY, .minuteOfDay = 100 };

    // Schedule the light to turn on at a specific time
    LightScheduler_scheduleTurnOn(5, time);

    // Schedule the light to turn off at the same time
    LightScheduler_scheduleTurnOff(5, time);

    // Mock TimeService to return the scheduled time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    LightScheduler_trigger();

    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Check that the light is turned off, as off should override on in case of overlap
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, state);
}

void testLightSchedulerMultipleEvents(void)
{
    // Define the time for the first event (Monday at 1:40 AM)
    Time time1 = { .dayOfWeek = MONDAY, .minuteOfDay = 100 };
    // Schedule turn-on event for light ID 10 at Monday 1:40 AM
    LightScheduler_scheduleTurnOn(10, time1);

    // Define the time for the second event (Saturday at 8:20 AM)
    Time time2 = { .dayOfWeek = SATURDAY, .minuteOfDay = 500 };
    // Schedule turn-off event for light ID 50 at Saturday 8:20 AM
    LightScheduler_scheduleTurnOff(50, time2);

    // Check the Saturday event
    time2.minuteOfDay = 500;
    // Mock TimeService to expect any arguments and return the specified time (Saturday 8:20 AM)
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time2);
    // Trigger LightScheduler to process scheduled events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Assert that the last controlled light ID is 50 and it is turned off
    TEST_ASSERT_EQUAL_INT(50, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, state);

    // Check the Monday event
    time1.minuteOfDay = 100;
    // Mock TimeService to expect any arguments and return the specified time (Monday 1:40 AM)
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time1);
    // Trigger LightScheduler to process scheduled events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    id = LightControlSpy_getLastLightId();
    state = LightControlSpy_getLastState();

    // Assert that the last controlled light ID is 10 and it is turned on
    TEST_ASSERT_EQUAL_INT(10, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);
}

void testLightSchedulerWeeklyEvent(void)
{
    // Define the time for scheduling events (every weekday at 12:00 PM)
    Time time = { .dayOfWeek = WEEKDAY, .minuteOfDay = 1200 };
    // Schedule turn-on event for light ID 10 every weekday at 12:00 PM
    LightScheduler_scheduleTurnOn(10, time);

    int id;
    int state;

    // Iterate through each weekday (Monday to Friday)
    for (int day = MONDAY; day <= FRIDAY; day++)
    {
        // Set the day of the week in the time structure
        time.dayOfWeek = day;

        // Mock TimeService to expect any arguments and return the specified time
        TimeService_getTime_ExpectAnyArgs();
        TimeService_getTime_ReturnThruPtr_time(&time);

        // Trigger LightScheduler to process scheduled events
        LightScheduler_trigger();

        // Retrieve the ID and state of the last controlled light from LightControlSpy
        id = LightControlSpy_getLastLightId();
        state = LightControlSpy_getLastState();

        // Assert that the last controlled light is ID 10 and it is turned on
        TEST_ASSERT_EQUAL_INT(10, id);
        TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);
    }
}

void testLightSchedulerWeekendEvents(void)
{
    // Define the time for scheduling events (every weekend at 12:00 PM)
    Time time = { .dayOfWeek = WEEKEND, .minuteOfDay = 1200 };
    // Schedule turn-on event for light ID 20 every weekend at 12:00 PM
    LightScheduler_scheduleTurnOn(20, time);

    int id;
    int state;

    // Iterate through each weekend day (Saturday and Sunday)
    for (int day = SATURDAY; day <= SUNDAY; day++){
        // Set the day of the week in the time structure
        time.dayOfWeek = day;

        // Mock TimeService to expect any arguments and return the specified time
        TimeService_getTime_ExpectAnyArgs();
        TimeService_getTime_ReturnThruPtr_time(&time);

        // Trigger LightScheduler to process scheduled events
        LightScheduler_trigger();

        // Retrieve the ID and state of the last controlled light from LightControlSpy
        id = LightControlSpy_getLastLightId();
        state = LightControlSpy_getLastState();

        // Assert that the last controlled light is ID 20 and it is turned on
        TEST_ASSERT_EQUAL_INT(20, id);
        TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);
    }
}

void testLightSchedulerCancelSchedule(void)
{
    // Define the time for scheduling the turn-on event (Thursday at 2:00 AM)
    Time time = { .dayOfWeek = THURSDAY, .minuteOfDay = 120 };

    // Schedule a turn-on event for light ID 5 at Thursday 2:00 AM
    LightScheduler_scheduleTurnOn(5, time);

    // Cancel the scheduled event for light ID 5 at Thursday 2:00 AM
    LightScheduler_cancelSchedule(5, time);

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);

    // Trigger LightScheduler to process the scheduled turn-on event (should not execute)
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();

    // Assert that no light control operation occurred
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, state);
}

void testLightSchedulerRetainLightState(void){
    int id;
    int state;
    
    // Define the initial time for scheduling the turn-on event (Thursday at 2:00 AM)
    Time time = { .dayOfWeek = THURSDAY, .minuteOfDay = 120 };
    // Schedule turn-on event for light ID 5 at Thursday 2:00 AM
    LightScheduler_scheduleTurnOn(5, time);

    // Define the time for scheduling the turn-off event (Thursday at 2:30 AM)
    time.minuteOfDay = 150;
    // Schedule turn-off event for light ID 5 at Thursday 2:30 AM
    LightScheduler_scheduleTurnOff(5, time);

    // Turn on the light
    time.minuteOfDay = 120;

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    // Trigger LightScheduler to process the scheduled turn-on event
    LightScheduler_trigger();

    // Check that the light is still on at 2:10 AM (before turn-off event)
    time.minuteOfDay = 130;

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    // Trigger LightScheduler to process events
    LightScheduler_trigger();
    // Retrieve the ID and state of the last controlled light from LightControlSpy
    id = LightControlSpy_getLastLightId();
    state = LightControlSpy_getLastState();
    // Assert that the last controlled light is ID 5 and it is turned on
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);

    // Turn off the light
    time.minuteOfDay = 150;

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    // Trigger LightScheduler to process the scheduled turn-off event
    LightScheduler_trigger();

    // Check that the light is still off at 2:50 AM (after turn-off event)
    time.minuteOfDay = 170;

    // Mock TimeService to expect any arguments and return the specified time
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    // Trigger LightScheduler to process events
    LightScheduler_trigger();

    // Retrieve the ID and state of the last controlled light from LightControlSpy
    id = LightControlSpy_getLastLightId();
    state = LightControlSpy_getLastState();
    // Assert that the last controlled light is ID 5 and it is turned off
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, state);
}

void testLightSchedulerStateAcrossMultipleDays(void) {
    // Initialize time for Monday at 3:00 PM
    Time time = { .dayOfWeek = MONDAY, .minuteOfDay = 180 };

    // Schedule the light to turn on at the specified time on Monday
    LightScheduler_scheduleTurnOn(5, time);

    // Mock TimeService to return the scheduled time on Monday
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    LightScheduler_trigger();

    // Check that the light is turned on
    int id = LightControlSpy_getLastLightId();
    int state = LightControlSpy_getLastState();
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);

    // Advance time to Tuesday, keeping the same minute of the day
    time.dayOfWeek = TUESDAY;

    // Mock TimeService to return the new time on Tuesday
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    LightScheduler_trigger();

    // Check that the light remains on
    id = LightControlSpy_getLastLightId();
    state = LightControlSpy_getLastState();
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);

    // Advance time to Wednesday, keeping the same minute of the day
    time.dayOfWeek = WEDNESDAY;

    // Mock TimeService to return the new time on Wednesday
    TimeService_getTime_ExpectAnyArgs();
    TimeService_getTime_ReturnThruPtr_time(&time);
    LightScheduler_trigger();

    // Check that the light remains on
    id = LightControlSpy_getLastLightId();
    state = LightControlSpy_getLastState();
    TEST_ASSERT_EQUAL_INT(5, id);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, state);
}
