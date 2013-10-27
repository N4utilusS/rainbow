

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
    bitset<24> fingerprint;
    
    keysFound.clear();  // Clear the vector for a new run.
    

    password = RT->checkRainbowTable(stolenFingerprint, foundInRT);

    if(foundInRT)    // stolenFingerprint found in RT, step 1
    {
        password = RT->realPassword(password,stolenFingerprint);
        keysFound.push_back(password);
        foundInRT = false;
        cout << "Found a key step 1 : " << password << endl;
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

            password = RT->checkRainbowTable(fingerprint, foundInRT);  // Is this new fp in the RT ?

            if(foundInRT)    // Fingerprint found in RT
            {
                password = RT->realPassword(password,stolenFingerprint);
                
                bool toBeAdded = true;  // Voir si le password n'est pas déjà dans la liste.
                for (vector<bitset<12> >::iterator it = keysFound.begin(); it < keysFound.end() && toBeAdded; it++)
                    toBeAdded = (*it != password);
                
                if (toBeAdded) {
                    keysFound.push_back(password);
                    cout << "Found a key step 2 : " << j << " " << password << endl;
                }
                foundInRT = false;
            }

        }
    }


}

vector<bitset<12> > CrackerRainbow::getKeysFound() const
{
    return keysFound;
}
