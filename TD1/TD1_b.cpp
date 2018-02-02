#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <pthread.h>

#define NANO 1000000000.

using namespace std;

struct Data_incr{
    int loops;
    double* counter;
};

void incr(unsigned int nLoops, double* pCounter){
    for(int i =0;i<nLoops;i++){
        (*pCounter)++;
    }
}

void* call_incr(void* v_data){
    Data_incr* p_data = (Data_incr*) v_data;
    incr(p_data->loops,p_data->counter);
    return v_data;
}

int main(int argc, char* argv[]){
    if (argc!=3){
        printf("Mauvais nombre d'argument. Attendu: nombre d'itérations, nombre de tâches");
        return (-1);
    }
    
    int nLoops = atoi(argv[1]);
    int nTasks = atoi(argv[2]);

    double counter = 0.;

    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    pthread_t threads[nTasks];
    Data_incr data = {nLoops, &counter};
    struct timespec start, stop;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
          perror( "clock gettime" );
          exit( EXIT_FAILURE );
    }

    for(int i=0;i<nTasks;i++){
        pthread_create(&threads[i],NULL,call_incr,&data);
    }

    for(int i=0;i<nTasks;i++){
        pthread_join(threads[i],0);
    }

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    //Résultats
    double duration =  (stop.tv_sec - start.tv_sec);
    double nduration = (stop.tv_nsec - start.tv_nsec)/NANO; //attention au dépassement de capacité
    double total = duration + nduration;
    cout << "Valeur du compteur à la fin du programme: " << counter << endl;
    cout << total << " s pour l'exécution du programme" << endl;
    //pthread_attr_destroy(&attr);
    //On constate que sans mutex, les valeurs prises sont au mieux très très aléatoires
    return 0;
}
