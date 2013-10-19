//
//  HashReduc.cpp
//  Rainbow
//
//  Created by Anthony Debruyn on 19/10/13.
//  Copyright (c) 2013 Anthony Debruyn. All rights reserved.
//

#include "HashReduc.h"

bitset<24> hashing(bitset<12> password)
{
    const bitset<64> msg = 0x0000000000000000;
    bitset<24> fingerprint;
    int key[64];
    
    // Odd parity bits
    
    int parity1 = (password[0] + password[1] + password[2] + password[3] + password[4] + 1) % 2;
    int parity2 = (password[5] + password[6] + password[7] + password[8] + password[9] + password[10] + password[11] + 1) % 2;
    
    // key = //56 bits key + 8 parity bits, given password is the 12 least significant bits of the key.
    //{
    //       0, 0, 0, 0, 0, 0, 0, 1,
    //       0, 0, 0, 0, 0, 0, 0, 1,
    //       0, 0, 0, 0, 0, 0, 0, 1,
    //       0, 0, 0, 0, 0, 0, 0, 1,
    //       0, 0, 0, 0, 0, 0, 0, 1,
    //       0, 0, 0, 0, 0, 0, 0, 1,
    //       0, 0, password[0], password[1], password[2], password[3], password[4], parity1,
    //       password[5], password[6], password[7], password[8], password[9], password[10], password[11], parity2,
    //   };
    
    int i;
    for (i = 0; i < 7; i++) key[i] = 0; key[i] = 1; // Real men know why.
    for (i = 8; i < 15; i++) key[i] = 0; key[i] = 1;    // While(1) break; missing.
    for (i = 16; i < 23; i++) key[i] = 0; key[i] = 1;
    for (i = 24; i < 31; i++) key[i] = 0; key[i] = 1;
    for (i = 32; i < 39; i++) key[i] = 0; key[i] = 1;
    for (i = 40; i < 47; i++) key[i] = 0; key[i] = 1;
    key[48] = 0; key[49] = 0; key[50] = password[0]; key[51] = password[1]; key[52] = password[2]; key[53] = password[3]; key[54] = password[4]; key[55] = parity1;
    key[56] = password[5]; key[57] = password[6]; key[58] = password[7]; key[59] = password[8]; key[60] = password[9]; key[61] = password[10]; key[62] = password[11]; key[63] = parity2;
    
    //fingerprint = DES(msg, key);
    
    fingerprint=0x001000;
    return fingerprint;
}

bitset<12> reduction(bitset<24> fingerprint, int i)
{
    bitset<12> password;
    if(i==1)
        password=reduction1(fingerprint);
    if(i==2)
        password=reduction2(fingerprint);
    if(i==3)
        password=reduction3(fingerprint);
    else
        password=reduction4(fingerprint);
    return password;
}

//take the 12 least bits
bitset<12> reduction1(bitset<24> fingerprint)
{
    bitset<12> password;
    for(int i=12;i<24;i++)
        password[i-12]=fingerprint[i];
    return password;
}

//take the 12 first bits
bitset<12> reduction2(bitset<24> fingerprint)
{
    bitset<12> password;
    for(int i=0;i<12;i++)
        password[i]=fingerprint[i];
    return password;
}

//take one bit in two (even)
bitset<12> reduction3(bitset<24> fingerprint)
{
    bitset<12> password;
    for(int i=0;i<24;i++)
        if(i%2==0)
            password[i/2]=fingerprint[i];
    return password;
}

//take one bit in two (odd)
bitset<12> reduction4(bitset<24> fingerprint)
{
    bitset<12> password;
    for(int i=0;i<24;i++)
        if(i%2==1)
            password[(i-1)/2]=fingerprint[i];
    return password;
}