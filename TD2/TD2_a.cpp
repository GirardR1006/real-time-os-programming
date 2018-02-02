#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>

void myHandler(int sig, siginfo_t* si, void* ptr) {
    (*(int*) si->si_value.sival_ptr)++; //Incrémentation de la valeur à l'adresse sival_ptr, ici notre entier
    printf("%d\n",*(int*) si->si_value.sival_ptr);
}


int main(){
    int counter=0;
    //Définition de l'action à effectuer à la réception du signal
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN,&sa,NULL);
    //**************************//
    //Définition du signal à envoyer
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &counter;
    //**************************//
    //Définition du temps avant émission du signal
    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    struct itimerspec its;
    its.it_value.tv_sec = 0; //Remise à zéro du compteur au bout d'une seconde
    its.it_value.tv_nsec = 500000000;
    its.it_interval.tv_sec = 0; //Remise à zéro du compteur toutes les secondes
    its.it_interval.tv_nsec = 500000000;
    timer_settime(tid, 0, &its, NULL);
    while(counter<15){}
    timer_delete(tid);
    return 0;
}
