#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "TypeConverters.h"

#include "arithmetic.idl"
//INSERT_IDL_HEADERS_HERE

using namespace C150NETWORK;  // for all the comp150 utilities 


int add(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("add")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("add", strlen("add")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: add received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add successful return from remote cal");
	return 5;

}

int divide(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("divide")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("divide", strlen("divide")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: divide received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide successful return from remote cal");

	return 5;
}

int multiply(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("multiply")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("multiply", strlen("multiply")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: multiply received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply successful return from remote cal");

	return 5;
}

int subtract(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("subtract")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("subtract", strlen("subtract")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: subtract received invalid response from the server");
	}
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract successful return from remote cal");

	return 5;
}

//INSERT_PROXIES_HERE


