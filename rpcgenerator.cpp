#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"


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
    string preFuncDefStr;
    
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
    string conversionCode;
    string conversionFunctionHeaders;
    //string capitalTypeStr;
    
    string str;
    string stubFileStr;
    
    ifstream t("stub_template.cpp");

    t.seekg(0, ios::end);  
    str.reserve(t.tellg());
    t.seekg(0, ios::beg);

    str.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
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
    
    
    for (argnum = 1; argnum < argc; argnum++) {
      
      stubFileStr.clear();
      stubFileStr.append(str); 
      includeStr.clear();
      stubCodeStr.clear();
      conversionCode.clear();
      conversionFunctionHeaders.clear();
      //functionHeaderIncludeStr.clear();
      
      string idlFileNameStr(argv[argnum]);
      string stubFileNameStr = idlFileNameStr.substr(0, idlFileNameStr.find(".idl"));
      stubFileNameStr.append(".stub.cpp");
      ifstream idlFile(idlFileNameStr.c_str());
      
      Declarations parseTree(idlFile);
      
      includeStr.append("#include \"");
      includeStr.append(argv[argnum]);
      includeStr.append("\"\n");
      
      std::map<std::string, TypeDeclaration*>::iterator iter;

      TypeDeclaration *typep;
      stringstream formattedType;
      for (iter = parseTree.types.begin(); iter != parseTree.types.end(); ++iter) {
          typep = iter -> second;
          formattedType.str(""); // empty the formatting buffer
          if(typep->isStruct()){
              conversionFunctionHeaders.append("size_t get" + typep->getName() +"FieldSize(" + typep->getName() + " s, string fieldName);\n");
		      conversionFunctionHeaders.append(typep->getName() +"* fromDataTo" + typep->getName() + "(char *data);\n");
		      conversionFunctionHeaders.append("void* convert" + typep->getName() + "ToByte(" + typep->getName() + " s, string fieldName,char *data);\n");
              string structFieldSizeFunction = structSizeStr;
              preFuncDefStr.append(createStructSizeFunction(structFieldSizeFunction, typep));
              preFuncDefStr.append("\n\n\n");
              string structConversionFunction = structConversionStr;
              preFuncDefStr.append(createStructConversionFunction(structConversionFunction, typep));
              preFuncDefStr.append("\n\n\n");
          }
      } 
      
      
      ////
      map<string, FunctionDeclaration*>::iterator fiter;  
      FunctionDeclaration *functionp;
      
      /*std::map<std::string, TypeDeclaration*>::iterator iter;  
      TypeDeclaration *typep;
      
      for (iter = parseTree.types.begin(); iter != parseTree.types.end(); ++iter) { 
	typep = iter -> second;
	if (typep->isStruct()) {
	   String structName = typep->getName();
	   preFuncDecStr.append(structName). append(" ").append("*fromDataTo");
	   preFuncDecStr.append(structName).append("(char* data);\n\t");
	   
	   preFuncDecStr.append("void *convert"). append(structName).append("ToByte");
	   preFuncDecStr.append("(string str, string fieldName, char *data=NULL);\n\t");
	}
      }*/

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

		if (typeNameStr.compare("string") == 0){
		  dispatchCondStr.append("string ").append(xStr).append("= fromDataToString(").append(dataStr);
		  dispatchCondStr.append(");\n\t");
		}

		if (argp->getType()->isStruct()){
		  dispatchCondStr.append(typeNameStr).append(" ").append(xStr).append("= *fromDataTo").append(typeNameStr);
		  dispatchCondStr.append("(").append(dataStr).append(");\n\t");
		}

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
	else if (functionp->getReturnType()->isStruct()){
	  stubCodeStr.append("convert").append(funcRetTypeStr).append("ToByte(retval, \"retval\", NULL);\n\t");
	}


	stubCodeStr.append("RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);\n\t");
	stubCodeStr.append("RPCSTUBSOCKET->write((char*)bytes,*(int*)bytes);\n\t");

	if (funcRetTypeStr.compare("void") != 0){
	  stubCodeStr.append("return retval;\n");
	}
	stubCodeStr.append("\n}\n\n");	
    }
    
    //Inserting Code to stub file
    conversionCode.insert(0, conversionFunctionHeaders);
    string stubs("//INSERT_STUBS_HERE");
    string code("//INSERT_DISPATCH_CODE");
    string header("//INSERT_IDL_HEADERS_HERE");
    string conversions("//INSERT_IDL_SPECIFIC_CONVERSIONS_HERE");

    int stubsPos = stubFileStr.find(stubs);
    stubFileStr.replace(stubsPos, stubs.length(), stubCodeStr);
    int codePos  = stubFileStr.find(code);
    stubFileStr.replace(codePos, code.length(), dispatchCondStr);
    int headerPos = stubFileStr.find(header);
    stubFileStr.replace(headerPos, header.length(),  includeStr);
    int conversionsPos = stubFileStr.find(conversions);
    stubFileStr.replace(conversionsPos, conversions.length(), conversionCode);
    
    //Erasing Placeholder Comment Lines for Rpcgenerator.cpp
    // stubsPos = stubFileStr.find(stubs);
    // stubFileStr.replace(stubsPos, stubs.size(),"");
    // codePos  = stubFileStr.find(code);
    // stubFileStr.replace(codePos,  code.size(),"");
    // headerPos = stubFileStr.find(header);
    // stubFileStr.replace(headerPos, header.size(),"");
    // preFuncPos = stubFileStr.find(prefunction);
    // stubFileStr.replace(preFuncPos, prefunction.size(),"");
    
    
    // Writing to stub
    ofstream file;
    file.open(stubFileNameStr.c_str());
    file << stubFileStr;
    file.close();
 } 
   return 0;
}

