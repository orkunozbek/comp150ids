#include "c150streamsocket.h"
#include "c150debug.h"
#include <fstream>

using namespace std;          
using namespace C150NETWORK; 

void checkAndPrintMessage(ssize_t readlen, char *buf, ssize_t bufferlen);
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
const int msgArg = 2;        // message text is 2nd arg
 
int 
main(int argc, char *argv[]) {

     ssize_t readlen;              // amount of data read from socket
     char incomingMessage[512];   // received message data

     setUpDebugLogging("pingstreamclientdebug.txt",argc, argv);

     if (argc != 3) {
       fprintf(stderr,"Correct syntxt is: %s <servername> <msgtxt>\n", argv[0]);
          exit(1);
     }


     try {

        // Create the socket
        c150debug->printf(C150APPLICATION,"Creating C150StreamSocket");
        C150StreamSocket *sock = new C150StreamSocket();

		sock -> connect(argv[serverArg]);  

        c150debug->printf(C150APPLICATION,"%s: Writing message: \"%s\"",
			  argv[0], argv[msgArg]);
        sock -> write(argv[msgArg], strlen(argv[msgArg])+1); // +1 includes the null

        // Read the response from the server
        c150debug->printf(C150APPLICATION,"%s: Returned from write",
				  argv[0]);

		c150debug->printf(C150APPLICATION,"%s: doing read()", argv[0]);	  
		readlen = sock -> read(incomingMessage, sizeof(incomingMessage));
	

		if (readlen == 0) {
			c150debug->printf(C150APPLICATION,"%s: UNEXPECTED 0 LENGTH READ", argv[0]);	       
			if (sock -> eof()) {
				c150debug->printf(C150APPLICATION,"%s: REASON WAS UNEXPECTED EOF", argv[0]);	       
			}
			if (sock -> timedout()) {
				c150debug->printf(C150APPLICATION,"%s: REASON WAS UNEXPECTED TIMEOUT", argv[0]);	       
			}
		}
		else {
			checkAndPrintMessage(readlen, incomingMessage, readlen);
		}
        c150debug->printf(C150APPLICATION,"%s: closing socket", argv[0]);	  
        sock -> close();   // tell other end "that's all folks!"

     }
     catch (C150NetworkException e) {
       // Write to debug log
       c150debug->printf(C150ALWAYSLOG,"Caught C150NetworkException: %s\n",
			 e.formattedExplanation().c_str());
       // In case we're logging to a file, write to the console too
       cerr << argv[0] << ": caught C150NetworkException: " << e.formattedExplanation() << endl;
     }

     return 0;
}



void
checkAndPrintMessage(ssize_t readlen, char *msg, ssize_t bufferlen) {

    if (readlen == 0) {
      throw C150NetworkException("Unexpected zero length read in client");
    }


    if (readlen > (int)(bufferlen)) {
      throw C150NetworkException("Unexpected over length read in client");
    }

    if(msg[readlen-1] != '\0') {
     throw C150NetworkException("Client received message that was not null terminated");	
    };

    string s(msg);
    cleanString(s);


    c150debug->printf(C150APPLICATION,"PRINTING RESPONSE: Response received is \"%s\"\n", s.c_str());
    printf("Response received is \"%s\"\n", s.c_str());

}


void setUpDebugLogging(const char *logname, int argc, char *argv[]) {
     ofstream *outstreamp = new ofstream(logname);
     DebugStream *filestreamp = new DebugStream(outstreamp);
     DebugStream::setDefaultLogger(filestreamp);
     c150debug->setPrefix(argv[0]);
     c150debug->enableTimestamp(); 
     c150debug->enableLogging(C150APPLICATION | C150NETWORKTRAFFIC | 
			      C150NETWORKDELIVERY); 
}
