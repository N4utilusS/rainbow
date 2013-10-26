#include <iostream>
#include <bitset>
#include "CrackerRainbow.h"
#include <vector>

using namespace std;


int main()
{
    bitset<24> stolenFingerprint = 0x0f0000;

    bool play = true;
    char answer;

    do{
        cout << "Please enter your fingerprint" << endl;
        int a;
        for (int i = 0; i < 24; i++){
			 cin >> a;
			 stolenFingerprint.set(i, a);
		 }

        CrackerRainbow CR;

        CR.findPassword(stolenFingerprint);

        vector<bitset<12> > v = CR.getKeysFound();

        for (vector<bitset<12> >::iterator it = v.begin(); it < v.end(); it++)
            cout << *it << endl;

        cout << endl << "Do you want to play again ? (y/n)" << endl;
        cin >> answer;
        if(answer == 'n') play = false;

    } while(play);




    return 0;
}


// Check if the stolenFingerprint is in the rainbow table, and if yes, return the corresponding password

//bitset<12> checkRainbowTable(bitset<24> fingerprint, vector<bitset<12> > RTp, vector<bitset<24> > RTf)
//{
//    bitset<12> password;
//    int length = RTf.size();//if we put RTf.size() in the loop for, we got a warning...
//    for(int i=0; i < length; i++)
//        if(fingerprint == RTf[i])
//        {
//            password = RTp[i];
//            foundInRT = true;
//            break;
//        }
//    return password;    // Returns the password corresponding to the fingerprint.
//}

// Returns the password that corresponds to the stolenFingerprint


