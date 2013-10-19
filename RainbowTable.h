#ifndef RAINBOW_TABLE_h
#define RAINBOW_TABLE_h

#include <vector>
#include <bitset>
#include "Dictionary.h"
#include "HashReduc.h"

using namespace std;

class RainbowTable{

public:

    RainbowTable(Dictionary &dico);
    bitset<12> checkRainbowTable(bitset<24> fingerprint, bool& foundInRT) const;
    bitset<12> realPassword(bitset<12> password, bitset<24> stolenFingerprint) const;
    void addEntry(int i, bitset<24> fingerprint);

private:

    vector<bitset<12> > RTp;
    vector<bitset<24> > RTf;

};
#endif // RAINBOW_TABLE_h
