// g++ -O2 DES.cpp -L/Users/anthonydebruyn/Documents/ULB/MA1/Computer\ Security/Projets/Rainbow/Rainbow/rainbow/crypto++ -lcryptopp -o DES


#include <iostream>
#include <string>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"
#include <fstream>
#include <bitset>
#include <vector>

#include <iomanip>
#include <cstdio>

using namespace std;
using namespace CryptoPP;

string print(byte[]);
vector<bitset<24> > writePossRed(vector<bitset<24> >);
vector<bitset<24> > readPossRed();
vector< vector<int> > initialCollision(vector< vector<int> >, bitset<24> [4096]);
void displayInitialCollision(vector< vector<int> >);
void checkReduction(vector<bitset<24> >, bitset<24> [4096], short int[]);
bitset<12> reduction(bitset<24>,bitset<24>);
bitset<24> hashing(bitset<12> password);

int main(int argc, char* argv[])
{
    
    bitset<24> num;
    vector<bitset<24> > PossRed;
    
    //Possible Reductions
    PossRed=writePossRed(PossRed);
    
    //hash all the passwords of the dictionary
    bitset<24> tabFingerprint[4096];
    for(int i=0; i<4096; i++)
        tabFingerprint[i]=hashing(i);
    
    //check how many collisions we have initially with the hash function
    vector< vector<int> > tabCollisions;
    tabCollisions=initialCollision(tabCollisions,tabFingerprint);
    
    //display all the passwords which produce some collisions
    displayInitialCollision(tabCollisions);
    //~tabCollisions;
    
    //check all the reduction functions
    int size=PossRed.size();
    short int tabCol[size];
    checkReduction(PossRed, tabFingerprint, tabCol);

    
//    bitset<12> p0(string("000010001000")), p1(string("111011010001"));
//    cout << "Hashing " << endl << hashing(p0) << endl << hashing(p1) << endl;
	
	
	
//   byte key[DES::DEFAULT_KEYLENGTH]={0x00,0x00,0x00,0x00,0x00,0x00,0x04,0xC1};
//   byte plainText[DES::BLOCKSIZE]={0xA4,0xA0,0x00,0x59,0x7C,0x5E,0x20,0xC1};
//   byte cypheredText[DES::BLOCKSIZE];
//   byte decipheredText[DES::BLOCKSIZE];
//   string text;
//
//   text=print(key);
//   cout << "key: " << text << endl;
//   text=print(plainText);
//   cout << "plainText: " << text << endl;
//
//   //!--! faudra ajouter des try,catch... voir driver.cpp
//   //Encryption
//   ECB_Mode<DES>::Encryption e(key,sizeof(key));
//   e.ProcessData(cypheredText,plainText,sizeof(plainText));
//
//   //cout << "Algorithm: " << e.AlgorithmName() << endl;
//   text=print(cypheredText);
//   cout << "Cyphered Text: " << text << endl;
//
//   //Decryption
//   ECB_Mode<DES>::Decryption d(key,sizeof(key));
//   d.ProcessData(decipheredText,cypheredText,sizeof(cypheredText));
//
//   text=print(decipheredText);
//   cout << "Deciphered Text: " << text << endl;

   return 0;
}

bitset<24> hashing(bitset<12> password)
{
   byte plainText[8] = {0,0,0,0,0,0,0,0};
   byte cypheredText[8];
    bitset<24> fingerprint;
    
    
    // Transform into a byte tab.
    
    byte key[8] = {1,1,1,1,1,1,0,0};
    int i = 0;
	
    for (; i < 5; ++i) {
    	key[6] |= password[i];
		key[6] <<= 1;
    }
    
	key[6] |= (password[0] + password[1] + password[2] + password[3] + password[4] + 1) % 2;
	
	for (; i < 12; i++) {
		key[7] |= password[i];
		key[7] <<= 1;
	}
	
	key[7] |= (password[5] + password[6] + password[7] + password[8] + password[9] + password[10] + password[11] + 1) % 2;
    
    // Encryption
    
	ECB_Mode<DES>::Encryption e(key,sizeof(key));
    e.ProcessData(cypheredText,plainText,sizeof(plainText));
    
	// Convert a byte tabular into a bitset.
	
	fingerprint |= cypheredText[5];
	fingerprint <<= 8;
	fingerprint |= cypheredText[6];
	fingerprint <<= 8;
	fingerprint |= cypheredText[7];
	
    //
    
    return fingerprint;
}

//display -- Pretty print
string print(byte a[8])
{
   string text;
   text.clear();
   StringSource(a, sizeof(a), true, new HexEncoder(new StringSink(text)));
   return text;
}

//Compute all the possible reduction function and write it in a file named "PossRed.txt"
//!--! need to check if this file exists already...
vector<bitset<24> > writePossRed(vector<bitset<24> > PossRed)
{
    bitset<24> num;
    bool cont=true;
    int numberOf1=0, size=0;
    //ofstream file;
    //file.open("PossRed.txt");
    
    for(int i=0;i<16777216;i++) //2^24 = 16,777,216
    {
        num=i;
        for(int j=0;j<24 && cont==true;j++)
        {
            numberOf1+=num[j];
            if(numberOf1>12)
                cont=false;
        }
        if(numberOf1==12)
        {
            PossRed.push_back(num);
            size++;
            //cout << numberOf1 << "-" << PossRed[size-1] << endl;
            //file << PossRed[size-1] << endl;
        }
        cont=true;
        numberOf1=0;
    }
    //file.close();
    cout << "size:" << size << endl; //24!/(12!12!) = 2,704,156
    return PossRed;
}

//Read from a file named "PossRed.txt" all the possible reductions
//!--! need to convert a string into a bitset
//!--! maybe we will need some try catch
vector<bitset<24> > readPossRed()
{
    vector<bitset<24> > PossRed;
    string line;
    ifstream file("PossRed.txt");
    if(file.good())
    {
        if(file.is_open())
        {
            while(getline(file,line))
                cout << line << endl;
            file.close();
        }
        else
            cout << "Unable to open file." << endl;
    }
    else
        cout << "This file doesn't exist." << endl;
    return PossRed;
}

//check how many collisions we have initially with the hash function
//why do we do this? Because we want to avoid passwords that collide to appear again once reduced
vector< vector<int> > initialCollision(vector< vector<int> > tabCollisions, bitset<24> tabFingerprint[4096])
{
    int collision=0, r=0;
    bool cont=false;
    for(int i=0; i<4096; i++)
    {
        collision=0;
        for(int j=0; j<4096; j++) //4096*4096 = 16,777,216 = 2^24
            if(i!=j)
                if(tabFingerprint[i]==tabFingerprint[j])
                {
                    if(collision==0)
                    {
                        collision++;
                        vector<int> row(1,collision);
                        tabCollisions.push_back(row);
                        tabCollisions[r].push_back(i);
                        tabCollisions[r].push_back(j);
                        cont = true;
                    }
                    else
                    {
                        collision++;
                        tabCollisions[r][0] = collision;
                        tabCollisions[r].push_back(j);
                    }
                }
        if(cont==true)
            r++;
        cont=false;
    }
    return tabCollisions;
}

//display all the passwords which produce initially some collisions and write all those passwords in a file named "InitialCollision.txt"
//!--! need to check if this file exists already...
void displayInitialCollision(vector< vector<int> > tabCollisions)
{
    bitset<12> passwordCollision;
    int size = tabCollisions.size(), size1=0;
    //ofstream file;
    //file.open("InitialCollision.txt");
    //cout << "Size of tabCollisions : " << size << endl;
    //file << "Size of tabCollisions : " << size << endl;
    for(int i=0; i<size; i++)
    {
        size1=tabCollisions[i].size();
        for(int j=0; j<size1; j++)
        {
            if(j==0)
            {
                //cout << "Number of collisions : " << tabCollisions[i][j] << endl;
                //file << "Number of collisions : " << tabCollisions[i][j] << endl;
            }
            else
            {
                passwordCollision=tabCollisions[i][j];
                //cout << "Password concerned by this collision: " << passwordCollision << endl;
                //file << "Password concerned by this collision: " << passwordCollision << endl;
            }
        }
    }
    //file.close();
}

//check all the reduction functions
void checkReduction(vector<bitset<24> > PossRed, bitset<24> tabFingerprint[4096], short int tabCol[])
{
    bitset<12> password;
    int size=PossRed.size(), pass=0; //size=2,704,156
    int tabPass[4096];
    //int tabCol[size][2];
    bool goodRed=true;
    int fourGoodRed=0;
    
    //init
    // for(int i=0; i<4096; i++)
    //   tabPass[i]=0;
    for(int i=0; i<size; i++)
    {
        tabCol[i]=0; //will contain number of collisions
        // tabCol[i][1]=i; //will contain the "function reduction" (which can be accessed by PossRed[i]) which corresponds to this number of collisions
    }
    
    //main algo to check all the reduction functions
    //!--! will need to use tabCollisions and a counter...
    
    int **best = new int*[10]();
    for (int i = 0; i < 10; ++i) {
        best[i] = new int[3]();
        best[i][0] = -1;
        best[i][1] = 1500;
        best[i][2] = 0;
    }
    int presentBest = 1500, temp;
    
    int idPass = 0;
    
    for(int i=0, k = 0; i<size; i++, k++)
    {
        for(int j=0; j<4096; j++)
            tabPass[j]=0;
        idPass = 0;
        for(int j=0; j<4096; j++) //4096*2,704,156 = 11,076,222,976 //it will take some times before getting a result...
        {
            
            password=reduction(tabFingerprint[j],PossRed[i]);
            if(password==j) //i.e. if password=initial password then it's not good
            {
                idPass++;
            }
            else
            {
                pass=password.to_ulong();
                tabPass[pass]++;
                if(tabPass[pass]>1) //then collision
                    tabCol[i]++;
            }
        }
        
        if((temp = idPass + tabCol[i]) <= presentBest)
        {
            for (int k = 0; k < 10; ++k) {
                if (temp < (best[k][1] + best[k][2])) {
                    delete [] best[9];
                    for (int l = 9; l > k; --l) {
                        best[l] = best[l-1];
                    }
                    best[k] = new int[3]();
                    best[k][0] = i;
                    best[k][1] = idPass;
                    best[k][2] = tabCol[i];
                    presentBest = best[9][1] + best[9][2];
                    break;
                }
            }
            
        }
        //cout
        if (k == 10000) {
            cout << endl << i << "this temp = " << temp << endl;
            k = 0;
            for (int i = 0; i < 10; ++i) {
                cout << best[i][0] << "-" << best[i][1] << "-" << best[i][2] << endl;
            }
        }
    }
    
    cout << endl;
    for (int i = 0; i < 10; ++i) {
        cout << best[i][0] << "-" << best[i][1] << "-" << best[i][2] << endl;
        delete [] best[i];
    }
    delete [] best;
    
}
//just need to sort this tabCol

//return the password resulting in the application of the reduction function on the fingerprint
bitset<12> reduction(bitset<24> fingerprint, bitset<24> reductionFunction)
{
    bitset<12> password;
    int j=0, size=fingerprint.size(); //size=24
    for(int i=0; i<size; i++)
    {
        if(reductionFunction[i]==1)
        {
            password[j]=fingerprint[i];
            j++;
        }
    }
    return password;
}

