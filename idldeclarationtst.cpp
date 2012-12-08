// --------------------------------------------------------------
//
//                        idldeclarationtst.cpp
//
//        Author: Noah Mendelsohn
//
//        Syntax:
//
//               idldeclarationtst idlfile1 [idlfile...]*
//  
//        This program reads each file named on the command line
//        and parses the file into a Declarations parse tree.
//        The results are then formatted on standard output for demonstration
//        purposes.
//
//        INTENDED USE:
//
//        In addition to being somewhat useful for exploring IDL files, this
//        code is intended to illustrate use of the data structures comprising
//        the parse tree.
//
//        NEEDSWORK:
//
//        This test program and the parsing framework were written in some haste.
//        There will likely be some problems especially with edge cases.
//
//        It's known that the parsing framework does not free dynamically
//        allocated structures -- valgrind will report leaks.
//
//       Copyright: 2012 Noah Mendelsohn
//     
// --------------------------------------------------------------



#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"
#include <string>
#include <streambuf>
#include <vector>
#include <sstream>

using namespace std;

string intToString ( int Number )
 {
    ostringstream ss;
    ss << Number;
    return ss.str();
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
      }
    }
    found = str.find(size, found);
    str.replace(found, size.length(), appendedStr);
    
    
    string conversions = "${APPEND_MEMBER_CONVERSIONS}";
	appendedStr.clear();

    for(size_t memberNum=0; memberNum<members.size();memberNum++) {
      Arg_or_Member_Declaration* memp = members[memberNum];
      //ss << endl << "   " << memp->getType()->getName() << "  " << memp->getName();
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
    }
    found = str.find(size, found);
    str.replace(found, size.length(), appendedStr);
	
	return str;
}


string createArraySizeFunction(string str, TypeDeclaration *typep){
    string typeNameStr = typep->getName();
    replace(typeNameStr.begin(),typeNameStr.end(), '[', '_');
	replace(typeNameStr.begin(),typeNameStr.end(), ']', '_');
    cout << "TYPEEEE NAME STRR" << typeNameStr <<  endl;
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
    
    return str;
}


string createArrayConversionFunction(string str, TypeDeclaration *typep){
    string typeNameStr = typep->getName();
    replace(typeNameStr.begin(),typeNameStr.end(), '[', '_');
	replace(typeNameStr.begin(),typeNameStr.end(), ']', '_');
    cout << "TYPEEEE NAME STRR" << typeNameStr <<  endl;
    // Replace the type name
    string typeNameStrTag = "${ARRAY_TYPE_S}";
    size_t found = str.find(typeNameStrTag);
    if(found!=string::npos){
        str.replace(found, typeNameStrTag.length(), typeNameStr);
    }
    
    
    // Append the dim data representation length
    // Keep a vector of array dimensions
    string dimsToBytes = "";
    string dataFieldSizeStr = "";
    string dimsStr = "";
    string argStr = "";
    TypeDeclaration *arrayType = typep->getArrayMemberType();
    int i = 0;
    dataFieldSizeStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(typep->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
    dimsStr.append("[i" + intToString(i) + "]");
    argStr.append("[" + intToString(typep->getArrayBound())+ "]");
    dimsToBytes.append("\tint bound = " + intToString(typep->getArrayBound()) + ";\n");
    dimsToBytes.append("\tmemcpy(tmp, &bound, sizeof(int));\n");
    dimsToBytes.append("\ttmp+=sizeof(int);\n");
    while(arrayType){
        i++;
        if(arrayType->isArray()){
        	argStr.append("[" + intToString(arrayType->getArrayBound())+ "]");
		    dataFieldSizeStr.append("\tfor(int i" + intToString(i) + "= 0; i" + intToString(i) + "< " + intToString(arrayType->getArrayBound()) +  "; i" + intToString(i) + "++)\n");
		    dimsStr.append("[i" + intToString(i) + "]");
		    dimsToBytes.append("\tbound = " + intToString(typep->getArrayBound()) + ";\n");
            dimsToBytes.append("\tmemcpy(tmp, &bound, sizeof(int));\n");
            dimsToBytes.append("\ttmp+=sizeof(int);\n");
			arrayType = arrayType->getArrayMemberType();
		}
		else{
		    dimsToBytes.insert(0,"\tint numDims = " + i + ";\n");
            dimsToBytes.append("\tmemcpy(tmp, &numDims, sizeof(int));\n");
            dimsToBytes.append("\ttmp+=sizeof(int);\n");
            string typeName =arrayType->getName();
            
		    if (typeName == "int"){
          		dataFieldSizeStr.append("\tconvertIntToByte(arr" + dimsStr + ", \"\", tmp);\n");
          		dataFieldSizeStr.append("\ttmp+=*tmp;\n")
          		argStr.insert(0, "int arr");
                dimsToBytes.append("\t*tmp++ = 1;\n");
          	}
          	else if(typeName == "float"){
              	dataFieldSizeStr.append("\tconvertFloatToByte(arr" + dimsStr + ", \"\", tmp);\n");
          		dataFieldSizeStr.append("\ttmp+=*tmp;\n")
              	argStr.insert(0, "float arr");
              	dimsToBytes.append("\t*tmp++ = 2;\n");
            }	
            else if(typeName == "string"){
            	dataFieldSizeStr.append("\tconvertStringToByte(arr" + dimsStr + ", \"\", tmp);\n");
            	dataFieldSizeStr.append("\ttmp+=*tmp;\n")
            	argStr.insert(0, "string arr");
            	dimsToBytes.append("\t*tmp++ = 4;\n");
            }
			else{
                dataFieldSizeStr.append("\tconvert"+ typeName +"ToByte(arr" + dimsStr + ",\"\", tmp);\n");
                dataFieldSizeStr.append("\ttmp+=*tmp;\n")
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
    
    
    
    string typeTag = "${ARRAY_TYPE}";
    found = str.find(typeTag);
    if(found != string::npos){
        str.replace(found, typeTag.length(), argStr);
    }    
    
    return str;    
}


void
processIDLFile(const char fileName[]);


// --------------------------------------------------------------
//
//                       main
//
//          Loop through all files calling processIDLFile on each
//
// --------------------------------------------------------------

int 
main(int argc, char *argv[])
{
    int argnum;

    //
    // Check argument count
    //
    if (argc < 2) {
      fprintf(stderr, "Syntax: %s  idlfile1 [idlfile...]*\n", argv[0]);
      exit (8);
    };

    //
    //  Loop through arguments, processing each named file
    //

    for (argnum = 1; argnum < argc; argnum ++) {

      try {
	processIDLFile(argv[argnum]);
      } 

      catch (C150Exception e) {
	//
	// If any of the exceptions that are created using the COMP 150
	// framework are thrown, they come with a detailed explanation.
	// Print it, then give up.
	//
	fprintf(stderr,"%s: caught C150Exception: %s\n", argv[0],  
		e.formattedExplanation().c_str());
	printf("...Giving up on file %s...",argv[argnum]);
	if (argnum< (argc-1)) 
	  printf("trying next file...\n\n-----------------------------------------\n\n");
      }
    }
    
    printf("\n\n");   // some diagnostic output may not have ended with linefeed

    return 0;
}

// -----------------------------------------------------
//                  processIDLFile
//
//  Use the IDLTokenizer class to tokenize one file.
//  Then format the results on stdout for diagnostic
//  purposes.
//
//  THIS IS WHERE YOU SHOULD LOOK TO LEARN THE PARSE
//  TREE DATA STRUCTURES, BECAUSE THE PRINTOUT ROUTINES
//  BELOW SHOW YOU HOW TO WALK THROUGH THE WHOLE PARSE
//  TREE. ALSO CHECK .H FILES LIKE functiondeclaration.h.
//
// -----------------------------------------------------

void
processIDLFile(const char fileName[]) {

  unsigned int argnum;
  ifstream t("structsizefunction");
  string str;
  t.seekg(0, ios::end);   
  str.reserve(t.tellg());
  t.seekg(0, ios::beg);
  str.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
  printf("%s\n", str.c_str());
  
  t.close();
  t.open("structconvertfunction");
  string convertFunctionStr;
  t.seekg(0, ios::end);   
  convertFunctionStr.reserve(t.tellg());
  t.seekg(0, ios::beg);
  convertFunctionStr.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
  printf("%s\n", convertFunctionStr.c_str());
  t.close();
  
  
  t.open("arraysizefunction");
  string arraySizeFunction;
  t.seekg(0, ios::end);   
  arraySizeFunction.reserve(t.tellg());
  t.seekg(0, ios::beg);
  arraySizeFunction.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
  printf("%s\n", arraySizeFunction.c_str());
  t.close();
  
  t.open("arrayconversionfunction");
  string arrayConversionFunction;
  t.seekg(0, ios::end);   
  arrayConversionFunction.reserve(t.tellg());
  t.seekg(0, ios::beg);
  arrayConversionFunction.assign((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());
  printf("%s\n", arrayConversionFunction.c_str());
  t.close();

  //
  // Open the file
  //
  ifstream idlFile(fileName);        // open 

  if (!idlFile.is_open()) {
    stringstream ss;
    ss << "Could not open IDL file: " << fileName;
    throw C150Exception(ss.str());
  }

  //
  //   Call the IDL parser to parse the file
  //   into typed tokens
  //

  printf("\n\n********************************************************\n");
  printf(    "              File: %-25s            \n",fileName);
  printf(    "********************************************************\n");


  printf("\nParsing Declarations(%s)\n", fileName);

  // The following line does all the work parsing the file into
  // the variable parseTree

  Declarations parseTree(idlFile);
  printf("Done Parsing Declarations\n");

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  //         Print out all Types
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

  printf("\n*------------------------------------------------------*\n");
  printf(    "|                    TYPES                             |\n");
  printf(    "*------------------------------------------------------*\n");
  printf("\n\nNumber of types=%d\n", (int)parseTree.types.size());
  
  //
  //  Loop once for each type declaration
  //
  //
  // The C++ iterator stuff over maps is a mess. 
  // The following shows you how to go through every type
  // regardless of name.
  //
  //  You could also reference a particular type with
  //
  //      parseTree.types["yourtypename"]
  //
  //  First, you should see whether the type exists by calling: 
  //
  //      parseTree.typeExists["yourtypename"]
  //

  // This iterator will return pairs of <string, TypeDeclaration*>
  // If this doesn't make sense, look on the Web for information
  // about iterating over C++ maps. 

  std::map<std::string, TypeDeclaration*>::iterator iter;  

  TypeDeclaration *typep;

  stringstream formattedType;

  for (iter = parseTree.types.begin(); iter != parseTree.types.end(); ++iter) {

    //
    // Iter actually is a pair, with members first (the key) and
    // second (the value) from the map. Our keys are the type
    // names, and the values are the actual type declaration structures.
    //
    // iter -> second gets you the value, so that's what we want
    //
    // We can actually get the type name from two places:
    // From the map at iter -> first, or from the TypeDeclaration
    // itself by doing typep->getName()  
    // 
    typep = iter -> second;

    // OK -- HERE IS WHERE YOU HAVE THE TYPE NAME

    formattedType.str("");      // empty the formatting buffer
    
    if(typep->isStruct()){
    	printf("This is struct!!!\n");
    	string structFieldFunction = str;
    	cout << createStructSizeFunction(structFieldFunction, typep) << endl;
    	string structConversionFunction = convertFunctionStr;
    	cout << createStructConversionFunction(structConversionFunction, typep) << endl;
    }else if(typep->isArray()){
        string arraySizeFunctionTmpStr = arraySizeFunction;
        cout << createArraySizeFunction(arraySizeFunctionTmpStr, typep) << endl;
        string arrayConversionFunctionTmpStr = arrayConversionFunction;
        cout << createArrayConversionFunction(arrayConversionFunctionTmpStr, typep) << endl;
	    // int i = 0;
	    //         //cout <<  typep-> getArrayBound() << " " << typep->getName() << " " ;
	    //         cout << "for(int i" << i << "= 0; i" << i << "< " << typep->getArrayBound() <<  "; i" << i << "++)\n";
	    //         //string str = "for(int i" + i + "= 0; i" + i + "< " + typep->getArrayBound()+ "; i" + i+ "++)\n";
	    //         TypeDeclaration *arrayType = typep->getArrayMemberType();
	    //         
	    //         while(arrayType){
	    //             i++;
	    //             
	    //             if(arrayType->isArray()){
	    //                 //cout <<  arrayType-> getArrayBound() << " " << arrayType->getName() <<  " " ;
	    //                 cout << "for(int i" << i << "= 0; i" << i << "< " << arrayType->getArrayBound() <<  "; i" << i << "++)\n";  
	    //                 arrayType = arrayType->getArrayMemberType();
	    //             }
	    //             else{
	    //                 cout << "convertTo" <<arrayType->getName() << "(),tmp+=*tmp";
	    //                 arrayType = NULL;
	    //             }
	    //         }
	    //         cout << endl;
    }

    typep->to_string_stream(formattedType);   // format the type info into the buffer

    printf("\n%s",formattedType.str().c_str());  // write the output
  } 

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  //         Print out all Functions
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


  printf("\n\n*------------------------------------------------------*\n");
  printf(    "|                   FUNCTIONS                          |\n");
  printf(    "*------------------------------------------------------*\n");
  printf("\n\nNumber of functions=%d\n", (int)parseTree.functions.size());
  
  //
  //  Loop once for each function declaration
  //
  //  You could also reference a particular function with
  //
  //      parseTree.functions["yourfunctionname"]
  //
  //  First, you should see whether the type exists by calling: 
  //
  //      parseTree.functionExists["yourfunctionname"]
  //



  // This iterator will return pairs of <string, FunctionDeclaration*>
  std::map<std::string, FunctionDeclaration*>::iterator fiter;  

  FunctionDeclaration *functionp;    // Declare FunctionDelcaration pointer

  //  ArgumentVector args;               // We'll hold a copy of the parameter
                                     // list here

  for (fiter = parseTree.functions.begin(); fiter != parseTree.functions.end(); ++fiter) {

    //
    // Fiter actually is a pair, with members first (the key) and
    // second (the value) from the map. Our keys are the function
    // names, and the values are the actual function declaration structures.
    // 
    functionp = fiter -> second;

    printf("\nFunction name: %s\n", functionp->getName().c_str());


    //
    // Get a C++ reference to the vector with the argument list
    //
    ArgumentVector& args = functionp -> getArgumentVector();

    printf("  Return type: %s\n\n",functionp->getReturnType()->getName().c_str());
    printf("  Number of arguments: %d\n\n",(int)args.size());

    //
    // The arguments are in a vector, not a map, so we
    // access them by position, not name
    //
    for(argnum=0; argnum<args.size();argnum++) {
      Arg_or_Member_Declaration* argp = args[argnum];
      printf("  ARGUMENT: name=%s type=%s\n",
	     argp->getName().c_str(),
	     argp->getType()->getName().c_str());
    }

    printf("\n\n");                    // separate functions w/ space

  } 




}
