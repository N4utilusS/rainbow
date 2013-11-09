#include "RainbowTable.h"
#include <iostream>

RainbowTable::RainbowTable(Dictionary &dico)
{
   bitset<24> fingerprint;
   bitset<12> pass[5], password;

   for(int i=0; i<4096; i++)
   {
      if(dico.getAvailability(i)) // If this entry is available.
      {
	 pass[0] = i;
         for(int j = 1; j <= 4; j++)
         {
            fingerprint = hashing(pass[j-1]);
            pass[j] = reduction(fingerprint,j);
         }

         fingerprint = hashing(pass[4]);
            
         if(!isInRT(fingerprint, password))  //check if the fingerprint is already in the table, in order to avoid collisions
         {
            addEntry(i, fingerprint);
            for(int j = 1; j < 4; j++)
               dico.setAvailability((int) pass[j].to_ulong(), false);  // The 4 derivated passwords become unavailable.
         }
      }
   }
   cout << "Size of RT : " << RTf.size() << endl;
   displayFile();
}

// "Returns" the initial password corresponding to the fingerprint (valid iff foundInRT = true).
bool RainbowTable::isInRT(bitset<24> fingerprint, bitset<12> &password) const
{
   if(RTf.size() > 0)
   {
      unsigned int max = (unsigned int) RTf.size()-1, min = 0, mid = (min+max)/2;
      for(; min < max; mid = (min+max)/2) 
      {
	 if (fingerprint.to_ulong() > RTf[mid].to_ulong())
	    min = mid + 1;
	 else
	    max = mid;
      }
      if(RTf[min] == fingerprint)
      {
         password = RTp[min];
         return true;
      }
   }
   return false;
}

// "Returns" the real password corresponding to the stolenFingerprint.
bool RainbowTable::FoundRealPassword(bitset<12> &password, bitset<24> stolenFingerprint) const // Step one of the algorithm
{
   bitset<24> fingerprint;
   bitset<12> pass = password;
   cout << password;
   for(int i = 1; i <= 5; i++)
   {
      fingerprint=hashing(pass);
      cout << "->H->" << fingerprint;
      if(fingerprint == stolenFingerprint)
      {
         password = pass;
         return true;
      }
      else
      {
	 if(i<5)
	 {
	    pass = reduction(fingerprint,i);
	    cout << "->R" << i << "->" << pass;
	 }
      }
   }
   cout << endl;
   return false;
}

void RainbowTable::addEntry(int i, bitset<24> fingerprint)
{
   unsigned int place = 0;

   if(RTf.size() > 0) 
   {
      unsigned int max = (unsigned int) RTf.size()-1, min = 0, mid = (min+max)/2;
      for(; min < max; mid = (min+max)/2)
      {
	 if (fingerprint.to_ulong() > RTf[mid].to_ulong())
	    min = mid + 1;
	 else
	    max = mid;
      }
      place = (fingerprint.to_ulong() < RTf[min].to_ulong()) ? min : min+1;
   }

   RTf.insert(RTf.begin()+place, fingerprint);
   RTp.insert(RTp.begin()+place, i);
    
   bitset<12> pass[5];
   pass[0] = i;
   //cout << pass[0];
   for(int j = 1; j <= 4; j++)
   {
      fingerprint = hashing(pass[j-1]);
      pass[j] = reduction(fingerprint,j);
      //cout << " -H> " << fingerprint << " -R> " << pass[j];
   }
    
   fingerprint = hashing(pass[4]);
   //cout << " -H> " << fingerprint << endl;
}

void RainbowTable::displayFile()
{
   if(ifstream("RT.txt"))
      cout << "file RT.txt already exists." << endl;
   else 
   {
      ofstream file;
      file.open("RT.txt");
      int size=RTf.size();
      for(int i=0; i<size; i++)
	 file << RTp[i] << " -> " << RTf[i] << endl;
      file.close();
   }
}
