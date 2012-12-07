#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "TypeConverters.h"


//INSERT_IDL_HEADERS_HERE

//INSERT_IDL_SPECIFIC_CONVERSIONS_HERE

using namespace C150NETWORK;  // for all the comp150 utilities 

void getFunctionNamefromStream();
void readNByte(char* buf, int i);

//INSERT_PROXIES_HERE


// Networking codes
void readNByte(char* buf, int n){
  int readlen = 0;
  int readSoFar = 0;
  while (readSoFar != n){
    readlen = RPCPROXYSOCKET-> read(buf + readSoFar, (n - readSoFar));
    readSoFar += readlen;
  }
}

char getArch(){
  int val = 0x10203040;
  char* x = (char*) &val;
  if (*x == 0x10)
    return 'B';
  else
    return 'L';
}

void reverseData(char* data, int dataLen){
  int left  = 0;
  int right = dataLen - 1;
  char tmpVal;
  
  while (left < right){
    tmpVal = data[right];
    data[right] = data[left];
    data[left]  = tmpVal;
    left++;
    right--;
  }
}


