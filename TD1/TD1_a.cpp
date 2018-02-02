#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <pthread>

#define NANO 1000000000.

using namespace std;

void incr(unsigned int nLoops, double* pCounter){
    for(int i =0;i<nLoops;i++){
        (*pCounter)++;
    }
}

int main(int argc, char* argv[]){
    if (argc!=2){
        printf("Mauvais nombre d'argument.");
        return (-1);
    }
    int nLoops = atoi(argv[1]);

    double counter = 0.;
    
    struct timespec start, stop;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
          perror( "clock gettime" );
          exit( EXIT_FAILURE );
    }
    incr(nLoops,&counter);
    
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    double duration =  (stop.tv_sec - start.tv_sec);
    double nduration = (stop.tv_nsec - start.tv_nsec)/NANO; //attention au dépassement de capacité
    double total = duration + nduration;
    cout << "Valeur du compteur à la fin du programme: " << counter << endl;
    cout << total << " s pour l'exécution du programme" << endl;
    return 0;
    //Écrire une fonction qui utilise les primitives Posix de temps pour
    //déterminer le temps d'évaluation d'une fonction
}
