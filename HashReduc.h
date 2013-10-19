//
//  HashReduc.h
//  Rainbow
//
//  Created by Anthony Debruyn on 19/10/13.
//  Copyright (c) 2013 Anthony Debruyn. All rights reserved.
//

#ifndef Rainbow_HashReduc_h
#define Rainbow_HashReduc_h

bitset<24> hashing(bitset<12> password);
bitset<12> reduction(bitset<24> fingerprint, int i);
bitset<12> reduction1(bitset<24> fingerprint);
bitset<12> reduction2(bitset<24> fingerprint);
bitset<12> reduction3(bitset<24> fingerprint);
bitset<12> reduction4(bitset<24> fingerprint);

#endif
