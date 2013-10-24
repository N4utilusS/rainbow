#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>

using namespace std;

vector<bitset<24> > writePossRed(vector<bitset<24> >);
vector<bitset<24> > readPossRed();
void initialHashing(bitset<24> [4096]);
vector< vector<int> > initialCollision(vector< vector<int> >, bitset<24> [4096]);
void displayInitialCollision(vector< vector<int> >);
void checkReduction(vector<bitset<24> >, bitset<24> [4096], int[][2]);
bitset<12> reduction(bitset<24>,bitset<24>);

int main() 
{
   bitset<24> num;
   vector<bitset<24> > PossRed;

   //Possible Reductions
   PossRed=writePossRed(PossRed);
   
   //hash all the passwords of the dictionary
   bitset<24> tabFingerprint[4096];
   initialHashing(tabFingerprint);
   
   //check how many collisions we have initially with the hash function 
   vector< vector<int> > tabCollisions;
   tabCollisions=initialCollision(tabCollisions,tabFingerprint);

   //display all the passwords which produce some collisions
   displayInitialCollision(tabCollisions);
      
   //check all the reduction functions
   int size=PossRed.size();
   int tabCol[size][2];
   checkReduction(PossRed, tabFingerprint, tabCol);
   return 0;
}

/******************************************************************************************/

//Compute all the possible reduction function and write it in a file named "PossRed.txt"
//!--! need to check if this file exists already...
vector<bitset<24> > writePossRed(vector<bitset<24> > PossRed)
{
   bitset<24> num;
   bool cont=true;
   int numberOf1=0, size=0;
   ofstream file;
   file.open("PossRed.txt");

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
	 cout << numberOf1 << "-" << PossRed[size-1] << endl;
	 file << PossRed[size-1] << endl;
      }
      cont=true;
      numberOf1=0;
   }
   file.close();
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

//hash all the passwords of the dictionary
void initialHashing(bitset<24> tabFingerprint[4096])
{
   for(int i=0; i<4096; i++)
      tabFingerprint[i]=hash(i);
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
   ofstream file;
   file.open("InitialCollision.txt");
   //cout << "Size of tabCollisions : " << size << endl;
   file << "Size of tabCollisions : " << size << endl;
   for(int i=0; i<size; i++)
   {
      size1=tabCollisions[i].size();
      for(int j=0; j<size1; j++)
      {
	 if(j==0)
	 {
	    //cout << "Number of collisions : " << tabCollisions[i][j] << endl;
	    file << "Number of collisions : " << tabCollisions[i][j] << endl;
	 }
	 else
	 {
	    passwordCollision=tabCollisions[i][j];
	    //cout << "Password concerned by this collision: " << passwordCollision << endl;
	    file << "Password concerned by this collision: " << passwordCollision << endl;
	 }
      }
   }
   file.close();
}

//check all the reduction functions
void checkReduction(vector<bitset<24> > PossRed, bitset<24> tabFingerprint[4096], int tabCol[][2])
{
   bitset<12> password;
   int size=PossRed.size(), pass=0; //size=2,704,156
   int tabPass[4096];
   //int tabCol[size][2];
   bool goodRed=true;

   //init
   for(int i=0; i<4096; i++)
      tabPass[i]=0;
   for(int i=0; i<size; i++)
   {
      tabCol[i][0]=0; //will contain number of collisions
      tabCol[i][1]=i; //will contain the "function reduction" (which can be accessed by PossRed[i]) which corresponds to this number of collisions
   }

   //main algo to check all the reduction functions
   //!--! will need to use tabCollisions and a counter...
   for(int i=0; i<size; i++)
   {
      cout << i << endl;
      for(int j=0; j<4096; j++)
	 tabPass[j]=0;

      for(int j=0; j<4096 && goodRed==true; j++) //4096*2,704,156 = 11,076,222,976 //it will take some times before getting a result...
      {
	 password=reduction(tabFingerprint[j],PossRed[i]);
	 if(password==j) //i.e. if password=initial password then it's not good
	    goodRed=false;
	 else
	 {
	    pass=password.to_ulong();
	    tabPass[pass]++;
	    if(tabPass[pass]>1) //then collision
	       tabCol[i][0]++;
	 }
      }
      goodRed=true;
   }
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
