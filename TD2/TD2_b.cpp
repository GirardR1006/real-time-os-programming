#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <signal.h>
#include <climits>

#define NANO 1000000000.

using namespace std;

unsigned int incr(unsigned long nLoops, double* pCounter, bool* pStop){
    unsigned long i = 0; 
    for(i=0;((i<nLoops) && ((*pStop)==false));i++){
        (*pCounter)++;
    }
    return(i+1);
}

void interruptCounter(int sig, siginfo_t* si, void*) {
    bool* counterStop = (bool*) si->si_value.sival_ptr;
    (*counterStop) = true;
}

int main(int argc, char* argv[]){
    if (argc!=1){
        printf("Mauvais nombre d'argument.\n");
        return (-1);
    }
    bool bstop  = false;		
    double counter = 0.;
    unsigned long nLoops = ULONG_MAX;
    //Définition de l'action à effectuer à la réception du signal
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = interruptCounter;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN,&sa,NULL);
    //**************************//
    ////Définition du signal à envoyer
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &bstop;
    //**************************//
    //Définition du temps avant émission du signal
    timer_t tid_5, tid_20;
    timer_create(CLOCK_REALTIME, &sev, &tid_5);
    struct itimerspec its_5, its_20;
    //Remise à zéro du compteur au bout de 5 secondes
    its_5.it_value.tv_sec= 5;
    its_5.it_value.tv_nsec = 0;
    its_5.it_interval.tv_sec=0;
    its_5.it_interval.tv_nsec = 0;
    //Lancement timer 5 secondes
    timer_settime(tid_5,0,&its_5,NULL);
    unsigned long i_5 = incr(nLoops,&counter,&bstop);
    timer_delete(tid_5);
    cout << "Timer 5 terminé " << endl;
    bstop = false;
    counter = 0.;
    timer_create(CLOCK_REALTIME, &sev, &tid_20);
    its_20.it_value.tv_sec= 20;
    its_20.it_value.tv_nsec = 0;
    its_20.it_interval.tv_sec=0;
    its_20.it_interval.tv_nsec = 0;
    timer_settime(tid_20,0,&its_20,NULL);
    unsigned long i_20 = incr(nLoops,&counter,&bstop);
    timer_delete(tid_20);
    bstop = false;
    counter = 0.;
    cout << "Timer 20 terminé" << endl;

    double a = (i_20-i_5)/15.;
    double b = i_5-5*a;
    cout << "i5: " << i_5 << endl;
    cout << "i20: " << i_20 << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    //TODO: mesurer sur la rapsberry les valeurs de a et b et tester avec un nombre de boucle fixé

    return 0;
}
