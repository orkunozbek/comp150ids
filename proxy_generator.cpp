#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;


string intToString ( int Number )
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}

string arrayTypeNameHelper(TypeDeclaration *typep){
	string typeNameStr = typep->getName();
    replace(typeNameStr.begin(),typeNameStr.end(), '[', '_');
	replace(typeNameStr.begin(),typeNameStr.end(), ']', '_');
	return typeNameStr;
}

string arrayTypeToVariableHelper(TypeDeclaration *typep){
	return "";
}

string createStructConversionFunction(string str, TypeDeclaration *typep){
	string name = "${STRUCT_NAME}";
	size_t found = str.find(name);
	while(found != string::npos){
		str.replace(found, name.length(), typep->getName());
		found = str.find(name, found+1);
	}
	
	vector<Arg_or_Member_Declaration *>& members = typep->getStructMembers();
	string size = "${APPEND_MEMBER_COPY}";
	string appendedStr = "";

    for(size_t memberNum=0; memberNum<members.size();memberNum++) {
      Arg_or_Member_Declaration* memp = members[memberNum];
      //ss << endl << "   " << memp->getType()->getName() << "  " << memp->getName();
      string type = memp->getType()->getName();
      string memberName = memp->getName();
      if (type == "int"){
          appendedStr.append("\tconvertIntToByte(s." + memberName + ", \"" + memberName+ "\", tmp);\n");
          appendedStr.append("\ttmp+=*tmp;\n");
      }
      else if(type == "float"){
          appendedStr.append("\tconvertFloatToByte(s." + memberName + ", \"" + memberName+ "\", tmp);\n");
          appendedStr.append("\ttmp+=*tmp;\n");
      }
      else if(type == "string"){
          appendedStr.append("\tconvertStringToByte(s." + memp->getName() + ", \"" + memp->getName() + "\", tmp);\n");
          appendedStr.append("\ttmp+=*tmp;\n");
      }else{
          typep = memp->getType();
          if(typep->isStruct()){
              appendedStr.append("\tconvert" + typep->getName() + "ToByte(s." + memp->getName() + ", \"" + memp->getName() + "\", tmp);\n");
              appendedStr.append("\ttmp+=*tmp;\n");
          }else if(typep->isArray()){
          	  appendedStr.append("\tconvert" + arrayTypeNameHelper(typep) + "ToByte(s." + memp->getName() + ", \"" + memp->getName() + "\", tmp);\n");
              appendedStr.append("\ttmp+=*tmp;\n");
          }
      }
    }
    found = str.find(size, found);
    str.replace(found, size.length(), appendedStr);
    
    
    string conversions = "${APPEND_MEMBER_CONVERSIONS}";
	appendedStr.clear();

    for(size_t memberNum=0; memberNum<members.size();memberNum++) {
      Arg_or_Member_Declaration* memp = members[memberNum];
      string type = memp->getType()->getName();
      string memberName = memp->getName();
      if (type == "int"){
          appendedStr.append("\ts->" + memberName + "= fromDataToInt(tmp);\n");
          appendedStr.append("\ttmp+=*tmp;\n");
      }
      else if(type == "float"){
           appendedStr.append("\ts->" + memberName + "= fromDataToFloat(tmp);\n");
           appendedStr.append("\ttmp+=*tmp;\n");
      }
      else if(type == "string"){
           appendedStr.append("\ts->" + memberName + "= fromDataToString(tmp);\n");
           appendedStr.append("\ttmp+=*tmp;\n");
      }
      else{
            typep = memp->getType();
            if(typep->isStruct()){
                appendedStr.append("\ts->" + memberName + "= *fromDataTo" + typep->getName() + "(tmp);\n");
                appendedStr.append("\ttmp+=*tmp;\n");
            }else if(typep->isArray()){
            	appendedStr.append("\tfromDataTo" + arrayTypeNameHelper(typep) + "(tmp, s->" +memberName+ ");\n");
                appendedStr.append("\ttmp+=*tmp;\n"); 
            }
        }
    }
    found = str.find(conversions, found);
    str.replace(found, conversions.length(), appendedStr);    
	
	return str;
}


string createStructSizeFunction(string str, TypeDeclaration *typep){
	string name = "${STRUCT_NAME}";
	size_t found = str.find(name);
	while(found != string::npos){
		str.replace(found, name.length(), typep->getName());
		found = str.find(name, found+1);
	}
	
	vector<Arg_or_Member_Declaration *>& members = typep->getStructMembers();
	string size = "${APPEND_TYPES}";
	string appendedStr = "";

    for(size_t memberNum=0; memberNum<members.size();memberNum++) {
      Arg_or_Member_Declaration* memp = members[memberNum];
      //ss << endl << "   " << memp->getType()->getName() << "  " << memp->getName();
      string type = memp->getType()->getName();
      
      if (type == "int")
  		appendedStr.append("\tlen+=getIntFieldSize(\"" + memp->getName() + "\");\n");
  	  else if(type == "float")
      	appendedStr.append("\tlen+=getFloatFieldSize(\"" + memp->getName() + "\");\n");
      else if(type == "string")
    	appendedStr.append("\tlen+=getStringFieldSize(\"" + memp->getName() + "\", s." + memp->getName() + ");\n");
      else{
          TypeDeclaration *typep = memp->getType();
          if(typep->isStruct()){
              appendedStr.append("\tlen+=get"+ typep->getName() +"FieldSize(s." + memp->getName() + ",\"" + memp->getName() + "\");\n");
          }
      }
    }
    found = str.find(size, found);
    str.replace(found, size.length(), appendedStr);
	
	return str;
}

string createArraySizeFunction(string str, TypeDeclaration *typep, string& functionPrototype){
    string typeNameStr = typep->getName();
    replace(typeNameStr.begin(),typeNameStr.end(), '[', '_');
	replace(typeNameStr.begin(),typeNameStr.end(), ']', '_');
    // Replace the type name
    string typeNameStrTag = "${ARRAY_TYPE_S}";
    size_t found = str.find(typeNameStrTag);
    if(found!=string::npos){
        str.replace(found, typeNameStrTag.length(), typeNameStr);
    }
    // Append the dim data representation length
    // Keep a vector of array dimensions
    string dimsDataStr = "\tlen+=0";
    string dataFieldSizeStr = "";
    string dimsStr = "";
    string argStr = "";
    TypeDeclaration *arrayType = typep->getArrayMemberType();
    int i = 0;
    dimsDataStr.append(" + sizeof(int)");
    dataFieldSizeStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(typep->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
    dimsStr.append("[i" + intToString(i) + "]");
    argStr.append("[" + intToString(typep->getArrayBound())+ "]");
    while(arrayType){
        i++;
        if(arrayType->isArray()){
        	argStr.append("[" + intToString(arrayType->getArrayBound())+ "]");
            dimsDataStr.append(" + sizeof(int)");
		    dataFieldSizeStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(arrayType->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
		    dimsStr.append("[i" + intToString(i) + "]");
			arrayType = arrayType->getArrayMemberType();
		}
		else{
            dimsDataStr.append(";\n");
            string typeName =arrayType->getName();
            
		    if (typeName == "int"){
          		dataFieldSizeStr.append("\tlen+=getIntFieldSize(\"\");\n");
          		argStr.insert(0, "int arr");
          	}
          	else if(typeName == "float"){
              	dataFieldSizeStr.append("\tlen+=getFloatFieldSize(\"\");\n");
              	argStr.insert(0, "float arr");
            }	
            else if(typeName == "string"){
            	dataFieldSizeStr.append("\tlen+=getStringFieldSize(\"\", arr" + dimsStr + ");\n");
            	argStr.insert(0, "string arr");
            }
			else{
                dataFieldSizeStr.append("\tlen+=get"+ typeName +"FieldSize(arr" + dimsStr + ",\"\");\n");
                argStr.insert(0, typeName + " arr");
            }
			arrayType = NULL;
		}
    }
    
    dimsDataStr.append("\n\n");
    dimsDataStr.append(dataFieldSizeStr);
    string appendTag = "${APPEND_DATA_CONVERSION}";
    found = str.find(appendTag);
    if(found != string::npos){
        str.replace(found, appendTag.length(), dimsDataStr);
    }
    
    
    
    string typeTag = "${ARRAY_TYPE}";
    found = str.find(typeTag);
    if(found != string::npos){
        str.replace(found, typeTag.length(), argStr);
    }    
    functionPrototype.append("size_t get" + typeNameStr + "FieldSize("+ argStr + ", string fieldName);\n");
    
    return str;
}


string createArrayConversionFunction(string str, TypeDeclaration *typep, string& functionPrototype){
    string typeNameStr = typep->getName();
    replace(typeNameStr.begin(),typeNameStr.end(), '[', '_');
	replace(typeNameStr.begin(),typeNameStr.end(), ']', '_');
    // Replace the type name
    string typeNameStrTag = "${ARRAY_TYPE_S}";
    size_t found = str.find(typeNameStrTag);
    while(found!=string::npos){
        str.replace(found, typeNameStrTag.length(), typeNameStr);
        found = str.find(typeNameStrTag, found+1);
    }
    
    
    // Append the dim data representation length
    // Keep a vector of array dimensions
    string dimsToBytes = "";
    string dataFieldSizeStr = "";
    string buildArrayStr = "";
    string dimsStr = "";
    string argStr = "";
    string itDimsStr = "";
    TypeDeclaration *arrayType = typep->getArrayMemberType();
    int i = 0;
    dataFieldSizeStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(typep->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
    buildArrayStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(typep->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
    dimsStr.append("[i" + intToString(i) + "]");
    argStr.append("[" + intToString(typep->getArrayBound())+ "]");
    dimsToBytes.append("\tint bound = " + intToString(typep->getArrayBound()) + ";\n");
    dimsToBytes.append("\tmemcpy(tmp, &bound, sizeof(int));\n");
    dimsToBytes.append("\ttmp+=sizeof(int);\n");
    itDimsStr.append("\ttmp+=sizeof(int);\n");
    while(arrayType){
        i++;
        if(arrayType->isArray()){
        	argStr.append("[" + intToString(arrayType->getArrayBound())+ "]");
		    dataFieldSizeStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(arrayType->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
            buildArrayStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(arrayType->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
		    dimsStr.append("[i" + intToString(i) + "]");
		    dimsToBytes.append("\tbound = " + intToString(arrayType->getArrayBound()) + ";\n");
            dimsToBytes.append("\tmemcpy(tmp, &bound, sizeof(int));\n");
            dimsToBytes.append("\ttmp+=sizeof(int);\n");
            itDimsStr.append("\ttmp+=sizeof(int);\n");
			arrayType = arrayType->getArrayMemberType();
		}
		else{
			
		    dimsToBytes.insert(0,"\tint numDims = " + intToString(i) + ";\n" + "\tmemcpy(tmp, &numDims, sizeof(int));\n" + "\ttmp+=sizeof(int);\n");
		    itDimsStr.insert(0, "\ttmp+=sizeof(int);\n");
		    itDimsStr.append("\ttmp++;\n");
            string typeName =arrayType->getName();
            
		    if (typeName == "int"){
          		dataFieldSizeStr.append("\tconvertIntToByte(arr" + dimsStr + ", \"\", tmp), ");
          		dataFieldSizeStr.append("\ttmp+=*tmp;\n");
          		buildArrayStr.append("\tarr" +dimsStr + "= fromDataToInt(tmp),");
                buildArrayStr.append("\ttmp+=*tmp;\n");
          		argStr.insert(0, "int arr");
                dimsToBytes.append("\t*tmp++ = 1;\n");
          	}
          	else if(typeName == "float"){
              	dataFieldSizeStr.append("\tconvertFloatToByte(arr" + dimsStr + ", \"\", tmp), ");
          		dataFieldSizeStr.append("\ttmp+=*tmp;\n");
          		buildArrayStr.append("\tarr" +dimsStr + "= fromDataToFloat(tmp),");
                buildArrayStr.append("\ttmp+=*tmp;\n");
              	argStr.insert(0, "float arr");
              	dimsToBytes.append("\t*tmp++ = 2;\n");
            }	
            else if(typeName == "string"){
            	dataFieldSizeStr.append("\tconvertStringToByte(arr" + dimsStr + ", \"\", tmp), ");
            	dataFieldSizeStr.append("\ttmp+=*tmp;\n");
            	buildArrayStr.append("\tarr" +dimsStr + "= fromDataToString(tmp),");
                buildArrayStr.append("\ttmp+=*tmp;\n");
            	argStr.insert(0, "string arr");
            	dimsToBytes.append("\t*tmp++ = 4;\n");
            }
			else{
                dataFieldSizeStr.append("\tconvert"+ typeName +"ToByte(arr" + dimsStr + ",\"\", tmp), ");
                dataFieldSizeStr.append("\ttmp+=*tmp;\n");
                buildArrayStr.append("\tarr" +dimsStr + "= *fromDataTo" + typeName + "(tmp),");
                buildArrayStr.append("\ttmp+=*tmp;\n");
                argStr.insert(0, typeName + " arr");
                dimsToBytes.append("\t*tmp++ = 5;\n");
            }
			arrayType = NULL;
		}
    }
    
    string appendDataType = "${APPEND_DATA_TYPE_AND_DIMENSIONS}";
    found = str.find(appendDataType);
    if(found != string::npos){
        str.replace(found, appendDataType.length(),  dimsToBytes);
    }
    dataFieldSizeStr.append("\n\n");
    string appendTag = "${APPEND_CONVERSIONS}";
    found = str.find(appendTag);
    if(found != string::npos){
        str.replace(found, appendTag.length(), dataFieldSizeStr);
    }
    
    buildArrayStr.append("\n\n");
    string buildArrTag = "${BUILD_ARRAY}";
    found = str.find(buildArrTag);
    if(found != string::npos){
        str.replace(found, buildArrTag.length(), buildArrayStr);
    }
    
    string itDimsTag = "${ITERATE_DIMS_AND_BASE_DATA}";
    found = str.find(itDimsTag);
    if(found != string::npos){
        str.replace(found, itDimsTag.length(), itDimsStr);
    }
    
    
    
    string typeTag = "${ARRAY_TYPE}";
    found = str.find(typeTag);
    while(found != string::npos){
        str.replace(found, typeTag.length(), argStr);
        found = str.find(typeTag, found+1);
    }    
    functionPrototype.append("void *convert" +typeNameStr+ "ToByte("+argStr+", string fieldName, char *data);\n");
    functionPrototype.append("void fromDataTo"+typeNameStr+"(char *data, "+argStr+");\n");
    return str;    
}

int main(int argc, char *argv[]){
	int argnum;

    if (argc < 2) {
      fprintf(stderr, "Syntax: %s  idlfile1 [idlfile...]*\n", argv[0]);
      exit (8);
    };
    
    
    
    string includeStr;
    string proxyCodeStr;
    string funcHeadStr;
    string funcCallStr;
    
    string funcRetTypeStr;
    string funcNameStr;
    string typeNameStr;
    string argNameStr;
    
    string partialStr;
    string str;
    string proxyFileStr;
    
    string argumentConversions;
    string conversionCode;
    string conversionFunctionHeaders;
    
    // Read the contents of proxy template
    ifstream t("proxy_template.cpp");

 	t.seekg(0, ios::end);  
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

 	str.assign((istreambuf_iterator<char>(t)),
    istreambuf_iterator<char>());
	t.close();
	
	t.open("structsizefunction");
	string structSizeStr;
	t.seekg(0, ios::end);   
	structSizeStr.reserve(t.tellg());
	t.seekg(0, ios::beg);
  	structSizeStr.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
  
  	t.close();
  	t.open("structconvertfunction");
  	string structConversionStr;
  	t.seekg(0, ios::end);   
  	structConversionStr.reserve(t.tellg());
  	t.seekg(0, ios::beg);
  	structConversionStr.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
  	t.close();
  	
  	t.open("arraysizefunction");
  	string arraySizeFunction;
  	t.seekg(0, ios::end);   
  	arraySizeFunction.reserve(t.tellg());
  	t.seekg(0, ios::beg);
  	arraySizeFunction.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
  	t.close();
  
  	t.open("arrayconversionfunction");
  	string arrayConversionFunction;
  	t.seekg(0, ios::end);   
  	arrayConversionFunction.reserve(t.tellg());
  	t.seekg(0, ios::beg);
  	arrayConversionFunction.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
  	t.close();
	
	//printf("1\n");
	
	
	for (argnum = 1; argnum < argc; argnum++) {
		proxyFileStr.clear();
		proxyFileStr.append(str);
		includeStr.clear();
		proxyCodeStr.clear();
		conversionCode.clear();
        conversionFunctionHeaders.clear();
		
      	
      	string idlFileNameStr(argv[argnum]);
      	string proxyFileNameStr = idlFileNameStr.substr(0, idlFileNameStr.find(".idl"));
      	proxyFileNameStr.append(".proxy.cpp");
      	ifstream idlFile(idlFileNameStr.c_str());
      	//printf("2\n");      	
      	Declarations parseTree(idlFile);
      	includeStr.append("#include \"");
      	includeStr.append(argv[argnum]);
      	includeStr.append("\"\n");
      	
      	// Build IDL specific Conversions
      	
      	std::map<std::string, TypeDeclaration*>::iterator iter;  
      	//printf("3\n");
		TypeDeclaration *typep;
		stringstream formattedType;
		for (iter = parseTree.types.begin(); iter != parseTree.types.end(); ++iter) {
		    typep = iter -> second;
		    formattedType.str("");      // empty the formatting buffer
		    if(typep->isStruct()){
		        conversionFunctionHeaders.append("size_t get" + typep->getName() +"FieldSize(" + typep->getName() + " s, string fieldName);\n");
		        conversionFunctionHeaders.append(typep->getName() +"* fromDataTo" + typep->getName() + "(char *data);\n");
		        conversionFunctionHeaders.append("void* convert" + typep->getName() + "ToByte(" + typep->getName() + " s, string fieldName,char *data);\n");
		    	string structFieldSizeFunction = structSizeStr;
		    	conversionCode.append(createStructSizeFunction(structFieldSizeFunction, typep));
		    	conversionCode.append("\n\n\n");
		    	string structConversionFunction = structConversionStr;
		    	conversionCode.append(createStructConversionFunction(structConversionFunction, typep));
		    	conversionCode.append("\n\n\n");
		    }else if(typep->isArray()){
				string arraySizeFunctionTmpStr = arraySizeFunction;
		        string functionPrototype = "";
		        conversionCode.append(createArraySizeFunction(arraySizeFunctionTmpStr, typep, functionPrototype));
		        string arrayConversionFunctionTmpStr = arrayConversionFunction;
		        conversionCode.append(createArrayConversionFunction(arrayConversionFunctionTmpStr, typep, functionPrototype));
		    	conversionFunctionHeaders.append(functionPrototype);
		    }
		} 
      	//printf("3\n");
      	map<string, FunctionDeclaration*>::iterator fiter;
      	FunctionDeclaration *functionp;
      	for (fiter = parseTree.functions.begin(); fiter != parseTree.functions.end(); ++fiter) {
      		functionp = fiter -> second;
      		funcHeadStr.clear();
      		funcCallStr.clear();
      		argumentConversions.clear();
      		funcRetTypeStr = functionp->getReturnType()->getName();
      		funcNameStr    = functionp->getName();
      		
      		funcHeadStr.append(funcRetTypeStr + " " + funcNameStr);
      		funcHeadStr.append("(");
      		ArgumentVector& args = functionp -> getArgumentVector();
      		size_t argsSize = args.size();
      		for(size_t argnum=0; argnum < argsSize; argnum++) {
			
      			Arg_or_Member_Declaration* argp = args[argnum];
      			typeNameStr = argp->getType()->getName();
      			argNameStr  = argp->getName();
      			
      			// Holds the value of argNum
				char strBuffer[33];
				snprintf(strBuffer, sizeof(strBuffer), "%d", (int)argnum);
				string strNum(strBuffer);
	  			if(typeNameStr == "int"){
	  				argumentConversions.append("\tchar *intData" + strNum + " = (char*)convertIntToByte(" + argNameStr + ",\"" + argNameStr + "\", NULL);\n");
	  				argumentConversions.append("\tRPCPROXYSOCKET->write(intData" + strNum + ", *(int*)intData" + strNum + ");\n");
	  				funcHeadStr.append(typeNameStr + " " + argNameStr + ",");
	  			}else if(typeNameStr == "float"){
	      			argumentConversions.append("\tchar *floatData" + strNum+ " = (char*)convertFloatToByte(" + argNameStr + ", \"" + argNameStr + "\", NULL);\n");
	      			argumentConversions.append("\tRPCPROXYSOCKET->write(floatData" + strNum + ", *(int*)floatData" + strNum + ");\n");
	      			funcHeadStr.append(typeNameStr + " " + argNameStr + ",");
	  			}else if(typeNameStr == "string"){
	      			argumentConversions.append("\tchar *stringData" + strNum + " = (char*)convertStringToByte(" + argNameStr + ", \"" + argNameStr + "\", NULL);\n");
	      			argumentConversions.append("\tRPCPROXYSOCKET->write(stringData" + strNum + ", *(int*)stringData" + strNum + ");\n");
	      			funcHeadStr.append(typeNameStr + " " + argNameStr + ",");
	  			}else{
	  				// handle struct and arrays here
	  				TypeDeclaration *typep = argp->getType();
	  				if(typep->isStruct()){
	  					argumentConversions.append("\tchar *sData" + strNum + " = (char*)convert" + typep->getName() + "ToByte(" + argNameStr + ",\"" + argNameStr + "\", NULL);\n");
	  					argumentConversions.append("\tRPCPROXYSOCKET->write(sData" + strNum + ", *(int*)sData" + strNum + ");\n");
	  					funcHeadStr.append(typeNameStr + " " + argNameStr + ",");
	  				}else if(typep->isArray()){
	  					string argStr = "";
	  					TypeDeclaration *arrayType = typep->getArrayMemberType();
	  					argStr.append("[" + intToString(typep->getArrayBound())+ "]");
	  					while(arrayType){
	  						if(arrayType->isArray()){
	  							argStr.append("[" + intToString(arrayType->getArrayBound())+ "]");
	  							arrayType = arrayType->getArrayMemberType();
	  						}else{
	  							typeNameStr = arrayType->getName();
	  							arrayType = NULL;
	  						}
	  					}
	  					
	  					argumentConversions.append("\t"+ typeNameStr +" arrayData" + strNum + " = (char*)convert" + arrayTypeNameHelper(typep) + "ToByte(" + argNameStr + ",\"" + argNameStr + "\", NULL);\n");
	  					argumentConversions.append("\tRPCPROXYSOCKET->write(arrayData" + strNum + ", *(int*)arrayData" + strNum + ");\n");	  				
	  					funcHeadStr.append(typeNameStr + " " + argNameStr + argStr + ",");
	  				}
	  			}
	  			argumentConversions.append("\n");
      		}
      		if (argsSize != 0){
      			funcHeadStr.erase(funcHeadStr.length() - 1);
      		}
      		funcHeadStr.append(")");
      	    
      		proxyCodeStr.append(funcHeadStr);
			proxyCodeStr.append("{\n");
			proxyCodeStr.append("\tchar readBuffer[5];\n");
			proxyCodeStr.append("\tc150debug->printf(C150RPCDEBUG,\"" + proxyFileNameStr + ": invoking\");\n");
            proxyCodeStr.append("\tint functionLength = strlen(\"" + funcNameStr + "\")+1;\n");
            proxyCodeStr.append("\tRPCPROXYSOCKET->write((char*)&functionLength, sizeof(int));\n");
			proxyCodeStr.append("\tRPCPROXYSOCKET->write(\""+ funcNameStr + "\", strlen(\"" + funcNameStr+ "\")+1);\n");
			// Now Writer the argument conversions -- And send them
			proxyCodeStr.append(argumentConversions);
			
			proxyCodeStr.append("\tc150debug->printf(C150RPCDEBUG,\"" + proxyFileNameStr + ": returned from\");\n");
			proxyCodeStr.append("\tRPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));\n");
			proxyCodeStr.append("\tif (strncmp(readBuffer,\"DONE\", sizeof(readBuffer))!=0) {\n");
			proxyCodeStr.append("\t\tthrow C150Exception(\"" + proxyFileNameStr+": " + funcNameStr +" received invalid response from the server\");\n");
      		proxyCodeStr.append("\t}\n");
      		
      		
      		proxyCodeStr.append("\tchar* retLenPtr = (char*) malloc(sizeof(int));\n");
      		proxyCodeStr.append("\treadNByte(retLenPtr, sizeof(int));\n");
      		proxyCodeStr.append("\tchar* arg0 = (char*) malloc(*(int *)retLenPtr);\n");
      		proxyCodeStr.append("\tmemcpy(arg0, retLenPtr, sizeof(int));\n");
      		proxyCodeStr.append("\tchar *data0 = arg0;\n");
      		proxyCodeStr.append("\targ0 += sizeof(int);\n");
      		proxyCodeStr.append("\treadNByte(arg0, (*(int*)retLenPtr) - sizeof(int));\n");
      		if(funcRetTypeStr == "int"){
      			proxyCodeStr.append("\tint retval = fromDataToInt(data0);\n");
      		}else if(funcRetTypeStr == "string"){
      			proxyCodeStr.append("\tstring retval = fromDataToString(data0);\n");
      		}else if(funcRetTypeStr == "float"){
      			proxyCodeStr.append("\tfloat retval = fromDataToFloat(data0);\n");
      		}else{
      			// Handle structs here
      			TypeDeclaration *typep = functionp->getReturnType();
      			if( typep->isStruct()){
      				proxyCodeStr.append("\t" + typep->getName() + " retval = *fromDataTo" + typep->getName() + "(data0);\n");	
      			}
      		}
      		proxyCodeStr.append("\tc150debug->printf(C150RPCDEBUG,\"" + proxyFileNameStr + ": "+ funcNameStr +" successful return from remote cal\");\n");
      		if(funcRetTypeStr != "void"){
      			proxyCodeStr.append("\treturn retval;\n");
      		}
      		proxyCodeStr.append("\n\n}\n\n");		
      		
      		//printf("4\n");		

      	}
      	
        conversionCode.insert(0, conversionFunctionHeaders);
	    string proxies("//INSERT_PROXIES_HERE");
		string header("//INSERT_IDL_HEADERS_HERE");
		string conversions("//INSERT_IDL_SPECIFIC_CONVERSIONS_HERE");
		
		int proxiesPos = proxyFileStr.find(proxies);
		proxyFileStr.replace(proxiesPos, proxies.length(), proxyCodeStr);
		int headerPos = proxyFileStr.find(header);
		proxyFileStr.replace(headerPos, header.length(),  includeStr);
		int conversionPos = proxyFileStr.find(conversions);
		proxyFileStr.replace(conversionPos, conversions.length(),  conversionCode);
	    
	    ofstream file;
	    file.open(proxyFileNameStr.c_str());
	    file << proxyFileStr;
	    file.close();
	}
}

