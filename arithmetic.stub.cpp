#include "rpcstubhelper.h"
#include "TypeConverters.h"
#include <cstdio>
#include <cstring>
#include "c150debug.h"

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





int __VertexAddYPos(Vertex x,Vertex y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingVertexAddYPos(x)");
	int retval = VertexAddYPos(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromVertexAddYPos(x)");
	void* bytes = convertIntToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

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

Rectangle __createRectangle(Vertex x,Vertex y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingcreateRectangle(x)");
	Rectangle retval = createRectangle(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromcreateRectangle(x)");
	void* bytes = convertRectangleToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

Vertex __createVertex(int x,int y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingcreateVertex(x)");
	Vertex retval = createVertex(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromcreateVertex(x)");
	void* bytes = convertVertexToByte(retval, "retval", NULL);
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

Student __getStudent(int id){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokinggetStudent(i)");
	Student retval = getStudent(id);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromgetStudent(i)");
	void* bytes = convertStudentToByte(retval, "retval", NULL);
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

int __rectangleAdd(Rectangle r1,Rectangle r2){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingrectangleAdd(r1r)");
	int retval = rectangleAdd(r1,r2);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromrectangleAdd(r1r)");
	void* bytes = convertIntToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

float __rectangleCornerDistance(Rectangle r1){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingrectangleCornerDistance(r)");
	float retval = rectangleCornerDistance(r1);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromrectangleCornerDistance(r)");
	void* bytes = convertFloatToByte(retval, "retval", NULL);
	RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
	RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);
	return retval;

}

int __studentAdd(Student s,Student t){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingstudentAdd(s)");
	int retval = studentAdd(s,t);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromstudentAdd(s)");
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

int __vertexAddXPos(Vertex x,Vertex y){
	char doneBuffer[5] = "DONE";
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: invokingvertexAddXPos(x)");
	int retval = vertexAddXPos(x,y);
	c150debug->printf(C150RPCDEBUG,"simplefunction.stub.cpp: returned fromvertexAddXPos(x)");
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
  
  if (strcmp(funcName,"VertexAddYPos") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	Vertex x0= *fromDataToVertex(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	Vertex x1= *fromDataToVertex(data1);
	__VertexAddYPos(x0,x1);
  }
  else if (strcmp(funcName,"add") == 0){
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
  else if (strcmp(funcName,"createRectangle") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	Vertex x0= *fromDataToVertex(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	Vertex x1= *fromDataToVertex(data1);
	__createRectangle(x0,x1);
  }
  else if (strcmp(funcName,"createVertex") == 0){
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
	__createVertex(x0,x1);
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
  else if (strcmp(funcName,"getStudent") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	int x0= fromDataToInt(data0);
	__getStudent(x0);
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
  else if (strcmp(funcName,"rectangleAdd") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	Rectangle x0= *fromDataToRectangle(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	Rectangle x1= *fromDataToRectangle(data1);
	__rectangleAdd(x0,x1);
  }
  else if (strcmp(funcName,"rectangleCornerDistance") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	Rectangle x0= *fromDataToRectangle(data0);
	__rectangleCornerDistance(x0);
  }
  else if (strcmp(funcName,"studentAdd") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	Student x0= *fromDataToStudent(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	Student x1= *fromDataToStudent(data1);
	__studentAdd(x0,x1);
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
  else if (strcmp(funcName,"vertexAddXPos") == 0){
	readNByte(argLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg0 , argLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)argLenPtr) - sizeof(int));
	Vertex x0= *fromDataToVertex(data0);
	readNByte(argLenPtr, sizeof(int));
	char* arg1 = (char*) malloc(*(int*)argLenPtr);
	memcpy(arg1 , argLenPtr, sizeof(int));
	char *data1 = arg1;
	arg1 += sizeof(int);
	readNByte(arg1, (*(int*)argLenPtr) - sizeof(int));
	Vertex x1= *fromDataToVertex(data1);
	__vertexAddXPos(x0,x1);
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

