#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "TypeConverters.h"

#include "floatarithmetic.idl"
//INSERT_IDL_HEADERS_HERE

using namespace C150NETWORK;  // for all the comp150 utilities 

void getFunctionNamefromStream();
void readNByte(char* buf, int i);

float add(float x,float y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: invoking");
	int functionLength = strlen("add")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("add", strlen("add")+1);
	char *floatData0 = (char*)convertFloatToByte(x, "x", NULL);
	RPCPROXYSOCKET->write(floatData0, *(int*)floatData0);

	char *floatData1 = (char*)convertFloatToByte(y, "y", NULL);
	RPCPROXYSOCKET->write(floatData1, *(int*)floatData1);

	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("floatarithmetic.proxy.cpp: add received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	float retval = fromDataToFloat(data0);
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: add successful return from remote cal");
	return retval;


}

float divide(float x,float y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: invoking");
	int functionLength = strlen("divide")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("divide", strlen("divide")+1);
	char *floatData0 = (char*)convertFloatToByte(x, "x", NULL);
	RPCPROXYSOCKET->write(floatData0, *(int*)floatData0);

	char *floatData1 = (char*)convertFloatToByte(y, "y", NULL);
	RPCPROXYSOCKET->write(floatData1, *(int*)floatData1);

	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("floatarithmetic.proxy.cpp: divide received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	float retval = fromDataToFloat(data0);
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: divide successful return from remote cal");
	return retval;


}

float multiply(float x,float y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: invoking");
	int functionLength = strlen("multiply")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("multiply", strlen("multiply")+1);
	char *floatData0 = (char*)convertFloatToByte(x, "x", NULL);
	RPCPROXYSOCKET->write(floatData0, *(int*)floatData0);

	char *floatData1 = (char*)convertFloatToByte(y, "y", NULL);
	RPCPROXYSOCKET->write(floatData1, *(int*)floatData1);

	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("floatarithmetic.proxy.cpp: multiply received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	float retval = fromDataToFloat(data0);
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: multiply successful return from remote cal");
	return retval;


}

float subtract(float x,float y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: invoking");
	int functionLength = strlen("subtract")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("subtract", strlen("subtract")+1);
	char *floatData0 = (char*)convertFloatToByte(x, "x", NULL);
	RPCPROXYSOCKET->write(floatData0, *(int*)floatData0);

	char *floatData1 = (char*)convertFloatToByte(y, "y", NULL);
	RPCPROXYSOCKET->write(floatData1, *(int*)floatData1);

	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("floatarithmetic.proxy.cpp: subtract received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	float retval = fromDataToFloat(data0);
	c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: subtract successful return from remote cal");
	return retval;


}

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


