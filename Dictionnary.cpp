#include "Dictionnary.h"

Dictionnary::Dictionnary(){
    for(int i=0;i<4096;i++) setBit(i, 0, i);
}

Dictionnary::~Dictionnary(){
    dico = NULL;
}

void setBit(int row, int column, int bit){
    dico[row][column] = bit;
}

int getBit(int row, int column){
    return dico[row][column];
}
