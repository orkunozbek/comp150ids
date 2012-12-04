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
void *convertIntToByte(int i, string fieldName);
void *convertFloatToByte(float f, string fieldName);
void *convertStringToByte(string str, string fieldName);

#endif
