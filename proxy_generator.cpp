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
    
    
    // Read the contents of proxy template
    ifstream t("proxy_template.cpp");

 	t.seekg(0, ios::end);  
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

 	str.assign((istreambuf_iterator<char>(t)),
    istreambuf_iterator<char>());
	t.close();
	
	printf("1\n");
	
	
	for (argnum = 1; argnum < argc; argnum++) {
		proxyFileStr.clear();
		proxyFileStr.append(str);
		includeStr.clear();
		proxyCodeStr.clear();
		
      	
      	string idlFileNameStr(argv[argnum]);
      	string proxyFileNameStr = idlFileNameStr.substr(0, idlFileNameStr.find(".idl"));
      	proxyFileNameStr.append(".proxy.cpp");
      	ifstream idlFile(idlFileNameStr.c_str());
      	
      	Declarations parseTree(idlFile);
      	includeStr.append("#include \"");
      	includeStr.append(argv[argnum]);
      	includeStr.append("\"\n");
      	
      	
      	printf("2\n");
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
      			funcHeadStr.append(typeNameStr + " " + argNameStr + ", ");
      			// Holds the value of argNum
				char strBuffer[33];
				snprintf(strBuffer, sizeof(strBuffer), "%d", (int)argnum);
				string strNum(strBuffer);
	  			if(typeNameStr == "int"){
	  				argumentConversions.append("\tchar *intData" + strNum + " = (char*)convertIntToByte(" + argNameStr + ",\"" + argNameStr + "\");\n");
	  				argumentConversions.append("\tRPCPROXYSOCKET->write(intData" + strNum + ", *intData" + strNum + ");\n");
	  			}else if(typeNameStr == "float"){
	      			argumentConversions.append("\tchar *floatData" + strNum+ " = (char*)convertFloatToByte(" + argNameStr + ", \"" + argNameStr + "\");\n");
	      			argumentConversions.append("\tRPCPROXYSOCKET->write(floatData" + strNum + ", *floatData" + strNum + ");\n");
	  			}else if(typeNameStr == "string"){
	      			argumentConversions.append("\tchar *stringData" + strNum + " = (char*)convertStringToByte(" + argNameStr + ", \"" + argNameStr + "\");\n");
	      			argumentConversions.append("\tRPCPROXYSOCKET->write(stringData" + strNum + ", *stringData" + strNum + ");\n");
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
            proxyCodeStr.append("\tint functionLength = strlen(\"" + funcNameStr + "\")+1;");
            proxyCodeStr.append("\tRPCPROXYSOCKET->write(&functionLength, sizeof(int));");
			proxyCodeStr.append("\tRPCPROXYSOCKET->write(\""+ funcNameStr + "\", strlen(\"" + funcNameStr+ "\")+1);\n");
			// Now Writer the argument conversions -- And send them
			proxyCodeStr.append(argumentConversions);
			
			proxyCodeStr.append("\tc150debug->printf(C150RPCDEBUG,\"" + proxyFileNameStr + ": returned from\");\n");
			proxyCodeStr.append("\tRPCPROXYSOCKET->read(readBuffer, sizeof(readBuffer));\n");
			proxyCodeStr.append("\tif (strncmp(readBuffer,\"DONE\", sizeof(readBuffer))!=0) {\n");
			proxyCodeStr.append("\t\tthrow C150Exception(\"" + proxyFileNameStr+": " + funcNameStr +" received invalid response from the server\");\n");
      		proxyCodeStr.append("\t}\n");
      		proxyCodeStr.append("\tc150debug->printf(C150RPCDEBUG,\"" + proxyFileNameStr + ": "+ funcNameStr +" successful return from remote cal\");\n");
      		proxyCodeStr.append("\n\n}\n\n");		
      		
      		printf("4\n");		

      	}
	    string proxies("//INSERT_PROXIES_HERE");
		string header("//INSERT_IDL_HEADERS_HERE");
		
		int proxiesPos = proxyFileStr.find(proxies);
		proxyFileStr.replace(proxiesPos, 0, proxyCodeStr);
		int headerPos = proxyFileStr.find(header);
		proxyFileStr.replace(headerPos, 0,  includeStr);
	    
	    ofstream file;
	    file.open(proxyFileNameStr.c_str());
	    file << proxyFileStr;
	    file.close();
	}
}

