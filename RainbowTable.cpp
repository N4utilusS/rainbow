#include "RainbowTable.h"

RainbowTable::RainbowTable(){}

RainbowTable::~RainbowTable(){
    RTp.erase(); RTp = NULL;
    RTf.erase(); RTf = NULL;
}

bitset<12> checkRainbowTable(bitset<24> fingerprint,bool& foundInRT)
{
    bitset<12> password;
    int length = RTf.size();//if we put RTf.size() in the loop for, we got a warning...
    for(int i=0; i < length; i++)
        if(fingerprint == RTf[i])
        {
            password = RTp[i];
            foundInRT = true;
            break;
        }
    return password;    // Returns the password corresponding to the fingerprint.
}

void push_backP(int i){
    RTp.push_back(i);
}

void push_backF(bitset<24> fingerprint){
    RTf.push_back(fingerprint);
}
