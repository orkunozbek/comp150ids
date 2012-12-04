#include "TypeConverters.h"

// sizeof total data +  1 + fielName.lengt()+1 + 4
void *convertIntToByte(int i, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) +fieldName.length() + 1 + sizeof(int);
	char *data = (char*)malloc(len);
	char *tmp  = data+sizeof(int);
	*tmp++= 1;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldName.length()+1);
	tmp += fieldName.length()+1;
	memcpy(tmp, &i, sizeof(int));
	memcpy(data, &len, sizeof(int));
	return data;
}

// sizeof total data + 1 + fielName.lengt()+1 + 4
void *convertFloatToByte(float f, string fieldName){
	size_t len = sizeof(int) + 1 + sizeof(int) + fieldName.length() + 1 + sizeof(float);
	char *data = (char*)malloc(len);
	char *tmp  = data+sizeof(int);
	*tmp++= 2;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldName.length()+1);
	tmp += fieldName.length()+1;
	memcpy(tmp, &f, sizeof(float));
	memcpy(data, &len, sizeof(int));
	return data;
}


void *convertStringToByte(string str, string fieldName){
	size_t len = sizeof(int) +  1 + sizeof(int) + fieldName.length() + 1 + sizeof(int) + str.length() + 1;
	char *data = (char*) malloc(len);
	char *tmp  = data+sizeof(int);
	*tmp++=4;
	int fieldLen = fieldName.length()+1;
	memcpy(tmp, &fieldLen, sizeof(int) );
	tmp+=sizeof(int);
	memcpy(tmp, fieldName.c_str(), fieldName.length()+1);
	tmp += fieldName.length()+1;
	int strLen =str.length()+1;
	memcpy(tmp,&strLen, sizeof(int));
	tmp+=4;
	memcpy(tmp, str.c_str(), str.length()+1);
	memcpy(data, &len, sizeof(int));
	return data;
}

