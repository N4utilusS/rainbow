

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
    bitset<12> password;
    bitset<24> fingerprint;
    
    keysFound.clear();  // Clear the vector for a new run.
    
    if(RT->isInRT(stolenFingerprint, password) && RT->FoundRealPassword(password, stolenFingerprint))    // stolenFingerprint found in RT, step 1
    {
        keysFound.push_back(password);
        cout << "Found a key at step 1 : " << password << endl;
    }
    else            // stolenFingerprint not found in RT, step 2
    {
        for(int j = 4; j >= 1; --j)
        {
            fingerprint = stolenFingerprint;
            for(int i = j; i <= 4; i++)
            {
                password = reduction(fingerprint,i);
                fingerprint = hashing(password);
            }
            
            if(RT->isInRT(fingerprint, password) && RT->FoundRealPassword(password, stolenFingerprint))    // Fingerprint found in RT
            {                
                bool toBeAdded = true;  // Voir si le password n'est pas déjà dans la liste.
                for (vector<bitset<12> >::iterator it = keysFound.begin(); it < keysFound.end() && toBeAdded; it++)
                    toBeAdded = (*it != password);
                
                if (toBeAdded) {
                    keysFound.push_back(password);
                    cout << "Found a key at step 2." << j << " : " << password << endl;
                }
            }

        }
    }


}

vector<bitset<12> > CrackerRainbow::getKeysFound() const
{
    return keysFound;
}
