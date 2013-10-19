#ifndef RAINBOW_TABLE_h
#define RAINBOW_TABLE_h

#include <vector>
#include <bitset>

class RainbowTable{

public:

    RainbowTable();
    ~RainbowTable();
    bitset<12> checkRainbowTable(bitset<24> fingerprint, bool foundInRT);
    void push_backP(int i);
    void push_backF(bitset<24> fingerprint);

private:

    vector<bitset<12> > RTp(0);
    vector<bitset<24> > RTf(0);

};
#endif // RAINBOW_TABLE_h
