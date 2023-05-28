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
    HashTable ht = HashTable(N);

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
            average = (double) probeSum / (double) nEntries;
            printf("50%% full: %.4f\n", average);
        }
        else if (ht.load_factor() == 0.9){
            average = (double) probeSum / (double) nEntries;
            printf("90%% full: %.4f\n", average);
            break;
        }
    }
    ht.delete_table();

    return 0;
}