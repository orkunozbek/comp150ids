#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"


using namespace std;

int main(int argc, char *argv[]){
    int argnum;
    int iterCnt = 0; // Determines whether to form if or else if statement inside dispatch function 

    if (argc < 2) {
      fprintf(stderr, "Syntax: %s  idlfile1 [idlfile...]*\n", argv[0]);
      exit (8);
    };
    
    string includeStr;
    string stubCodeStr;
    string dispatchCondStr;
    
    string funcHeadStr;
    string funcCallStr;
    string funcCallRightStr;
    string funcCallRight2Str;
    
    string funcRetTypeStr;
    string funcNameStr;
    string typeNameStr;
    string argNameStr;
    
    string argStr;
    string dataStr;
    string xStr;
    
    string str;
    string stubFileStr;
    
    ifstream t("stub_template.cpp");

    t.seekg(0, ios::end);  
    str.reserve(t.tellg());
    t.seekg(0, ios::beg);

    str.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
    t.close();
    
    for (argnum = 1; argnum < argc; argnum++) {
      
      stubFileStr.clear();
      stubFileStr.append(str); 
      includeStr.clear();
      stubCodeStr.clear();
      
      string idlFileNameStr(argv[argnum]);
      string stubFileNameStr = idlFileNameStr.substr(0, idlFileNameStr.find(".idl"));
      stubFileNameStr.append(".stub.cpp");
      ifstream idlFile(idlFileNameStr.c_str());
      
      Declarations parseTree(idlFile);
      
      includeStr.append("#include \"");
      includeStr.append(argv[argnum]);
      includeStr.append("\"\n");
      
      map<string, FunctionDeclaration*>::iterator fiter;  
      FunctionDeclaration *functionp;    

      for (fiter = parseTree.functions.begin(); fiter != parseTree.functions.end(); ++fiter) {
	
	functionp = fiter -> second;
	funcHeadStr.clear();
	funcCallStr.clear();
	funcCallRightStr.clear();
	
	funcRetTypeStr = functionp->getReturnType()->getName();
	funcNameStr    = functionp->getName();
	
	funcHeadStr.append(funcRetTypeStr);
	funcHeadStr.append(" __");
	funcHeadStr.append(funcNameStr);
	funcHeadStr.append("(");
	
	if (funcRetTypeStr .compare("void") != 0){
	  funcCallStr.append(funcRetTypeStr);
	  funcCallStr.append(" retval = ");
	}
	
	funcCallStr.append(funcNameStr);
	funcCallStr.append("(");
	funcCallRightStr.append(funcNameStr);
	funcCallRightStr.append("(");
	
	
	if (iterCnt == 0){
	  dispatchCondStr.append("  if (strcmp(funcName,\"");
	  iterCnt = 1;
	}
	else{
	  dispatchCondStr.append("  else if (strcmp(funcName,\"");
	}
	dispatchCondStr.append(funcNameStr);
	dispatchCondStr.append("\") == 0){\n\t");
	
	ArgumentVector& args = functionp -> getArgumentVector();
	int argsSize = args.size();
	funcCallRight2Str.clear();
	funcCallRight2Str.append("__");
	funcCallRight2Str.append(funcCallRightStr);
	
	for(argnum=0; argnum < argsSize; argnum++) {
		string numberStr = static_cast<ostringstream*>( &(ostringstream() << argnum))->str();
		
		argStr.clear();
		argStr.append("arg");
		argStr.append(numberStr);
		
		dataStr.clear();
		dataStr.append("data");
		dataStr.append(numberStr);
		
		xStr.clear();
		xStr.append("x");
		xStr.append(numberStr);
	  
		Arg_or_Member_Declaration* argp = args[argnum];
		typeNameStr = argp->getType()->getName();
		argNameStr  = argp->getName();
		funcHeadStr.append(typeNameStr);
		funcHeadStr.append(" ");
		funcHeadStr.append(argNameStr);
		funcHeadStr.append(",");
		
		funcCallStr.append(argNameStr);
		funcCallStr.append(",");
		funcCallRightStr.append(argNameStr);
		funcCallRight2Str.append(xStr).append(",");
		
		dispatchCondStr.append("readNByte(argLenPtr, sizeof(int));\n\t");
		dispatchCondStr.append("char* ");
		dispatchCondStr.append(argStr);
		dispatchCondStr.append(" = (char*) malloc(*(int*)argLenPtr);\n\t");
		dispatchCondStr.append("memcpy(");
		dispatchCondStr.append(argStr);
		dispatchCondStr.append(" , argLenPtr, sizeof(int));\n\t");
		dispatchCondStr.append("char *").append(dataStr).append(" = ");
		dispatchCondStr.append(argStr).append(";\n\t");
		dispatchCondStr.append(argStr).append(" += sizeof(int);\n\t");
		dispatchCondStr.append("readNByte(").append(argStr).append(", (*(int*)argLenPtr) - sizeof(int));\n\t");
		
		if (typeNameStr.compare("int") == 0){
		  dispatchCondStr.append("int ").append(xStr).append("= fromDataToInt(").append(dataStr);
		  dispatchCondStr.append(");\n\t");
		}
		
		if (typeNameStr.compare("float") == 0){
		  dispatchCondStr.append("float ").append(xStr).append("= fromDataToFloat(").append(dataStr);
		  dispatchCondStr.append(");\n\t");
		}
		
		//if (typeNameStr.compare("byte") == 0){
		//  dispatchCondStr.append("byte ").append(xStr).append("= fromDataToByte(").append(dataStr);
		//  dispatchCondStr.append(");\n\t");
		//}
		
		if (typeNameStr.compare("string") == 0){
		  dispatchCondStr.append("string ").append(xStr).append("= fromDataToString(").append(dataStr);
		  dispatchCondStr.append(");\n\t");
		}
		
		
		
		
		
		//dispatchCondStr.append("readNByte(");
		//dispatchCondStr.append(argStr);
		//ispatchCondStr.append(", argLen);\n\t");
		
		//Change Byte order of data if client and server endianness are not compatible
		////dispatchCondStr.append("if (reverseBytes)\n\t");
		////dispatchCondStr.append("reverseData(arg");//
		////dispatchCondStr.append(numberStr);	  //
		////dispatchCondStr.append(", argLen);\n\t"); //
		
		/*
		if (typeNameStr == "int"){
		  dispatchCondStr.append("int x");
		  dispatchCondStr.append(numberStr);
		  dispatchCondStr.append(" = fromDataToInt(arg");
		  dispatchCondStr.append(numberStr);
		  dispatchCondStr.append(");\n\t\n\t");		  
		  
		}
		
		else if (typeNameStr == "float"){
		  dispatchCondStr.append("float x");
		  dispatchCondStr.append(numberStr);
		  dispatchCondStr.append(" = fromDataToFloat(arg");
		  dispatchCondStr.append(numberStr);
		  dispatchCondStr.append(");\n\t\n\t");
		}
		
		else if (typeNameStr == "string"){
		  dispatchCondStr.append("string x");
		  dispatchCondStr.append(numberStr);
		  dispatchCondStr.append(" = fromDataToString(arg");
		  dispatchCondStr.append(numberStr);
		  dispatchCondStr.append(");\n\t\n\t");
		}
		
		else{}
		*/
		
	}
	
	
	
	if (argsSize != 0){
	  funcHeadStr.erase(funcHeadStr.length() - 1);
	  funcCallStr.erase(funcCallStr.length() - 1);
	  funcCallRightStr.erase(funcCallRightStr.length() - 1);
	  funcCallRight2Str.erase(funcCallRight2Str.length() - 1);
	}
	
	funcHeadStr.append(")");
	funcCallStr.append(")");
	funcCallRightStr.append(")");
	dispatchCondStr.append(funcCallRight2Str).append(");\n");
	dispatchCondStr.append("  }\n");
	
	stubCodeStr.append(funcHeadStr);
	stubCodeStr.append("{\n\t");
	stubCodeStr.append("char doneBuffer[5] = \"DONE\";\n\t");
	stubCodeStr.append("c150debug->printf(C150RPCDEBUG,\"simplefunction.stub.cpp: invoking");
	stubCodeStr.append(funcCallRightStr);
	stubCodeStr.append("\");\n\t");
	stubCodeStr.append(funcCallStr + ";\n\t");
	stubCodeStr.append("c150debug->printf(C150RPCDEBUG,\"simplefunction.stub.cpp: returned from");
	stubCodeStr.append(funcCallRightStr);
	stubCodeStr.append("\");\n\t");
	
	stubCodeStr.append("void* bytes = ");
	
	if (functionp->getReturnType()->getName().compare("int") == 0){
	  stubCodeStr.append("convertIntToByte(retval, \"retval\", NULL);\n\t");
	}
	else if (functionp->getReturnType()->getName().compare("float") == 0){
	  stubCodeStr.append("convertFloatToByte(retval, \"retval\", NULL);\n\t");
	}
	else if (functionp->getReturnType()->getName().compare("string") == 0){
	  stubCodeStr.append("convertStringToByte(retval, \"retval\", NULL);\n\t");
	}
	else if (functionp->getReturnType()->getName().compare("void") == 0){
	  stubCodeStr.append("convertVoidToByte();\n\t");
	}
	else{
	  //TO BE DONE
	}
	
	
	stubCodeStr.append("RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);\n\t");
	stubCodeStr.append("RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);\n\t");
	
	if (funcRetTypeStr.compare("void") != 0){
	  stubCodeStr.append("return retval;\n");
	}
	stubCodeStr.append("\n}\n\n");	
    }
    
    //Inserting Code to stub file
    string stubs("//INSERT_STUBS_HERE");
    string code("//INSERT_DISPATCH_CODE");
    string header("//INSERT_IDL_HEADERS_HERE");

    int stubsPos = stubFileStr.find(stubs);
    stubFileStr.replace(stubsPos, 0, stubCodeStr);
    int codePos  = stubFileStr.find(code);
    stubFileStr.replace(codePos, 0, dispatchCondStr);
    int headerPos = stubFileStr.find(header);
    stubFileStr.replace(headerPos, 0,  includeStr);
    
    //Erasing Placeholder Comment Lines for Rpcgenerator.cpp
    
    stubsPos = stubFileStr.find(stubs);
    stubFileStr.replace(stubsPos, stubs.size(),"");
    codePos  = stubFileStr.find(code);
    stubFileStr.replace(codePos,  code.size(),"");
    headerPos = stubFileStr.find(header);
    stubFileStr.replace(headerPos, header.size(),"");
    
    
    // Writing to stub
    ofstream file;
    file.open(stubFileNameStr.c_str());
    file << stubFileStr;
    file.close();
 } 
   return 0;
}

