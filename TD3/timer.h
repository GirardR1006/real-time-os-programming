#include <time.h>
#include <signal.h>
/**
 * This is the documentation for Timer class
 */
class Timer
{
    private:
        /*!
        * call_callback definition
        * @param[in] sig ID of signal
        * @param[in] data si->si_value.sival_ptr carries the tid 
        * @param[in] user hm, don't know about that
        */
        static void call_callback(int sig, siginfo_t* si, void* user);
    public:
        /*!
         *Constructor, initiate the POSIX timer
         */
        Timer();
        /*!
         *Destructor, should probably do stuff
         */
        ~Timer(); 
        /*!
         *Start the timer for duration duration_ms
         *@param[in] duration_ms duration of the timer in ms
         */
        void start(double duration_ms); 
        /*!
         *Stop the timer
         */
        void stop(); 
    protected:
        timer_t tid;//!< POSIX timer
        /*!
        * Virtual callback definition, to be implemented in a derivate class
        */
        virtual void callback()=0;
};
