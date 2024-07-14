#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

#include "LightControl.h"
#include "TimeService.h"

typedef struct {
    Time time;
    int lightID;
    int action; 
} Event;

int LightScheduler_initialize(void);
void LightScheduler_terminate(int schedulerID);
void LightScheduler_trigger(void);
int LightScheduler_scheduleTurnOn(int lightID, Time time);
int LightScheduler_scheduleTurnOff(int lightID, Time time);
int LightScheduler_cancelSchedule(int lightID, Time time);
int LightScheduler_isLightIDInRange(int id);
int LightScheduler_scheduleRecurringEvent(int lightID, Time time, int action);
#endif
