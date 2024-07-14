/**
 * @file LightScheduler.c
 * @brief Implementation of the LightScheduler module.
 *
 * This module provides functions to schedule and control the turning on and off of lights
 * at specific times. It uses an array to store scheduled events and a periodic alarm to trigger
 * the execution of the scheduled events.
 */

#include "LightScheduler.h"
#include "LightControlSpy.h"

// Define the maximum number of scheduled events and declare the array to store events
#define MAX_SCHEDULED_EVENTS 256
static Event scheduledEvents[MAX_SCHEDULED_EVENTS];
static int eventCount; 

// Function to initialize the LightScheduler
int LightScheduler_initialize(void)
{
    // Start periodic alarm with a 60-second interval, triggering LightScheduler_trigger function
    int schedulerID = TimeService_startPeriodicAlarm(60, LightScheduler_trigger);

    // Initialize event count and scheduledEvents array
    eventCount = 0;
    for (int i = 0; i < MAX_SCHEDULED_EVENTS; i++)
    {
        scheduledEvents[i].time.dayOfWeek = NONE;
        scheduledEvents[i].time.minuteOfDay = -1;
        scheduledEvents[i].lightID = LIGHT_ID_UNKNOWN;
        scheduledEvents[i].action = -1;
    }
    return schedulerID;
}

// Function to terminate the LightScheduler
void LightScheduler_terminate(int schedulerID)
{
    // Stop periodic alarm associated with the given scheduler ID
    TimeService_stopPeriodicAlarm(schedulerID);
}

// Function to trigger scheduled events
void LightScheduler_trigger(void)
{   
    // Get current time from TimeService
    Time currentTime;
    TimeService_getTime(&currentTime);

    // Process all the scheduled events
    for (int i = 0; i < eventCount; i++)
    {
        // Check if the current time matches a scheduled event
        if ((currentTime.dayOfWeek == scheduledEvents[i].time.dayOfWeek) && 
            (currentTime.minuteOfDay == scheduledEvents[i].time.minuteOfDay))
        {
            // Perform action based on the scheduled event
            if (scheduledEvents[i].action)
            {
                LightControl_on(scheduledEvents[i].lightID);
            }
            else
            {
                LightControl_off(scheduledEvents[i].lightID);
            }
        }
    }
}

// Function to schedule turning on a light at a specific time
int LightScheduler_scheduleTurnOn(int lightID, Time time)
{
    // Check if the light ID is within valid range
    if (LightScheduler_isLightIDInRange(lightID) < 0)
    {
        return -1;
    }
    // Check if the event should recur every day, weekend, or weekday
    if ((time.dayOfWeek == EVERYDAY) || (time.dayOfWeek == WEEKEND) || (time.dayOfWeek == WEEKDAY))
    {
        int scheduled = LightScheduler_scheduleRecurringEvent(lightID, time, 1);
        return scheduled;
    }
    else
    {
        // Schedule a one-time event on a specific day and time
        scheduledEvents[eventCount].time.dayOfWeek = time.dayOfWeek;
        scheduledEvents[eventCount].time.minuteOfDay = time.minuteOfDay;
        scheduledEvents[eventCount].lightID = lightID;
        scheduledEvents[eventCount].action = 1;
        eventCount += 1;
    }
    return 0;
}

// Function to schedule turning off a light at a specific time
int LightScheduler_scheduleTurnOff(int lightID, Time time)
{
    // Check if the light ID is within valid range
    if (LightScheduler_isLightIDInRange(lightID) < 0)
    {
        return -1;
    }
    // Check if the event should recur every day, weekend, or weekday
    if ((time.dayOfWeek == EVERYDAY) || (time.dayOfWeek == WEEKEND) || (time.dayOfWeek == WEEKDAY))
    {
        int scheduled = LightScheduler_scheduleRecurringEvent(lightID, time, 0);
        return scheduled;
    }
    else
    {
        // Schedule a one-time event on a specific day and time
        scheduledEvents[eventCount].time.dayOfWeek = time.dayOfWeek;
        scheduledEvents[eventCount].time.minuteOfDay = time.minuteOfDay;
        scheduledEvents[eventCount].lightID = lightID;
        scheduledEvents[eventCount].action = 0;
        eventCount += 1;
    }
    return 0;
}

// Function to cancel a scheduled event for a light at a specific time
int LightScheduler_cancelSchedule(int lightID, Time time)
{
    if ((lightID < 0) || (lightID > 256))
    {
        return -1;
    }
    // Check if the event is in the list, loop over the array
    for (int i = 0; i < eventCount; i++)
    {
        if ((scheduledEvents[i].lightID == lightID) && 
            (scheduledEvents[i].time.dayOfWeek == time.dayOfWeek) && 
            (scheduledEvents[i].time.minuteOfDay == time.minuteOfDay))
        {
            // Shift elements to remove the canceled event
            for (int j = i; j < eventCount - 1; j++)
            {
                scheduledEvents[j] = scheduledEvents[j + 1];
            }
            eventCount -= 1;
            // Reset the last event slot
            scheduledEvents[eventCount].time.dayOfWeek = NONE;
            scheduledEvents[eventCount].time.minuteOfDay = -1;
            scheduledEvents[eventCount].lightID = LIGHT_ID_UNKNOWN;
            scheduledEvents[eventCount].action = LIGHT_STATE_UNKNOWN;
        }
    }
    return 0;
}

// Function to check if a light ID is within valid range
int LightScheduler_isLightIDInRange(int id)
{
    if ((id >= 0) && (id <= 256) && (eventCount < MAX_SCHEDULED_EVENTS))
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// Helper function to schedule events for weekdays, weekends, and everyday
int LightScheduler_scheduleRecurringEvent(int lightID, Time time, int action)
{
    if ((time.dayOfWeek == EVERYDAY) && (eventCount + 7 <= MAX_SCHEDULED_EVENTS))
    {
        // Schedule event for every day of the week
        for (int day = MONDAY; day <= SUNDAY; day++)
        {
            scheduledEvents[eventCount].time.dayOfWeek = day;
            scheduledEvents[eventCount].time.minuteOfDay = time.minuteOfDay;
            scheduledEvents[eventCount].lightID = lightID;
            scheduledEvents[eventCount].action = action;
            eventCount += 1;
        }
    }
    else if ((time.dayOfWeek == WEEKDAY) && (eventCount + 5 <= MAX_SCHEDULED_EVENTS))
    {
        // Schedule event for weekdays (Monday to Friday)
        for (int day = MONDAY; day <= FRIDAY; day++)
        {
            scheduledEvents[eventCount].time.dayOfWeek = day;
            scheduledEvents[eventCount].time.minuteOfDay = time.minuteOfDay;
            scheduledEvents[eventCount].lightID = lightID;
            scheduledEvents[eventCount].action = action;
            eventCount += 1;
        }
    }
    else if ((time.dayOfWeek == WEEKEND) && (eventCount + 2 <= MAX_SCHEDULED_EVENTS))
    {
        // Schedule event for weekends (Saturday and Sunday)
        for (int day = SATURDAY; day <= SUNDAY; day++)
        {
            scheduledEvents[eventCount].time.dayOfWeek = day;
            scheduledEvents[eventCount].time.minuteOfDay = time.minuteOfDay;
            scheduledEvents[eventCount].lightID = lightID;
            scheduledEvents[eventCount].action = action;
            eventCount += 1;
        }
    }
    else
    {
        return -1; // Not enough space in the array
    }
    return 0;
}