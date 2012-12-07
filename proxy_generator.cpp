#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;


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
              appendedStr.append("\ttmp+=*tmp;\n")
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
                appendedStr.append("\ts->" + memberName + "= fromDataTo" + typep->getName() + "(tmp);\n");
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
              cout << "entered struct field size" << endl;
              appendedStr.append("\tlen+=get"+ typep->getName() +"FieldSize(s." + memp->getName() + ",\"" + memp->getName() + "\");\n");
          }
      }
    }
    found = str.find(size, found);
    str.replace(found, size.length(), appendedStr);
	
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
	
	//printf("1\n");
	
	
	for (argnum = 1; argnum < argc; argnum++) {
		proxyFileStr.clear();
		proxyFileStr.append(str);
		includeStr.clear();
		proxyCodeStr.clear();
		conversionCode.clear();
		
      	
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
		    	string structFieldSizeFunction = structSizeStr;
		    	conversionCode.append(createStructSizeFunction(structFieldSizeFunction, typep));
		    	conversionCode.append("\n\n\n");
		    	string structConversionFunction = structConversionStr;
		    	conversionCode.append(createStructConversionFunction(structConversionFunction, typep));
		    	conversionCode.append("\n\n\n");
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
      			funcHeadStr.append(typeNameStr + " " + argNameStr + ",");
      			// Holds the value of argNum
				char strBuffer[33];
				snprintf(strBuffer, sizeof(strBuffer), "%d", (int)argnum);
				string strNum(strBuffer);
	  			if(typeNameStr == "int"){
	  				argumentConversions.append("\tchar *intData" + strNum + " = (char*)convertIntToByte(" + argNameStr + ",\"" + argNameStr + "\", NULL);\n");
	  				argumentConversions.append("\tRPCPROXYSOCKET->write(intData" + strNum + ", *(int*)intData" + strNum + ");\n");
	  			}else if(typeNameStr == "float"){
	      			argumentConversions.append("\tchar *floatData" + strNum+ " = (char*)convertFloatToByte(" + argNameStr + ", \"" + argNameStr + "\", NULL);\n");
	      			argumentConversions.append("\tRPCPROXYSOCKET->write(floatData" + strNum + ", *(int*)floatData" + strNum + ");\n");
	  			}else if(typeNameStr == "string"){
	      			argumentConversions.append("\tchar *stringData" + strNum + " = (char*)convertStringToByte(" + argNameStr + ", \"" + argNameStr + "\", NULL);\n");
	      			argumentConversions.append("\tRPCPROXYSOCKET->write(stringData" + strNum + ", *(int*)stringData" + strNum + ");\n");
	  			}else{
	  				// handle struct and arrays here
	  				TypeDeclaration *typep = argp->getType();
	  				if(typep->isStruct()){
	  					argumentConversions.append("\tchar *sData" + strNum + " = (char*)convert" + typep->getName() + "ToByte(" + argNameStr + ",\"" + argNameStr + "\", NULL);\n");
	  					argumentConversions.append("\tRPCPROXYSOCKET->write(sData" + strNum + ", *(int*)sData" + strNum + ");\n");
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

