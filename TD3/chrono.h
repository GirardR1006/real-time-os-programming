#include <time.h>
/**
 * This is the documentation for Chrono class
 */
class Chrono
{
    private:

        struct timespec start_time;//!< start timer
        struct timespec stop_time;//!< stop timer
        bool active;//bool describing if the timer is active or not
    public:
        /*!
         *Constructor, initiate the start_time at POSIX's CLOCK_REALTIME and set active field to true
         */
        Chrono();
        /*!
         *Destructor, should probably do stuff
         */
        ~Chrono(); 
        /*!
         *Initiate the stop_time at POSIX's CLOCK_REALTIME and set active field to false
         */
        void stop(); 
        /*!
         *Reinitialize the timer: start_time is reset to current CLOCK_REALTIME and active is set to true
         */
        void restart(); 
        /*!
        * isActive() documentation
        * @param[out] active describe if timer is running
        */
        bool isActive();
        /*!
        * startTime() documentation
        * @param[out] startTime time of start
        */
        double startTime();
        /*!
        * stopTime() documentation
        * @param[out] stopTime time of stop
        */
        double stopTime();
        /*!
        * lap() documentation
        * @param[out] lap time elapsed between the starting and stopping of chronometer
        */
        double lap();

};
