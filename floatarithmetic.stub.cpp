#include "rpcstubhelper.h"
#include "TypeConverters.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"

#include "floatarithmetic.idl"


using namespace C150NETWORK;  // for all the comp150 utilities
void getFunctionNamefromStream();
void readNByte(char* buf, int i); 


float __add(float x,float y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingadd(x)");
	float retval = add(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromadd(x)");
	void* bytes = convertFloatToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

float __divide(float x,float y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingdivide(x)");
	float retval = divide(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromdivide(x)");
	void* bytes = convertFloatToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

float __multiply(float x,float y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingmultiply(x)");
	float retval = multiply(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned frommultiply(x)");
	void* bytes = convertFloatToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

float __subtract(float x,float y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingsubtract(x)");
	float retval = subtract(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromsubtract(x)");
	void* bytes = convertFloatToByte(retval, "retval", NULL);
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
	float x0= fromDataToFloat(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	float x1= fromDataToFloat(data1);
	__add(x0,x1);
  }
  else if (strcmp(funcName,"divide") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	float x0= fromDataToFloat(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	float x1= fromDataToFloat(data1);
	__divide(x0,x1);
  }
  else if (strcmp(funcName,"multiply") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	float x0= fromDataToFloat(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	float x1= fromDataToFloat(data1);
	__multiply(x0,x1);
  }
  else if (strcmp(funcName,"subtract") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	float x0= fromDataToFloat(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	float x1= fromDataToFloat(data1);
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

