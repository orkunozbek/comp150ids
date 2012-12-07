// --------------------------------------------------------------
//
//                        arithmeticclient.cpp
//
//        Author: Noah Mendelsohn         
//   
//
//        This is a test program designed to call a few demonstration
//        functions, after first enabling the COMP 150-IDS rpcproxyhelper.
//        (The purpose of the helper is to open a TCP stream connection
//        to the proper server, and to leave the socket pointer where
//        the generated proxies can find it.
//
//        NOTE: Although this example does nothing except test the
//        functions, we may test your proxies and stubs with client
//        applications that do real work. 
//
//        NOTE: When actually testing your RPC submission, you will use
//        a different client application for each set of functions. This
//        one is just to show a simple example.
//
//        NOTE: The only thing that makes this different from 
//        an ordinary local application is the call to
//        rpcproxyinitialize. If you commented that out, you could
//        link this with the local version of simplefunction.o
//        (which has the remotable function implementations)			      
//
//        COMMAND LINE
//
//              arithmeticclient <servername> 
//
//        OPERATION
//
//
//       Copyright: 2012 Noah Mendelsohn
//     
// --------------------------------------------------------------


// IMPORTANT! WE INCLUDE THE IDL FILE AS IT DEFINES THE INTERFACES
// TO THE FUNCTIONS WE'RE REMOTING. OF COURSE, THE PARTICULAR IDL FILE
// IS CHOSEN ACCORDING TO THE TEST OR APPLICATION
// 
// NOTE THAT THIS IS THE SAME IDL FILE INCLUDED WITH THE PROXIES
// AND STUBS, AND ALSO USED AS INPUT TO AUTOMATIC PROXY/STUB
// GENERATOR PROGRAM

#include "arithmetic.idl"

#include "rpcproxyhelper.h"

#include "c150debug.h"
#include "c150grading.h"
#include <fstream>

using namespace std;          // for C++ std library
using namespace C150NETWORK;  // for all the comp150 utilities 

// forward declarations
void setUpDebugLogging(const char *logname, int argc, char *argv[]);


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                    Command line arguments
//
// The following are used as subscripts to argv, the command line arguments
// If we want to change the command line syntax, doing this
// symbolically makes it a bit easier.
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

const int serverArg = 1;     // server name is 1st arg


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                           main program
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 
int 
main(int argc, char *argv[]) {

     //
     //  Set up debug message logging
     //
     setUpDebugLogging("simplefunctionclientdebug.txt",argc, argv);

     //
     // Make sure command line looks right
     //
     if (argc != 2) {
       fprintf(stderr,"Correct syntxt is: %s <servername> \n", argv[0]);
       exit(1);
     }

     //
     //  DO THIS FIRST OR YOUR ASSIGNMENT WON'T BE GRADED!
     //
     
     GRADEME(argc, argv);

     //
     //     Call the functions and see if they return
     //
     try {
       int result; 

       //
       // Set up the socket so the proxies can find it
       //
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
	
       printf("Calling getStudent(5)\n");
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



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                     setUpDebugLogging
//
//        For COMP 150-IDS, a set of standards utilities
//        are provided for logging timestamped debug messages.
//        You can use them to write your own messages, but 
//        more importantly, the communication libraries provided
//        to you will write into the same logs.
//
//        As shown below, you can use the enableLogging
//        method to choose which classes of messages will show up:
//        You may want to turn on a lot for some debugging, then
//        turn off some when it gets too noisy and your core code is
//        working. You can also make up and use your own flags
//        to create different classes of debug output within your
//        application code
//
//        NEEDSWORK: should be factored into shared code w/pingstreamserver
//        NEEDSWORK: document arguments
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 
void setUpDebugLogging(const char *logname, int argc, char *argv[]) {

     //   
     //           Choose where debug output should go
     //
     // The default is that debug output goes to cerr.
     //
     // Uncomment the following three lines to direct
     // debug output to a file. Comment them
     // to default to the console.
     //
     // Note: the new DebugStream and ofstream MUST live after we return
     // from setUpDebugLogging, so we have to allocate
     // them dynamically.
     //
     //
     // Explanation: 
     // 
     //     The first line is ordinary C++ to open a file
     //     as an output stream.
     //
     //     The second line wraps that will all the services
     //     of a comp 150-IDS debug stream, and names that filestreamp.
     //
     //     The third line replaces the global variable c150debug
     //     and sets it to point to the new debugstream. Since c150debug
     //     is what all the c150 debug routines use to find the debug stream,
     //     you've now effectively overridden the default.
     //
     ofstream *outstreamp = new ofstream(logname);
     DebugStream *filestreamp = new DebugStream(outstreamp);
     DebugStream::setDefaultLogger(filestreamp);

     //
     //  Put the program name and a timestamp on each line of the debug log.
     //
     c150debug->setPrefix(argv[0]);
     c150debug->enableTimestamp(); 

     //
     // Ask to receive all classes of debug message
     //
     // See c150debug.h for other classes you can enable. To get more than
     // one class, you can or (|) the flags together and pass the combined
     // mask to c150debug -> enableLogging 
     //
     // By the way, the default is to disable all output except for
     // messages written with the C150ALWAYSLOG flag. Those are typically
     // used only for things like fatal errors. So, the default is
     // for the system to run quietly without producing debug output.
     //
     c150debug->enableLogging(C150ALLDEBUG | C150RPCDEBUG | C150APPLICATION | C150NETWORKTRAFFIC | 
			      C150NETWORKDELIVERY); 
}
