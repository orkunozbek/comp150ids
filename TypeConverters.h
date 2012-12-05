#ifndef TYPE_CONVERTERS_H
#define TYPE_CONVERTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>
#include <map>

using namespace std;

enum TYPE {VOID, INT, FLOAT, STRING};
size_t getIntFieldSize(string fieldName);
size_t getFloatFieldSize(string fieldName);
size_t getStringFieldSize(string fieldName, string str);
void *convertIntToByte(int i, string fieldName, char *data);
void *convertFloatToByte(float f, string fieldName, char *data);
void *convertStringToByte(string str, string fieldName, char *data);
int fromDataToInt(char* data);
float fromDataToFloat(char *data);
char * fromDataToString(char *data);

#endif
