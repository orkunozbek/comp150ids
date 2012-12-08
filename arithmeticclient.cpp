
// arithmetic.idl  Tester

#include "arithmetic.idl"

#include "rpcproxyhelper.h"

#include "c150debug.h"
#include "c150grading.h"
#include <fstream>

using namespace std;          // for C++ std library
using namespace C150NETWORK;  // for all the comp150 utilities 

// forward declarations
void setUpDebugLogging(const char *logname, int argc, char *argv[]);


const int serverArg = 1;     // server name is 1st arg 
int 
main(int argc, char *argv[]) {

     setUpDebugLogging("simplefunctionclientdebug.txt",argc, argv);

     if (argc != 2) {
       fprintf(stderr,"Correct syntxt is: %s <servername> \n", argv[0]);
       exit(1);
     }

     
     GRADEME(argc, argv);

     try {
       int result; 


       rpcproxyinitialize(argv[serverArg]);

       // 
       // Call (possibly remote) add
       //
       printf("Calling add(10,2)\n");
       result = add(10,2);                          // remote call (we hope!)
       printf("Returned from add(10,2). Result=%d\n",result);

       // 
       // Call (possibly remote) subtract
       //
       printf("Calling subtract(10,2)\n");
       result = subtract(10,2);                          // remote call (we hope!)
       printf("Returned from subtract(10,2). Result=%d\n",result);

       // 
       // Call (possibly remote) multiply
       //
       printf("Calling multiply(10,2)\n");
       result = multiply(10,2);                          // remote call (we hope!)
       printf("Returned from multiply(10,2). Result=%d\n",result);

       // 
       // Call (possibly remote) divide
       //
       printf("Calling divide(10,2)\n");
       result = divide(10,2);                          // remote call (we hope!)
       printf("Returned from divide(10,2). Result=%d\n",result);

       printf("Calling getStudent(5)\n");
       Student s = getStudent(5);
       printf("Returned from getStudent(5). Result=%d\n", s.id);
	
       printf("Calling getStudent(10)\n");
       Student t = getStudent(10);
       printf("Returned from getStudent(5). Result=%d\n", t.id);

       printf("Calling studentAdd(s,t)\n");
       result = studentAdd(s,t);
       printf("Returned from studetnAdd(s,t). Result=%d\n", result);
       
       Vertex k1;
       k1.x = 5;
       k1.y = 10;
       
       Vertex k2;
       k2.x = 50;
       k2.y = 100;
       
       
       
       
       printf("Calling vertexADDXPos(k1,k2)\n");
       result = vertexAddXPos(k1,k2); // remote call (we hope!)
       printf("Returned from vertexADDXPos(k1,k2). Result=%d\n",result);
       
       printf("Calling vertexADDYPos(k1,k2)\n");
       result = vertexAddYPos(k2,k1); // remote call (we hope!)
       printf("Returned from vertexADDYPos(k1,k1). Result=%d\n",result);
       
       printf("Calling createVertex(6,36)\n");
       Vertex v = createVertex(6,36);
       printf("Returning createVertex(6,36) v1.x = %d v1.y = %d\n",v.x, v.y);
       
       printf("Calling createRectange(k1,k2)\n");
       Rectangle a = createRectangle(k1,k2);
       printf("Returning createRectange(k1,k2) corner1.x = %d corner1.y = %d \tcorner2.x = %d corner2.y = %d\n",a.corner1.x, a.corner1.y, a.corner2.x, a.corner2.y);
    
       printf("Calling createRectange(v,r)\n");
       Rectangle r = createRectangle(k2,k1);
       printf("Returning createRectange(k1,k2) corner1.x = %d corner1.y = %d \tcorner2.x = %d corner2.y = %d\n",r.corner1.x, r.corner1.y, r.corner2.x, r.corner2.y);

       printf("Calling rectangleAdd(a,r)\n");
       int d =rectangleAdd(a,r);
       printf("Returning rectangleAdd(a,r). Result: %d\n", d);

       
       
       printf("Calling rectangleCornerDistance(v,r)\n");
       float abc = rectangleCornerDistance(r);
       printf("Returned from rectangleCornerDistance(v,r). Result=%f\n",abc);
       
       float x[15], y[15];
       for(int i = 0; i <15; i++){
       		x[i] = i;
       		y[i] = 15+i;
       }
       printf("Calling addArray(x,y)\n");
       float fResult = addArray(x,y);                          // remote call (we hope!)
       printf("Returned from addArray(x,y). Result=%f\n",fResult);
       
       Vertex arr[2];
       arr[0] = k1;
       arr[1] = k2;
       printf("Calling vertexSum(arr)\n");
       result = vertexSum(arr);                          // remote call (we hope!)
       printf("Returned from vertexSum(arr). Result=%d\n",result);

     }

     //
     //  Handle networking errors -- for now, just print message and give up!
     //
     catch (C150Exception e) {
       // Write to debug log
       c150debug->printf(C150ALWAYSLOG,"Caught C150Exception: %s\n",
			 e.formattedExplanation().c_str());
       // In case we're logging to a file, write to the console too
       cerr << argv[0] << ": caught C150NetworkException: " << e.formattedExplanation() << endl;
     }

     return 0;
}



 
void setUpDebugLogging(const char *logname, int argc, char *argv[]) {


     ofstream *outstreamp = new ofstream(logname);
     DebugStream *filestreamp = new DebugStream(outstreamp);
     DebugStream::setDefaultLogger(filestreamp);

     //
     //  Put the program name and a timestamp on each line of the debug log.
     //
     c150debug->setPrefix(argv[0]);
     c150debug->enableTimestamp(); 

     
     c150debug->enableLogging(C150ALLDEBUG | C150RPCDEBUG | C150APPLICATION | C150NETWORKTRAFFIC | 
			      C150NETWORKDELIVERY); 
}
