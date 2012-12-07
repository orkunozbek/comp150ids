#include "rpcstubhelper.h"
#include "TypeConverters.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"

//INSERT_IDL_HEADERS_HERE

using namespace C150NETWORK;  // for all the comp150 utilities
void getFunctionNamefromStream();
void readNByte(char* buf, int i); 


//INSERT_FUNCTION_HEADERS

//INSERT_STUBS_HERE



void dispatchFunction() {
/*
  bool reverseBytes = reverse;
  int argLen;
  char* argLenPtr = (char*) & argLen;
  
  char* intBuf   = (char*) malloc(sizeof(int));
  readNByte(intBuf, sizeof(int));
  int funcNameLen = *(int*) intBuf;
  
  char* funcNameStr = (char*) malloc(funcNameLen+1);
  readNByte(funcNameStr, funcNameLen + 1); */
  char* intBuf   = (char*) malloc(sizeof(int));
  readNByte(intBuf, sizeof(int));
  int funcNameLen = *(int*)intBuf;
  char* funcName = (char*) malloc(funcNameLen);
  readNByte(funcName, funcNameLen);
  char* argLenPtr = (char*) malloc(sizeof(int));
  
//INSERT_DISPATCH_CODE
  
}

void readNByte(char* buf, int n){
  int readLen = 0;
  int readSoFar = 0;
  while (readSoFar != n){
    readLen = RPCSTUBSOCKET-> read(buf + readSoFar, (n - readSoFar));
    readSoFar += readLen;
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

