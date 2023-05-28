#include "HashTable.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]){
    
    int N = -1;

    if (argc == 2) {
        N = atoi (argv[1]);
        assert(N > 0);
    } else {
        fprintf (stderr, "usage: %s <n>\n", argv[0]);
        fprintf (stderr, "where <n> is the length of hash table.\n");
        return -1;
    }

    int nProbe;
    double average;
    int nEntries = 0;
    int probeSum = 0;
    bool found;
    HashTable ht = HashTable(N);

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
        found = ht.find(randomNum, nProbe);
        probeSum += nProbe;
    }

    average = (double)  probeSum/ (double) 10000;
    printf("50%% full: %.4f\n", average);

    while (true){
        
        int randomNum = distribution(generator);
        ht.insert(randomNum);

        if (ht.load_factor() == 0.9){
            break;
        }
    }

    for (int i = 0; i < 10000; i++){
        int randomNum = distribution(generator);
        found = ht.find(randomNum, nProbe);
        probeSum += nProbe;
    }

    average = (double) probeSum/ (double) (10000*2);
    printf("90%% full: %.4f\n", average);

    ht.delete_table();

    return 0;
}