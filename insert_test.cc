#include "HashTable.h"
#include <iostream>
#include <random>

using namespace std;

int main(int argc, char* argv[]){
    
    int nProbe;
    int average;
    int nEntries = 0;
    int probeSum = 0;
    HashTable ht = HashTable();

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 100000);

    while (true){
        
        int randomNum = distribution(generator);
        nProbe = ht.insert(randomNum);

        if (nProbe != -1){
            nEntries++;
            probeSum += nProbe;
        }

        if (ht.load_factor() == 0.5){
            average = probeSum / nEntries;
            printf("50%% full: %d\n", average);
        }
        else if (ht.load_factor() == 0.9){
            average = probeSum / nEntries;
            printf("90%% full: %d\n", average);
            break;
        }

    }
    ht.delete_table();

    return 0;
}