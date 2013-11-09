#include <iostream>
#include <bitset>
#include "CrackerRainbow.h"
#include "HashReduc.h"
#include <vector>
//#include <string>

using namespace std;

int main()
{
   char answer;
   string response;
   CrackerRainbow CR;  // The cracking machine.
   int r;
   
  /* int count=0, incomplete=0;
   string tabFingerprint[4096];
   ifstream file("dicoFp.txt");
    if(file.good())
    {
        if(file.is_open())
        {
	   for(int i=0;i<4096;i++)
	   {
	       getline(file,response);
	       tabFingerprint[i]=response;
	   }
            file.close();
        }
        else
            cout << "Unable to open file." << endl;
    }   */ 
    
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
     // bitset<24> stolenFingerprint(string("001110111110110101101111")); //give a password
      
      /*response=tabFingerprint[count];
      bitset<24> stolenFingerprint(response);
      count++;*/

      cout << "This is your stolenFingerprint: " << stolenFingerprint << endl;
              
      // Find passwords if they exist
      CR.findPassword(stolenFingerprint);
        
      // Get the keys.
      vector<bitset<12> > v = CR.getKeysFound();
        
      // Printing the results, if any.
      if (!v.empty())
      {
	 cout << endl << "Grab the keys ! :" << endl;    
         for (vector<bitset<12> >::iterator it = v.begin(); it < v.end(); it++)
            cout << *it << " --> " << hashing(*it) << endl;
      } 
      else
      {
	 cout << endl << "Rainbow table is incomplete..." << endl; 
	 //incomplete++;
      }
        
	 cout << endl << "Do you wish to give another fingerprint ? (y/n) ";
	 cin >> answer;
        
    } while(answer == 'y');
   /*} while(count<4096);
   cout << "incomplete :" << incomplete << endl;*/
    
    return 0;
}
