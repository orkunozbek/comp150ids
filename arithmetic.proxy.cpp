#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "TypeConverters.h"


#include "arithmetic.idl"


using namespace C150NETWORK;  // for all the comp150 utilities 

void getFunctionNamefromStream();
void readNByte(char* buf, int i);

size_t getRectangleFieldSize(Rectangle s, string fieldName);
Rectangle* fromDataToRectangle(char *data);
void* convertRectangleToByte(Rectangle s, string fieldName,char *data);
size_t getStudentFieldSize(Student s, string fieldName);
Student* fromDataToStudent(char *data);
void* convertStudentToByte(Student s, string fieldName,char *data);
size_t getVertexFieldSize(Vertex s, string fieldName);
Vertex* fromDataToVertex(char *data);
void* convertVertexToByte(Vertex s, string fieldName,char *data);
size_t getRectangleFieldSize(Rectangle s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getVertexFieldSize(s.corner1,"corner1");
	len+=getVertexFieldSize(s.corner2,"corner2");

	return len;
}


void* convertRectangleToByte(Rectangle s, string fieldName,char *data=NULL){
	size_t len = getRectangleFieldSize(s, fieldName);
	data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convertVertexToByte(s.corner1, "corner1", tmp);
	tmp+=*tmp;
	convertVertexToByte(s.corner2, "corner2", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

Rectangle* fromDataToRectangle(char *data){
	Rectangle *s = new Rectangle();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	s->corner1= *fromDataToVertex(tmp);
	tmp+=*tmp;
	s->corner2= *fromDataToVertex(tmp);
	tmp+=*tmp;

	

	return s;
}


size_t getStudentFieldSize(Student s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getIntFieldSize("id");

	return len;
}


void* convertStudentToByte(Student s, string fieldName,char *data=NULL){
	size_t len = getStudentFieldSize(s, fieldName);
	data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convertIntToByte(s.id, "id", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

Student* fromDataToStudent(char *data){
	Student *s = new Student();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	s->id= fromDataToInt(tmp);
	tmp+=*tmp;

	

	return s;
}


size_t getVertexFieldSize(Vertex s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getIntFieldSize("x");
	len+=getIntFieldSize("y");

	return len;
}


void* convertVertexToByte(Vertex s, string fieldName,char *data=NULL){
	size_t len = getVertexFieldSize(s, fieldName);
	data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convertIntToByte(s.x, "x", tmp);
	tmp+=*tmp;
	convertIntToByte(s.y, "y", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

Vertex* fromDataToVertex(char *data){
	Vertex *s = new Vertex();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	s->x= fromDataToInt(tmp);
	tmp+=*tmp;
	s->y= fromDataToInt(tmp);
	tmp+=*tmp;

	

	return s;
}






int add(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("add")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("add", strlen("add")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *(int*)intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: add received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add successful return from remote cal");
	return retval;


}

Rectangle createRectangle(Vertex x,Vertex y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("createRectangle")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("createRectangle", strlen("createRectangle")+1);
	char *sData0 = (char*)convertVertexToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	char *sData1 = (char*)convertVertexToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(sData1, *(int*)sData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: createRectangle received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	Rectangle retval = *fromDataToRectangle(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: createRectangle successful return from remote cal");
	return retval;


}

Vertex createVertex(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("createVertex")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("createVertex", strlen("createVertex")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *(int*)intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: createVertex received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	Vertex retval = *fromDataToVertex(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: createVertex successful return from remote cal");
	return retval;


}

int divide(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("divide")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("divide", strlen("divide")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *(int*)intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: divide received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide successful return from remote cal");
	return retval;


}

Student getStudent(int id){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("getStudent")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("getStudent", strlen("getStudent")+1);
	char *intData0 = (char*)convertIntToByte(id,"id", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: getStudent received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	Student retval = *fromDataToStudent(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: getStudent successful return from remote cal");
	return retval;


}

int multiply(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("multiply")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("multiply", strlen("multiply")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *(int*)intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: multiply received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply successful return from remote cal");
	return retval;


}

int rectangleAdd(Rectangle r1,Rectangle r2){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("rectangleAdd")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("rectangleAdd", strlen("rectangleAdd")+1);
	char *sData0 = (char*)convertRectangleToByte(r1,"r1", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	char *sData1 = (char*)convertRectangleToByte(r2,"r2", NULL);
	RPCPROXYSOCKET->write(sData1, *(int*)sData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: rectangleAdd received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: rectangleAdd successful return from remote cal");
	return retval;


}

float rectangleCornerDistance(Rectangle r1){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("rectangleCornerDistance")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("rectangleCornerDistance", strlen("rectangleCornerDistance")+1);
	char *sData0 = (char*)convertRectangleToByte(r1,"r1", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: rectangleCornerDistance received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	float retval = fromDataToFloat(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: rectangleCornerDistance successful return from remote cal");
	return retval;


}

int studentAdd(Student s,Student t){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("studentAdd")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("studentAdd", strlen("studentAdd")+1);
	char *sData0 = (char*)convertStudentToByte(s,"s", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	char *sData1 = (char*)convertStudentToByte(t,"t", NULL);
	RPCPROXYSOCKET->write(sData1, *(int*)sData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: studentAdd received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: studentAdd successful return from remote cal");
	return retval;


}

int subtract(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("subtract")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("subtract", strlen("subtract")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *(int*)intData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: subtract received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract successful return from remote cal");
	return retval;


}

int vertexAddXPos(Vertex x,Vertex y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("vertexAddXPos")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("vertexAddXPos", strlen("vertexAddXPos")+1);
	char *sData0 = (char*)convertVertexToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	char *sData1 = (char*)convertVertexToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(sData1, *(int*)sData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: vertexAddXPos received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: vertexAddXPos successful return from remote cal");
	return retval;


}

int vertexAddYPos(Vertex x,Vertex y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: invoking");
	int functionLength = strlen("vertexAddYPos")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("vertexAddYPos", strlen("vertexAddYPos")+1);
	char *sData0 = (char*)convertVertexToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	char *sData1 = (char*)convertVertexToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(sData1, *(int*)sData1);

	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("arithmetic.proxy.cpp: vertexAddYPos received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: vertexAddYPos successful return from remote cal");
	return retval;


}




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


