/*
 g++ -O2 main.cpp CrackerRainbow.cpp RainbowTable.cpp Dictionary.cpp HashReduc.cpp -L/Users/anthonydebruyn/Documents/ULB/MA1/Computer\ Security/Projets/Rainbow/Rainbow/rainbow/crypto++ -lcryptopp -o Project
 
 */

#include <iostream>
#include <bitset>
#include "CrackerRainbow.h"
#include "HashReduc.h"
#include <vector>

using namespace std;


int main()
{
    char answer;
    string response;
    CrackerRainbow CR;  // The cracking machine.
    int r;
    
    do{
        cout << endl << "Which type of value ? (2/10/16) :" << endl;
        
        cin >> response;
        
        cout << "Please enter your fingerprint :" << endl;
        
        if (response == "2") {
            cin >> response;
            r = stoi(response,0,2);
        } else if (response == "16"){
            cin >> response;
            r = stoi(response,0,16);
        } else {
            cin >> response;
            r = stoi(response,0,10);
        }
        
        bitset<24> stolenFingerprint(r);
        
        // Release the Kraken.
        
        CR.findPassword(stolenFingerprint);
        
        // Get the keys.
        
        vector<bitset<12> > v = CR.getKeysFound();
        
        // Printing the results, if any.
        
        if (!v.empty()) {
            cout << endl << "Grab the keys ! :" << endl;
            
            for (vector<bitset<12> >::iterator it = v.begin(); it < v.end(); it++)
                cout << *it << " --> " << hashing(*it) << endl;
        } else {
            cout << endl << "Rainbow table is not good..." << endl;
        }
        
        
        
        cout << endl << "Do you wish to release the Kraken again ? (y/n) ";
        cin >> answer;
        
    } while(answer == 'y');
    
    return 0;
}
