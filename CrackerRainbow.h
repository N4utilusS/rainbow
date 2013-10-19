//
//  CrackerRainbow.h
//  Rainbow
//
//  Created by Anthony Debruyn on 19/10/13.
//  Copyright (c) 2013 Anthony Debruyn. All rights reserved.
//

#ifndef __Rainbow__CrackerRainbow__
#define __Rainbow__CrackerRainbow__

#include <iostream>
#include <bitset>
#include "RainbowTable.h"
#include "Dictionary.h"
#include <queue>
#include <vector>

using namespace std;

class CrackerRainbow {
    
public:
    CrackerRainbow();
    ~CrackerRainbow();
    void findPassword(bitset<24> stolenFingerprint);
    vector<bitset<12>> getKeysFound() const;
    
private:
    Dictionary dico;
    RainbowTable *RT;
    vector<bitset<12>> keysFound;   // Add the matching passwords.
    
};

#endif /* defined(__Rainbow__CrackerRainbow__) */
