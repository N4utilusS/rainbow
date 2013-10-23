#include "RainbowTable.h"

RainbowTable::RainbowTable(Dictionary &dico)
{
    bitset<24> fingerprint;
    bitset<12> pass[5], password;
    bool foundInRT = false;
    
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
            password = checkRainbowTable(fingerprint,foundInRT); //check if the fingerprint is already in the table, in order to avoid collisions
            
            if(foundInRT)
                foundInRT = false;
            else
            {
                addEntry(i, fingerprint);
                for(int j = 1; j <= 4; j++)
                    dico.setAvailability((int) pass[j].to_ulong(), false);  // The 4 derivated passwords become unavailable.
            }
        }
    }
    
}

bitset<12> RainbowTable::checkRainbowTable(bitset<24> fingerprint, bool& foundInRT) const
{
    unsigned int end = (unsigned int) RTf.size()-1, beg = 0, dic = (beg+end)/2;
    
    
    for (; beg+1 != end; dic = (beg+end)/2) {
        
        if (fingerprint.to_ulong() > RTf[dic].to_ulong())
            beg = dic;
        else if (fingerprint.to_ulong() < RTf[dic].to_ulong())
            end = dic;
        else
            return RTp[dic];
        
    }
    
    if (fingerprint.to_ulong() == RTf[beg].to_ulong())
        foundInRT = true;
    
    
    return RTp[beg];    // Returns the password corresponding to the fingerprint (valid iff foundInRT = true).
}

bitset<12> RainbowTable::realPassword(bitset<12> password, bitset<24> stolenFingerprint) const
{
    bitset<24> fingerprint;
    for(int i = 1; i <= 4; i++) //!--! 4?? if not, do a while(a)
    {
        fingerprint = hashing(password);
        
        if(fingerprint == stolenFingerprint)
            break;
        else
            password = reduction(fingerprint,i);
    }
    return password;    // Password corresponding to the stolen fingerprint.
}

void RainbowTable::addEntry(int i, bitset<24> fingerprint)
{
	unsigned int place = 0;
	
	if (RTf.size() > 0) {
	    unsigned int max = (unsigned int) RTf.size()-1, min = 0, mid = (min+max)/2;
	    
	    
	    for (; min < max; mid = (min+max)/2) {
	        
	        if (fingerprint.to_ulong() > RTf[mid].to_ulong())
	            min = mid + 1;
	        else
	            max = mid;
	        
	    }

		place = (fingerprint.to_ulong() < RTf[min].to_ulong()) ? min : min+1;
    }
	
    RTf.insert(RTf.begin()+place, fingerprint);
    RTp.insert(RTp.begin()+place, i);
}

