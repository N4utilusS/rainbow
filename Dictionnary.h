#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include <bitset>

class Dictionnary {

public:

    Dictionnary();
    ~Dictionnary();
    void setBit(int row, int column, int bit);
    int getBit(int row, int column);

private:

    bitset<12> dico[4096][2];

};

#endif // DICTIONNARY_H
