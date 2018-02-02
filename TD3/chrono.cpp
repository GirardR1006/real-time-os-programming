#include "chrono.h"
#define NANO 1000000000.


Chrono::Chrono()
{
    clock_gettime(CLOCK_REALTIME, &start_time);
    active = true;
}

Chrono::~Chrono()
{
}

void Chrono::stop()
{
    clock_gettime(CLOCK_REALTIME, &stop_time);
    active = false;
}

void Chrono::restart()
{
    clock_gettime(CLOCK_REALTIME, &start_time);
    active = true;
}

bool Chrono::isActive()
{
    return active;
}

double Chrono::startTime()
{
    double duration = start_time.tv_sec;
    double nduration= start_time.tv_nsec/NANO;
    return duration + nduration;
}

double Chrono::stopTime()
{
    double duration = stop_time.tv_sec;
    double nduration= stop_time.tv_nsec/NANO;
    return duration + nduration;
}

double Chrono::lap()
{
    double duration, nduration;
    struct timespec current_time;
    if (!active)
    {
        current_time = stop_time;
    }
    else{
        clock_gettime(CLOCK_REALTIME, &current_time);
    }
    duration = current_time.tv_sec-start_time.tv_sec;
    nduration = (current_time.tv_nsec-start_time.tv_nsec)/NANO;
    return (duration+nduration);
}
