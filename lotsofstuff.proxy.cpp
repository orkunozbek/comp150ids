#include "rpcproxyhelper.h"

#include <cstdio>
#include <cstring>
#include "c150debug.h"
#include "TypeConverters.h"


#include "lotsofstuff.idl"


using namespace C150NETWORK;  // for all the comp150 utilities 

void getFunctionNamefromStream();
void readNByte(char* buf, int i);

size_t getMTFieldSize(MT s, string fieldName);
MT* fromDataToMT(char *data);
void* convertMTToByte(MT s, string fieldName,char *data);
size_t getPersonFieldSize(Person s, string fieldName);
Person* fromDataToPerson(char *data);
void* convertPersonToByte(Person s, string fieldName,char *data);
size_t getStructWithArraysFieldSize(StructWithArrays s, string fieldName);
StructWithArrays* fromDataToStructWithArrays(char *data);
void* convertStructWithArraysToByte(StructWithArrays s, string fieldName,char *data);
size_t getThreePeopleFieldSize(ThreePeople s, string fieldName);
ThreePeople* fromDataToThreePeople(char *data);
void* convertThreePeopleToByte(ThreePeople s, string fieldName,char *data);
size_t get__Person_10_FieldSize(Person arr[10], string fieldName);
void *convert__Person_10_ToByte(Person arr[10], string fieldName, char *data);
void fromDataTo__Person_10_(char *data, Person arr[10]);
size_t get__int_1000_FieldSize(int arr[1000], string fieldName);
void *convert__int_1000_ToByte(int arr[1000], string fieldName, char *data);
void fromDataTo__int_1000_(char *data, int arr[1000]);
size_t get__int_100_FieldSize(int arr[100], string fieldName);
void *convert__int_100_ToByte(int arr[100], string fieldName, char *data);
void fromDataTo__int_100_(char *data, int arr[100]);
size_t get__int_100__1000_FieldSize(int arr[100][1000], string fieldName);
void *convert__int_100__1000_ToByte(int arr[100][1000], string fieldName, char *data);
void fromDataTo__int_100__1000_(char *data, int arr[100][1000]);
size_t get__int_15_FieldSize(int arr[15], string fieldName);
void *convert__int_15_ToByte(int arr[15], string fieldName, char *data);
void fromDataTo__int_15_(char *data, int arr[15]);
size_t get__int_24_FieldSize(int arr[24], string fieldName);
void *convert__int_24_ToByte(int arr[24], string fieldName, char *data);
void fromDataTo__int_24_(char *data, int arr[24]);
size_t get__int_24__100_FieldSize(int arr[24][100], string fieldName);
void *convert__int_24__100_ToByte(int arr[24][100], string fieldName, char *data);
void fromDataTo__int_24__100_(char *data, int arr[24][100]);
size_t get__int_24__100__1000_FieldSize(int arr[24][100][1000], string fieldName);
void *convert__int_24__100__1000_ToByte(int arr[24][100][1000], string fieldName, char *data);
void fromDataTo__int_24__100__1000_(char *data, int arr[24][100][1000]);
size_t get__int_24__15_FieldSize(int arr[24][15], string fieldName);
void *convert__int_24__15_ToByte(int arr[24][15], string fieldName, char *data);
void fromDataTo__int_24__15_(char *data, int arr[24][15]);
size_t get__rectangle_200_FieldSize(rectangle arr[200], string fieldName);
void *convert__rectangle_200_ToByte(rectangle arr[200], string fieldName, char *data);
void fromDataTo__rectangle_200_(char *data, rectangle arr[200]);
size_t getrectangleFieldSize(rectangle s, string fieldName);
rectangle* fromDataTorectangle(char *data);
void* convertrectangleToByte(rectangle s, string fieldName,char *data);
size_t getsFieldSize(s s, string fieldName);
s* fromDataTos(char *data);
void* convertsToByte(s s, string fieldName,char *data);
size_t getMTFieldSize(MT s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;

	return len;
}


void* convertMTToByte(MT s, string fieldName,char *data){
	size_t len = getMTFieldSize(s, fieldName);
	if (data== NULL)
		data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	


	memcpy(data, &len, sizeof(int));
	return data;
}

MT* fromDataToMT(char *data){
	MT *s = new MT();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	

	

	return s;
}


size_t getPersonFieldSize(Person s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getStringFieldSize("firstname", s.firstname);
	len+=getStringFieldSize("lastname", s.lastname);
	len+=getIntFieldSize("age");

	return len;
}


void* convertPersonToByte(Person s, string fieldName,char *data){
	size_t len = getPersonFieldSize(s, fieldName);
	if (data== NULL)
		data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convertStringToByte(s.firstname, "firstname", tmp);
	tmp+=*tmp;
	convertStringToByte(s.lastname, "lastname", tmp);
	tmp+=*tmp;
	convertIntToByte(s.age, "age", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

Person* fromDataToPerson(char *data){
	Person *s = new Person();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	s->firstname= fromDataToString(tmp);
	tmp+=*tmp;
	s->lastname= fromDataToString(tmp);
	tmp+=*tmp;
	s->age= fromDataToInt(tmp);
	tmp+=*tmp;

	

	return s;
}


size_t getStructWithArraysFieldSize(StructWithArrays s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getIntFieldSize("aNumber");

	return len;
}


void* convertStructWithArraysToByte(StructWithArrays s, string fieldName,char *data){
	size_t len = getStructWithArraysFieldSize(s, fieldName);
	if (data== NULL)
		data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convertIntToByte(s.aNumber, "aNumber", tmp);
	tmp+=*tmp;
	convert__Person_10_ToByte(s.people, "people", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

StructWithArrays* fromDataToStructWithArrays(char *data){
	StructWithArrays *s = new StructWithArrays();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	s->aNumber= fromDataToInt(tmp);
	tmp+=*tmp;
	fromDataTo__Person_10_(tmp, s->people);
	tmp+=*tmp;

	

	return s;
}


size_t getThreePeopleFieldSize(ThreePeople s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getPersonFieldSize(s.p1,"p1");
	len+=getPersonFieldSize(s.p2,"p2");
	len+=getPersonFieldSize(s.p3,"p3");

	return len;
}


void* convertThreePeopleToByte(ThreePeople s, string fieldName,char *data){
	size_t len = getThreePeopleFieldSize(s, fieldName);
	if (data== NULL)
		data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convertPersonToByte(s.p1, "p1", tmp);
	tmp+=*tmp;
	convertPersonToByte(s.p2, "p2", tmp);
	tmp+=*tmp;
	convertPersonToByte(s.p3, "p3", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

ThreePeople* fromDataToThreePeople(char *data){
	ThreePeople *s = new ThreePeople();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	s->p1= *fromDataToPerson(tmp);
	tmp+=*tmp;
	s->p2= *fromDataToPerson(tmp);
	tmp+=*tmp;
	s->p3= *fromDataToPerson(tmp);
	tmp+=*tmp;

	

	return s;
}


size_t get__Person_10_FieldSize(Person arr[10], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int);


	for(int i0= 0; i0< 10; i0++)
	len+=getPersonFieldSize(arr[i0],"");

	return len;
}

void *convert__Person_10_ToByte(Person arr[10], string fieldName, char *data){
	size_t len = get__Person_10_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 1;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 10;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 5;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 10; i0++)
	convertPersonToByte(arr[i0],"", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__Person_10_(char *data, Person arr[10]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 10; i0++)
	arr[i0]= *fromDataToPerson(tmp),	tmp+=*tmp;




}


size_t get__int_1000_FieldSize(int arr[1000], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int);


	for(int i0= 0; i0< 1000; i0++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_1000_ToByte(int arr[1000], string fieldName, char *data){
	size_t len = get__int_1000_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 1;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 1000;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 1000; i0++)
	convertIntToByte(arr[i0], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_1000_(char *data, int arr[1000]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 1000; i0++)
	arr[i0]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_100_FieldSize(int arr[100], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int);


	for(int i0= 0; i0< 100; i0++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_100_ToByte(int arr[100], string fieldName, char *data){
	size_t len = get__int_100_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 1;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 100;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 100; i0++)
	convertIntToByte(arr[i0], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_100_(char *data, int arr[100]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 100; i0++)
	arr[i0]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_100__1000_FieldSize(int arr[100][1000], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int) + sizeof(int);


	for(int i0= 0; i0< 100; i0++)
	for(int i1= 0; i1< 1000; i1++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_100__1000_ToByte(int arr[100][1000], string fieldName, char *data){
	size_t len = get__int_100__1000_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 2;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 100;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	bound = 1000;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 100; i0++)
	for(int i1= 0; i1< 1000; i1++)
	convertIntToByte(arr[i0][i1], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_100__1000_(char *data, int arr[100][1000]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 100; i0++)
	for(int i1= 0; i1< 1000; i1++)
	arr[i0][i1]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_15_FieldSize(int arr[15], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int);


	for(int i0= 0; i0< 15; i0++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_15_ToByte(int arr[15], string fieldName, char *data){
	size_t len = get__int_15_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 1;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 15;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 15; i0++)
	convertIntToByte(arr[i0], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_15_(char *data, int arr[15]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 15; i0++)
	arr[i0]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_24_FieldSize(int arr[24], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int);


	for(int i0= 0; i0< 24; i0++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_24_ToByte(int arr[24], string fieldName, char *data){
	size_t len = get__int_24_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 1;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 24;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 24; i0++)
	convertIntToByte(arr[i0], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_24_(char *data, int arr[24]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 24; i0++)
	arr[i0]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_24__100_FieldSize(int arr[24][100], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int) + sizeof(int);


	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 100; i1++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_24__100_ToByte(int arr[24][100], string fieldName, char *data){
	size_t len = get__int_24__100_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 2;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 24;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	bound = 100;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 100; i1++)
	convertIntToByte(arr[i0][i1], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_24__100_(char *data, int arr[24][100]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 100; i1++)
	arr[i0][i1]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_24__100__1000_FieldSize(int arr[24][100][1000], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int) + sizeof(int) + sizeof(int);


	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 100; i1++)
	for(int i2= 0; i2< 1000; i2++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_24__100__1000_ToByte(int arr[24][100][1000], string fieldName, char *data){
	size_t len = get__int_24__100__1000_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 3;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 24;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	bound = 100;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	bound = 1000;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 100; i1++)
	for(int i2= 0; i2< 1000; i2++)
	convertIntToByte(arr[i0][i1][i2], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_24__100__1000_(char *data, int arr[24][100][1000]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 100; i1++)
	for(int i2= 0; i2< 1000; i2++)
	arr[i0][i1][i2]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__int_24__15_FieldSize(int arr[24][15], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int) + sizeof(int);


	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 15; i1++)
	len+=getIntFieldSize("");

	return len;
}

void *convert__int_24__15_ToByte(int arr[24][15], string fieldName, char *data){
	size_t len = get__int_24__15_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 2;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 24;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	bound = 15;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 1;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 15; i1++)
	convertIntToByte(arr[i0][i1], "", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__int_24__15_(char *data, int arr[24][15]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 24; i0++)
	for(int i1= 0; i1< 15; i1++)
	arr[i0][i1]= fromDataToInt(tmp),	tmp+=*tmp;




}


size_t get__rectangle_200_FieldSize(rectangle arr[200], string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=0 + sizeof(int);


	for(int i0= 0; i0< 200; i0++)
	len+=getrectangleFieldSize(arr[i0],"");

	return len;
}

void *convert__rectangle_200_ToByte(rectangle arr[200], string fieldName, char *data){
	size_t len = get__rectangle_200_FieldSize(arr,fieldName);
	
	if (data== NULL)
		data = (char*)malloc(len);
	
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 6;
	
	int numDims = 1;
	memcpy(tmp, &numDims, sizeof(int));
	tmp+=sizeof(int);
	int bound = 200;
	memcpy(tmp, &bound, sizeof(int));
	tmp+=sizeof(int);
	*tmp++ = 5;

	
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	for(int i0= 0; i0< 200; i0++)
	convertrectangleToByte(arr[i0],"", tmp), 	tmp+=*tmp;



	
	memcpy(data, &len, sizeof(int));
	return data;	
}

void fromDataTo__rectangle_200_(char *data, rectangle arr[200]){
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	
	tmp+=sizeof(int);
	tmp+=sizeof(int);
	tmp++;
	
	
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;

	for(int i0= 0; i0< 200; i0++)
	arr[i0]= *fromDataTorectangle(tmp),	tmp+=*tmp;




}


size_t getrectangleFieldSize(rectangle s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;
	len+=getIntFieldSize("x");
	len+=getIntFieldSize("y");

	return len;
}


void* convertrectangleToByte(rectangle s, string fieldName,char *data){
	size_t len = getrectangleFieldSize(s, fieldName);
	if (data== NULL)
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

rectangle* fromDataTorectangle(char *data){
	rectangle *s = new rectangle();
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


size_t getsFieldSize(s s, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1;

	return len;
}


void* convertsToByte(s s, string fieldName,char *data){
	size_t len = getsFieldSize(s, fieldName);
	if (data== NULL)
		data = (char*)malloc(len);
	char *tmp = data;
	tmp+= sizeof(int);
	*tmp++ = 5;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldLen);
	tmp += fieldLen;
	
	convert__int_24_ToByte(s.m1, "m1", tmp);
	tmp+=*tmp;
	convert__int_24__100_ToByte(s.m2, "m2", tmp);
	tmp+=*tmp;
	convert__int_24__100__1000_ToByte(s.m3, "m3", tmp);
	tmp+=*tmp;


	memcpy(data, &len, sizeof(int));
	return data;
}

s* fromDataTos(char *data){
	s *s = new s();
	char *tmp = data;
	//int len = *(int*)tmp;
	tmp+=sizeof(int);
	tmp++;
	int fieldNameLen = *(int*)tmp;
	tmp+=sizeof(int)+fieldNameLen;
	
	fromDataTo__int_24_(tmp, s->m1);
	tmp+=*tmp;
	fromDataTo__int_24__100_(tmp, s->m2);
	tmp+=*tmp;
	fromDataTo__int_24__100__1000_(tmp, s->m3);
	tmp+=*tmp;

	

	return s;
}






int area(rectangle r){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("area")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("area", strlen("area")+1);
	char *sData0 = (char*)convertrectangleToByte(r,"r", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: area received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: area successful return from remote cal");
	return retval;


}

Person findPerson(ThreePeople tp){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("findPerson")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("findPerson", strlen("findPerson")+1);
	char *sData0 = (char*)convertThreePeopleToByte(tp,"tp", NULL);
	RPCPROXYSOCKET->write(sData0, *(int*)sData0);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: findPerson received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	Person retval = *fromDataToPerson(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: findPerson successful return from remote cal");
	return retval;


}

void func1(){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("func1")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("func1", strlen("func1")+1);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: func1 received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: func1 successful return from remote cal");


}

void func2(){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("func2")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("func2", strlen("func2")+1);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: func2 received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: func2 successful return from remote cal");


}

void func3(){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("func3")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("func3", strlen("func3")+1);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: func3 received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: func3 successful return from remote cal");


}

float multiply(float x,float y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("multiply")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("multiply", strlen("multiply")+1);
	char *floatData0 = (char*)convertFloatToByte(x, "x", NULL);
	RPCPROXYSOCKET->write(floatData0, *(int*)floatData0);

	char *floatData1 = (char*)convertFloatToByte(y, "y", NULL);
	RPCPROXYSOCKET->write(floatData1, *(int*)floatData1);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: multiply received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	float retval = fromDataToFloat(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: multiply successful return from remote cal");
	return retval;


}

void searchRectangles(rectangle rects[200]){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("searchRectangles")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("searchRectangles", strlen("searchRectangles")+1);
	rectangle arrayData0 = (char*)convert__rectangle_200_ToByte(rects,"rects", NULL);
	RPCPROXYSOCKET->write(arrayData0, *(int*)arrayData0);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: searchRectangles received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: searchRectangles successful return from remote cal");


}

int showsArraysofArrays(int x[24],int y[24][15],int z[24][15]){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("showsArraysofArrays")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("showsArraysofArrays", strlen("showsArraysofArrays")+1);
	int arrayData0 = (char*)convert__int_24_ToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(arrayData0, *(int*)arrayData0);

	int arrayData1 = (char*)convert__int_24__15_ToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(arrayData1, *(int*)arrayData1);

	int arrayData2 = (char*)convert__int_24__15_ToByte(z,"z", NULL);
	RPCPROXYSOCKET->write(arrayData2, *(int*)arrayData2);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: showsArraysofArrays received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: showsArraysofArrays successful return from remote cal");
	return retval;


}

int sqrt(int x,int y){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("sqrt")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("sqrt", strlen("sqrt")+1);
	char *intData0 = (char*)convertIntToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(intData0, *(int*)intData0);

	char *intData1 = (char*)convertIntToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(intData1, *(int*)intData1);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: sqrt received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: sqrt successful return from remote cal");
	return retval;


}

int takesTwoArrays(int x[24],int y[24]){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("takesTwoArrays")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("takesTwoArrays", strlen("takesTwoArrays")+1);
	int arrayData0 = (char*)convert__int_24_ToByte(x,"x", NULL);
	RPCPROXYSOCKET->write(arrayData0, *(int*)arrayData0);

	int arrayData1 = (char*)convert__int_24_ToByte(y,"y", NULL);
	RPCPROXYSOCKET->write(arrayData1, *(int*)arrayData1);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: takesTwoArrays received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	int retval = fromDataToInt(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: takesTwoArrays successful return from remote cal");
	return retval;


}

string upcase(string s){
	char readBuffer[5];
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: invoking");
	int functionLength = strlen("upcase")+1;
	RPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));
	RPCPROXYSOCKET->write("upcase", strlen("upcase")+1);
	char *stringData0 = (char*)convertStringToByte(s, "s", NULL);
	RPCPROXYSOCKET->write(stringData0, *(int*)stringData0);

	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: returned from");
	RPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));
	if (strncmp(readBuffer,"DONE", sizeof(readBuffer))!=0) {
		throw C150Exception("lotsofstuff.proxy.cpp: upcase received invalid response from the server");
	}
	char* retLenPtr = (char*) malloc(sizeof(int));
	readNByte(retLenPtr, sizeof(int));
	char* arg0 = (char*) malloc(*(int *)retLenPtr);
	memcpy(arg0, retLenPtr, sizeof(int));
	char *data0 = arg0;
	arg0 += sizeof(int);
	readNByte(arg0, (*(int*)retLenPtr) - sizeof(int));
	string retval = fromDataToString(data0);
	c150debug->printf(C150RPCDEBUG,"lotsofstuff.proxy.cpp: upcase successful return from remote cal");
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


