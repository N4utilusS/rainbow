//
//  CrackerRainbow.cpp
//  Rainbow
//
//  Created by Anthony Debruyn on 19/10/13.
//  Copyright (c) 2013 Anthony Debruyn. All rights reserved.
//

#include "CrackerRainbow.h"

CrackerRainbow::CrackerRainbow()
{
    RT = new RainbowTable(dico);
}

CrackerRainbow::~CrackerRainbow()
{
    delete RT;
    RT = NULL;
}

void CrackerRainbow::findPassword(bitset<24> stolenFingerprint)
{
    bool foundInRT = false;
    bitset<12> password;
    bitset<24> fingerprint, fingerprintPrime;
    queue<bitset<24> > fifo;
    
    password = RT->checkRainbowTable(stolenFingerprint, foundInRT);
    
    if(foundInRT)    // stolenFingerprint found in RT, step 1
    {
        password = RT->realPassword(password,stolenFingerprint);
        cout << password << endl;
    }
    else        // stolenFingerprint not found in RT, step 2 (ALGO À REMPLACER !!!!)
    {
        bool a = true;
        fingerprintPrime = stolenFingerprint;
        int j = 1;
        while(a)
        {
            fingerprint = fingerprintPrime;
            for(int i = j; i <= 4; i++)
            {
                password = reduction(fingerprint,i);
                fingerprint = hashing(password);
            }
            
            password = RT->checkRainbowTable(fingerprint, foundInRT);  // Is this new fp in the RT ?
            
            if(foundInRT)    // Fingerprint found in RT
            {
                password = RT->realPassword(password,fingerprint);
                a = false;
            }
            else
            {
                j++;
                fifo.push(fingerprint);
            }
            
            if(j == 5)
            {
                j = 1;
                fingerprintPrime = fifo.front();
                fifo.pop();
            }
        }
    }
    
    
}

vector<bitset<12>> CrackerRainbow::getKeysFound() const
{
    return keysFound;
}