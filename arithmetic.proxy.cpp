#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "TypeConverters.h"

#include "arithmetic.idl"
//INSERT_IDL_HEADERS_HERE

using namespace C150NETWORK;  // for all the comp150 utilities 


int add(int x, int y,){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	RPCPROXYSOCKET->write("add", strlen(add)+1);

	char *intData0 = (char*)convertIntToByte(x," x");
	RPCPROXYSOCKET->write(intData0, *intData0);


	char *intData1 = (char*)convertIntToByte(y," y");
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: add received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add successful return from remote cal");


}

int divide(int x, int y,){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	RPCPROXYSOCKET->write("divide", strlen(divide)+1);

	char *intData0 = (char*)convertIntToByte(x," x");
	RPCPROXYSOCKET->write(intData0, *intData0);


	char *intData1 = (char*)convertIntToByte(y," y");
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: divide received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide successful return from remote cal");


}

int multiply(int x, int y,){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	RPCPROXYSOCKET->write("multiply", strlen(multiply)+1);

	char *intData0 = (char*)convertIntToByte(x," x");
	RPCPROXYSOCKET->write(intData0, *intData0);


	char *intData1 = (char*)convertIntToByte(y," y");
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: multiply received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply successful return from remote cal");


}

int subtract(int x, int y,){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	RPCPROXYSOCKET->write("subtract", strlen(subtract)+1);

	char *intData0 = (char*)convertIntToByte(x," x");
	RPCPROXYSOCKET->write(intData0, *intData0);


	char *intData1 = (char*)convertIntToByte(y," y");
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: subtract received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract successful return from remote cal");


}

//INSERT_PROXIES_HERE
