#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <bitset>
using namespace std;

class Dictionary 
{
   public:
      Dictionary();
      void setAvailability(int row, bool status);
      bool getAvailability(int row);
   
   private:
      bool availability[4096];
};

#endif // DICTIONARY_H
