#include "timer.h"
/**
 * This is the documentation for PeriodicTimer class
 */
class PeriodicTimer : public Timer
{
    public:
        /*!
         *Overload the start method of Timer class
         *Sets a period equals to duration
         *@param[in] duration_ms duration of the timer in ms
         */
        void start(double duration_ms); 
};
