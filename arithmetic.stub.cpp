#include "rpcstubhelper.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>
#include "c150debug.h"
#include "TypeConverters.h"

#include "arithmetic.idl"


using namespace C150NETWORK;  // for all the comp150 utilities 
using namespace std;

void getFunctionNamefromStream();
void readNByte(char* buf, int i);

int __add(int x,int y){
	printf("ADD1");
	char doneBuffer[5] = "DONE";  // to write magic value DONE + null
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingadd(x)");
	int retval = add(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromadd(x)");
	void* bytes = convertIntToByte(retval ,"return", NULL); 
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

/*int __addFun(int x,int y){
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingaddFun(x)");
	int retval = addFun(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromaddFun(x)");
	//char* retBuf = (char*) convertIntToByte(retval, "retVal,NULL");
	return retval;

}*/

int __divide(int x,int y){
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingdivide(x)");
	int retval = divide(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromdivide(x)");
	//char* retBuf = (char*) convertIntToByte(retval, "retVal", NULL);
	return retval;

}

int __multiply(int x,int y){
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingmultiply(x)");
	int retval = multiply(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned frommultiply(x)");
	//char* retBuf = (char*) convertIntToByte(retval, "retVal", NULL);
	return retval;

}

/*void __printFunc(){
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingprintFunc()");
	printFunc();
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromprintFunc()");
	//char* retBuf = (char*) convertVoidToByte();
	
}*/

int __subtract(int x,int y){
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingsubtract(x)");
	int retval = subtract(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromsubtract(x)");
	//char* retBuf = (char*) convertIntToByte(retval, "retVal", NULL);
	return retval;

}





void dispatchFunction() { 
  char* intBuf   = (char*) malloc(sizeof(int));
  readNByte(intBuf, sizeof(int));
  int funcNameLen = *(int*)intBuf;
  
  char* funcName = (char*) malloc(funcNameLen);
  readNByte(funcName, funcNameLen);
  char* argLenPtr = (char*) malloc(sizeof(int));
  
  if (strcmp(funcName,"add") == 0){
  	cout << "inside add" << endl;
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)argLenPtr);
	memcpy(arg0, argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	int x0 = fromDataToInt(data0);
	cout << x0 << endl;

	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc((*(int*)argLenPtr));
	memcpy(arg1, argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	int x1 = fromDataToInt(data1);
	cout << x1 << endl;

	__add(x0,x1);
  }

 /* else if (strcmp(funcName,"addFun") == 0){
        readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc((*(int*)argLenPtr));
	readNByte(arg0,(*(int*)argLenPtr));
	int x0 = fromDataToInt(arg0);

	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc((*(int*)argLenPtr));
	readNByte(arg1,(*(int*)argLenPtr));
	int x1 = fromDataToInt(arg0);

	
	__addFun(x0,x1);
  }*/

  else if (strcmp(funcName,"divide") == 0){
			 readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc((*(int*)argLenPtr));
	readNByte(arg0,(*(int*)argLenPtr));
	int x0 = fromDataToInt(arg0);

	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc((*(int*)argLenPtr));
	readNByte(arg1,(*(int*)argLenPtr));
	int x1 = fromDataToInt(arg0);	
	
	__divide(x0,x1);
  }
	
  else if (strcmp(funcName,"subtract") == 0){
		 readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc((*(int*)argLenPtr));
	readNByte(arg0,(*(int*)argLenPtr));
	int x0 = fromDataToInt(arg0);

	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc((*(int*)argLenPtr));
	readNByte(arg1,(*(int*)argLenPtr));
	int x1 = fromDataToInt(arg0);	
	
	__subtract(x0,x1);
  }

  
}

void readNByte(char* buf, int n){
  int readlen = 0;
  int readSoFar = 0;
  while (readSoFar != n){
    readlen = RPCSTUBSOCKET-> read(buf + readSoFar, (n - readSoFar));
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
  
  
