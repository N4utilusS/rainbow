//
//  DES.cpp
//  Rainbow
//
//  Created by Anthony Debruyn on 18/10/13.
//  Copyright (c) 2013 Anthony Debruyn. All rights reserved.
//

#include <bitset>
#include "DESNote.h"

/************************ Copy paste no-brain avec CBC --> ECB ************************/

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "des.h"
using CryptoPP::DES;

#include "modes.h"
using CryptoPP::ECB_Mode;

#include "secblock.h"
using CryptoPP::SecByteBlock;

using namespace std;

bitset<24> DES(bitset<64> msg, bitset<64> key2)
{
    AutoSeededRandomPool prng;
    
	SecByteBlock key(DES::DEFAULT_KEYLENGTH);
	prng.GenerateBlock(key, key.size());
    
	byte iv[DES::BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));
    
	string plain = "ECB Mode Test";
	string cipher, encoded, recovered;
    
	/*********************************\
     \*********************************/
    
    // cout << "key length: " << DES::DEFAULT_KEYLENGTH << endl;
    // cout << "block size: " << DES::BLOCKSIZE << endl;
    
	// Pretty print key
	encoded.clear();
	StringSource(key, key.size(), true,
                 new HexEncoder(
                                new StringSink(encoded)
                                ) // HexEncoder
                 ); // StringSource
	cout << "key: " << encoded << endl;
    
	// Pretty print iv
	encoded.clear();
	StringSource(iv, sizeof(iv), true,
                 new HexEncoder(
                                new StringSink(encoded)
                                ) // HexEncoder
                 ); // StringSource
	cout << "iv: " << encoded << endl;
    
	/*********************************\
     \*********************************/
    
	try
	{
		cout << "plain text: " << plain << endl;
        
		ECB_Mode< DES >::Encryption e;
		e.SetKeyWithIV(key, key.size(), iv);
        
		// The StreamTransformationFilter adds padding
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)
                                                    ) // StreamTransformationFilter
                     ); // StringSource
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    
	/*********************************\
     \*********************************/
    
	// Pretty print
	encoded.clear();
	StringSource(cipher, true,
                 new HexEncoder(
                                new StringSink(encoded)
                                ) // HexEncoder
                 ); // StringSource
	cout << "cipher text: " << encoded << endl;
    
	/*********************************\
     \*********************************/
    
	try
	{
		ECB_Mode<DES>::Decryption d;
		d.SetKeyWithIV(key, key.size(), iv);
        
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)
                                                      ) // StreamTransformationFilter
                       ); // StringSource
        
		cout << "recovered text: " << recovered << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    
	/*********************************\
     \*********************************/
    
	return 0;
}