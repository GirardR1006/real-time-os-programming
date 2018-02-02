#include <cstdio>
#include <iostream>
#include "chrono.h"
#include <unistd.h>

using namespace std;

int main()
{
    Chrono chrono;
    int i = 0;
    while(i<10){
        cout<<"Starting chrono, timer is: "<<chrono.lap()<<" s."<<endl;
        sleep(60);
        chrono.stop();
        cout<<"Stopping chrono, timer is: "<<chrono.lap()<<" s."<<endl;
        chrono.restart();
        cout<<"Restarting chrono, now!"<<endl;
        i++;
    }
}
