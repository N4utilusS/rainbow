#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"
#include "HashReduc.h"

bitset<24> hashing(bitset<12> password)
{
   byte plainText[8] = {0,0,0,0,0,0,0,0};
   byte cypheredText[8];
   bitset<24> fingerprint;
    
   // Transform into a byte tab.
   byte key[8] = {1,1,1,1,1,1,0,0};
   int i = 0;
	
   for (; i < 5; ++i) 
   {
      key[6] |= password[i];
      key[6] <<= 1;
   }
   key[6] |= (password[0] + password[1] + password[2] + password[3] + password[4] + 1) % 2;
   for (; i < 12; i++) 
   {
      key[7] |= password[i];
      key[7] <<= 1;
   }
   key[7] |= (password[5] + password[6] + password[7] + password[8] + password[9] + password[10] + password[11] + 1) % 2;
    
   // Encryption
   CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption e(key,sizeof(key));
   e.ProcessData(cypheredText,plainText,sizeof(plainText));

   // Convert a byte tabular into a bitset.
   fingerprint |= cypheredText[5];
   fingerprint <<= 8;
   fingerprint |= cypheredText[6];
   fingerprint <<= 8;
   fingerprint |= cypheredText[7];	
    
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

bitset<12> reduction1(bitset<24> fingerprint)
{
   bitset<12> password;
   bitset<24> reductionFunction(3.7738e+06);
   int size = fingerprint.size(); //size=24
 
   for(int i = 0, j = 0; i<size; i++)
      if(reductionFunction[i] == 1)
         password[j++] = fingerprint[i];
    
   return password;
}

bitset<12> reduction2(bitset<24> fingerprint)
{
   bitset<12> password;
   bitset<24> reductionFunction(2.7486e+06);
   int size = fingerprint.size(); //size=24
   
   for(int i = 0, j = 0; i<size; i++)
      if(reductionFunction[i] == 1)
         password[j++] = fingerprint[i];
    
   return password;
}

bitset<12> reduction3(bitset<24> fingerprint)
{
   bitset<12> password;
   bitset<24> reductionFunction(1.63544e+07);
   int size = fingerprint.size(); //size=24
    
   for(int i = 0, j = 0; i<size; i++)
      if(reductionFunction[i] == 1)
         password[j++] = fingerprint[i];
    
   return password;
}

bitset<12> reduction4(bitset<24> fingerprint)
{
   bitset<12> password;
   bitset<24> reductionFunction(6.66478e+06);
   int size = fingerprint.size(); //size=24
    
   for(int i = 0, j = 0; i<size; i++)
      if(reductionFunction[i] == 1)
         password[j++] = fingerprint[i];
    
   return password;
}
