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
    
    do{
        cout << "Please enter your fingerprint :" << endl;
        
        cin >> response;
        cout << response << endl;
        bitset<24> stolenFingerprint(stoi(response,0,0));
        cout << "bitset : " << stolenFingerprint << endl;
        
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
        
        
        
        cout << endl << "Do you want to play again ? (y/n) ";
        cin >> answer;
        
    } while(answer == 'y');
    
    return 0;
}
