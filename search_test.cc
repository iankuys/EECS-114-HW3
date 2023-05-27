#include "HashTable.h"
#include <iostream>
#include <random>

using namespace std;

int main(int argc, char* argv[]){
    
    int* nProbe;
    int average;
    int nEntries = 0;
    int probeSum = 0;
    bool found;
    HashTable ht = HashTable();

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 100000);

    while (true){
        
        int randomNum = distribution(generator);
        ht.insert(randomNum);

        if (ht.load_factor() == 0.5){
            break;
        }
    }

    for (int i = 0; i < 10000; i++){
        int randomNum = distribution(generator);
        found = ht.find(randomNum,*nProbe);
        probeSum += *(nProbe);
    }

    average = probeSum/10000;
    printf("50%% full: %d\n", average);

    while (true){
        
        int randomNum = distribution(generator);
        ht.insert(randomNum);

        if (ht.load_factor() == 0.9){
            break;
        }
    }

    for (int i = 0; i < 10000; i++){
        int randomNum = distribution(generator);
        found = ht.find(randomNum,*nProbe);
        probeSum += *(nProbe);
    }

    average = probeSum/20000;
    printf("90%% full: %d\n", average);

    ht.delete_table();
    delete nProbe;

    return 0;
}