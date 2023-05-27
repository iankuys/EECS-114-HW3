#include "HashTable.h"

HashTable::HashTable(){
    load = 0;
    nSlot = 65536;
    nElem = 0;

    table = new int[nSlot];

    for (int i = 0; i < nSlot; i++){
        table[i] = -1;
    }
}

int HashTable::insert(int value){

    int hashIndex = value % nSlot;
    int newIndex = hashIndex;
    int probe = 0;
    bool found = false;

    while (!found && probe < nSlot){
        if (table[newIndex] != -1){
            probe++;
            newIndex = (hashIndex + probe) % nSlot;
        } else {
            table[newIndex] = value;
            load = (double) nElem / (double) nSlot;
            found = true;
        }
    }
    if (probe >= nSlot){
        probe = -1;
    }
    return probe;

}

bool HashTable::find(int value, int &nProbes){

    int hashIndex = value % nSlot;
    int newIndex = hashIndex;
    int probe = 0;
    bool found = false;
    int occupiedSlots = 0;

    while (probe < nSlot){
        if (table[newIndex] == value){
            found = true;
            break;
        } 
        probe++;
        newIndex = (hashIndex + probe) % nSlot;
    }

    if (!found){
        probe = -1;
    }

    nProbes = probe;

    return found;
}

void HashTable::delete_table(){
    delete [] table;
}