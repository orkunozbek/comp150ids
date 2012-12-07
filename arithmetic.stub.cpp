#include "rpcstubhelper.h"
#include "TypeConverters.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"

#include "arithmetic.idl"


using namespace C150NETWORK;  // for all the comp150 utilities
void getFunctionNamefromStream();
void readNByte(char* buf, int i); 


int __add(int x,int y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingadd(x)");
	int retval = add(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromadd(x)");
	void* bytes = convertIntToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

int __divide(int x,int y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingdivide(x)");
	int retval = divide(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromdivide(x)");
	void* bytes = convertIntToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

int __multiply(int x,int y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingmultiply(x)");
	int retval = multiply(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned frommultiply(x)");
	void* bytes = convertIntToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

int __subtract(int x,int y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingsubtract(x)");
	int retval = subtract(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromsubtract(x)");
	void* bytes = convertIntToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}





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
  
  if (strcmp(funcName,"add") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	int x0= fromDataToInt(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	int x1= fromDataToInt(data1);
	__add(x0,x1);
  }
  else if (strcmp(funcName,"divide") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	int x0= fromDataToInt(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	int x1= fromDataToInt(data1);
	__divide(x0,x1);
  }
  else if (strcmp(funcName,"multiply") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	int x0= fromDataToInt(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	int x1= fromDataToInt(data1);
	__multiply(x0,x1);
  }
  else if (strcmp(funcName,"subtract") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	int x0= fromDataToInt(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	int x1= fromDataToInt(data1);
	__subtract(x0,x1);
  }

  
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

