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
   
   cout << endl << "STEP1 of the algo:" << endl;
   if(RT->isInRT(stolenFingerprint,password))	//stolenFingerprint found in RT, step1
   {
      cout << "Found a fingerprint matching the stolen fingerprint in the Rainbow Table!!" << endl;
      cout << "The initial password corresponding to this fingerprint : " << password << endl;
      if(RT->FoundRealPassword(password, stolenFingerprint))
      {
      	 keysFound.push_back(password);
	 cout << endl << "The key is : " << password << endl;
	 fingerprint=hashing(password);
	 cout << "The corresponding fingerprint to this key : " << fingerprint << endl << endl;
      }
      else  // passwords don't match the stolen fingerprint, step 2
      {
	 cout << "None of these passwords give the stolen fingerprint." << endl;
	 step2algo(stolenFingerprint);
      }
   }
   else            // stolenFingerprint not found in RT, step 2
   {
      cout << "The stolen fingerprint was not found in the Rainbow Table..." << endl;
      step2algo(stolenFingerprint);
   }
}

void CrackerRainbow::step2algo(bitset<24> stolenFingerprint)
{
   bitset<12> password;
   bitset<24> fingerprint;
   cout << endl << "STEP2 of the algo:" << endl << endl;
      for(int j = 4; j >= 1; --j)
      {
         fingerprint = stolenFingerprint;
	 cout << fingerprint;
         for(int i = j; i <= 4; i++)
         {
	    cout << "->R" << i << "->";
            password = reduction(fingerprint,i);
	    cout << password << "->H->";
            fingerprint = hashing(password);
	    cout << fingerprint;
         }
	 cout << endl << "checking if this new fingerprint: " << fingerprint << " is in the table." << endl;
	 if(RT->isInRT(fingerprint,password)) 
	 {
	    cout << "Found a fingerprint in the table matching this new fingerprint in the Rainbow Table!!" << endl;
	    cout << "The initial password corresponding to this fingerprint : " << password << endl;
	    if(RT->FoundRealPassword(password, stolenFingerprint))    // Fingerprint found in RT
	    {
	       cout << endl << "Fingerprint found in the Rainbow Table." << endl;
	       cout << "The key is : " << password << endl;
	       fingerprint=hashing(password);
	       cout << "The corresponding fingerprint to this key : " << fingerprint << endl;
	       cout << "Checking if this password has already been discovered..." << endl;

	       bool toBeAdded = true;  // See if the password is already in the list.
	       for (vector<bitset<12> >::iterator it = keysFound.begin(); it < keysFound.end() && toBeAdded; it++)
		  toBeAdded = (*it != password); 
	       if (toBeAdded)
	       {
		  cout << "This password has not yet been discovered" << endl;
		  cout << "The key "<< password << " has been added." << endl << endl;
		  keysFound.push_back(password);
	       }
	       else
		  cout << "Password already discovered." << endl << endl;
	    }
	    else
	       cout << "None of these passwords give the stolen fingerprint." << endl << endl;
	 }
	 else
	    cout << "This fingerprint is not in the table." << endl << endl;
      }
}


vector<bitset<12> > CrackerRainbow::getKeysFound() const
{
   return keysFound;
}
