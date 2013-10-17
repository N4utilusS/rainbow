#include <iostream>
#include <queue>
#include <vector>
#include <bitset>
//#include <Crypto++> //need to download it...

using namespace std;

bool cont=false; //global variable

bitset<12> checkRainbowTable(bitset<24>, vector<bitset<12> >, vector<bitset<24> >);
bitset<12> realPassword(bitset<12>, bitset<24>);
bitset<24> hashing(bitset<12>);
bitset<12> reduction(bitset<24>,int);
bitset<12> reduction1(bitset<24> fingerprint);
bitset<12> reduction2(bitset<24> fingerprint);
bitset<12> reduction3(bitset<24> fingerprint);
bitset<12> reduction4(bitset<24> fingerprint);

int main()
{
   bitset<12> password;
   bitset<24> fingerprint;
   bitset<24> stolenFingerprint=0x0f0000;
   queue<bitset<24> > fifo;

   //Rainbow Table
   vector<bitset<12> > RTp(0);
   vector<bitset<24> > RTf(0);

   //make dico
   bitset<12> dico[4096][2];
   bitset<12> pass[4];
   for(int i=0;i<4096;i++)
      dico[i][0]=i;
   //make RT
   for(int i=0;i<4096;i++)
   {
      if(dico[i][1]==0) 
      {
	 pass[0]=dico[i][0];
	 for(int j=1;j<=4;j++) 
	 {
	    fingerprint=hashing(pass[j-1]);
	    pass[j-1]=reduction(fingerprint,j);
	 }
	 fingerprint=hashing(pass[4]);
	 password=checkRainbowTable(fingerprint,RTp,RTf); //check if the fingerprint is already in the table, in order to avoid collisions
	 if(cont==true)
	    cont=false;
	 else
	 {
	    RTp.push_back(dico[i][0]);
	    RTf.push_back(fingerprint);
	    for(int j=0;j<4;j++)
	       dico[pass[j].to_ulong()][1]=1;
	 } 
      }
   }

   //main algorithm
   password=checkRainbowTable(stolenFingerprint,RTp,RTf);
   if(cont==true)
   {
      password=realPassword(password,stolenFingerprint);
      cout << password << endl;
   }
   else
   {
      bool a=true;
      fingerprint=stolenFingerprint;
      int j=1;
      while(a)
      {
	 for(int i=j; i<=4; i++)
	 {
	    password=reduction(fingerprint,i);
	    fingerprint=hashing(password);
	 }
	 password=checkRainbowTable(fingerprint,RTp,RTf);
	 if(cont==true)
	 {
	    password=realPassword(password,fingerprint);
	    a=false;
	 }
	 else
	 {
	    j++;
	    fifo.push(fingerprint);
	 }
   	 if(j==4)
	 {
	     j = 1;
	    fingerprint=fifo.front();
	    fifo.pop();
	 }
      }
   }
   return 0;
}


//check if the stolenFingerprint is in the rainbow table, and if yes, return the corresponding password
bitset<12> checkRainbowTable(bitset<24> stolenFingerprint, vector<bitset<12> > RTp, vector<bitset<24> > RTf)
{
   bitset<12> password;
   bool a=true;
   int length=RTf.size();//if we put RTf.size() in the loop for, we got a warning...
   for(int i=0; i<length && a==true; i++)
      if(stolenFingerprint==RTf[i])
      {
      	 password=RTp[i];
	 a=false;
	 cont=true;
      }
   return password;
}

//return the password that corresponds to the stolenFingerprint
bitset<12> realPassword(bitset<12> password, bitset<24> stolenFingerprint)
{
   bool a=true;
   cont=false;
   bitset<24> fingerprint;
   for(int i=1;i<=4 && a==true;i++) //!--! 4?? if not, do a while(a)
   {
      fingerprint=hashing(password);
      if(fingerprint==stolenFingerprint)
   	 a=false;
      else
	 password=reduction(fingerprint,i);
   }
   return password;
}

/**************************************** NEED TO IMPLEMENT FROM HERE *******************************************/
//hashing
bitset<24> hashing(bitset<12> password)
{
   const bitset<64> msg = 0x0000000000000000;
   bitset<24> fingerprint;
   fingerprint=0x001000;
   return fingerprint;
}


bitset<12> reduction(bitset<24> fingerprint, int i)
{
   bitset<12> password;
   if(i==1)
      password=reduction1(fingerprint);
   if(i==2)
      password=reduction2(fingerprint);
   if(i==3)
      password=reduction3(fingerprint);
   else
      password=reduction4(fingerprint);
   return password;
}

//take the 12 least bits
bitset<12> reduction1(bitset<24> fingerprint)
{
   bitset<12> password;
   for(int i=12;i<24;i++)
      password[i-12]=fingerprint[i];
   return password;
}

//take the 12 first bits
bitset<12> reduction2(bitset<24> fingerprint)
{
   bitset<12> password;
   for(int i=0;i<12;i++)
      password[i]=fingerprint[i];
   return password;
}

//take one bit in two (even)
bitset<12> reduction3(bitset<24> fingerprint)
{
   bitset<12> password;
   for(int i=0;i<24;i++)
      if(i%2==0)
	 password[i/2]=fingerprint[i];
   return password;
}

//take one bit in two (odd)
bitset<12> reduction4(bitset<24> fingerprint)
{
   bitset<12> password;
   for(int i=0;i<24;i++)
      if(i%2==1)
	 password[(i-1)/2]=fingerprint[i];
   return password;
}
