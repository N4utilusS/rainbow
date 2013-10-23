#include <iostream>
#include <string>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"

#include <iomanip>
#include <cstdio>

using namespace std;
using namespace CryptoPP;

string print(byte[]);

int main(int argc, char* argv[])
{
	bitset<12> password(std::string("111111111111"));
	byte plainText[8] = {0,0,0,0,0,0,0,0};
		byte cypheredText[8];
	    bitset<24> fingerprint;

	    
	    // Transformer en tableau de char.
	    
	    byte key[8] = {1,1,1,1,1,1,0,0};	// Tous les bits à 0.
	    int i = 0;
		
	    for (; i < 5; ++i) {
	    	key[6] |= password[i];	// Expression ternaire si ça ne marche pas.
			key[6] <<= 1;
	    }

		key[6] |= (password[0] + password[1] + password[2] + password[3] + password[4] + 1) % 2;
		
		for (; i < 12; i++) {
			key[7] |= password[i];	// Expression ternaire si ça ne marche pas.
			key[7] <<= 1;
		}
		
		key[7] |= (password[5] + password[6] + password[7] + password[8] + password[9] + password[10] + password[11] + 1) % 2;

/*
key: 0000000000003EFE
plainText: 0000000000000000
Cyphered Text: 44E4FB6F232DC44F
001011011100010001001111
*/
		
		string text;
		text=print(key);
		   cout << "key: " << text << endl;
		   text=print(plainText);
		   cout << "plainText: " << text << endl;
	    
	    // Fournir au constructeur de Encryption.

		ECB_Mode<DES>::Encryption e(key,sizeof(key));
	    e.ProcessData(cypheredText,plainText,sizeof(plainText));
	
	   text=print(cypheredText);
	   cout << "Cyphered Text: " << text << endl;

		// Convert a byte tabular into a bitset.
		
		fingerprint |= cypheredText[5];
		fingerprint <<= 8;
		fingerprint |= cypheredText[6];
		fingerprint <<= 8;
		fingerprint |= cypheredText[7];
		
		cout << fingerprint << endl;
	
	
	
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

//display -- Pretty print
string print(byte a[8])
{
   string text;
   text.clear();
   StringSource(a, sizeof(a), true, new HexEncoder(new StringSink(text)));
   return text;
}
