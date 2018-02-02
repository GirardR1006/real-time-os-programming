#include "periodic_timer.h"
/**
 * This is the documentation for Timer class
 */
class Countdown : public PeriodicTimer
{
    private:
        int* pCounter;
    protected:
        void callback();
    public:
        /*!
        * constructor of Countdown
        * @param[in] pCounter Initial value of counter, to be decremented with 1Hz frequency
        */
        Countdown(int* pCounter);
        ~Countdown();

};
