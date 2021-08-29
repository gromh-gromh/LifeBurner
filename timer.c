#include <timer.h>
#include <stdio.h>
#include <stdlib.h>

double GetTime(struct World* world)
{
    double time_sec;

    time_t start_time = world->start_time;

    time_t current_time;
    time(&current_time);

    time_sec = difftime(current_time, start_time);

    return time_sec;
}