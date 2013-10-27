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
    bool isInRT(bitset<24> fingerprint, bitset<12> &password) const;
    bool FoundRealPassword(bitset<12> &password, bitset<24> stolenFingerprint) const;
    void addEntry(int i, bitset<24> fingerprint);

private:

    vector<bitset<12> > RTp;
    vector<bitset<24> > RTf;

};
#endif // RAINBOW_TABLE_h
