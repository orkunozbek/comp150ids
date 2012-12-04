#include "c150streamsocket.h"
#include "c150debug.h"
#include <fstream>
#include <cstdlib> 


using namespace C150NETWORK;  // for all the comp150 utilities 

void setUpDebugLogging(const char *logname, int argc, char *argv[]);
 
int
main(int argc, char *argv[])
{

     ssize_t readlen;             // amount of data read from socket
     char incomingMessage[512];   // received message data

     // Command line arguments processing
     if (argc != 1)  {
       fprintf(stderr,"Correct syntxt is: %s\n", argv[0]);
          exit(1);
     }
     setUpDebugLogging("pingstreamserverdebug.txt",argc, argv);

     // Indent server log
     c150debug->setIndent("    ");
     
     // Create tcp socket and listen connections
     try {
       c150debug->printf(C150APPLICATION,"Creating C150StreamSocket");
       C150StreamSocket *sock = new C150StreamSocket();

       c150debug->printf(C150APPLICATION,"Calling C150StreamSocket::listen");
       sock -> listen();


       c150debug->printf(C150APPLICATION,"Ready to accept messages");
       
       // Accept Connections
       while (1) {

         c150debug->printf(C150APPLICATION,"Calling C150StreamSocket::accept");
         sock -> accept();
	 
       
         while(1)	{
         	readlen = sock -> read(incomingMessage, sizeof(incomingMessage)-1);
  
         	if (readlen == 0) {
	  	    	c150debug->printf(C150APPLICATION,"Read zero length message, checking EOF");
		  	    if (sock -> eof()) {
		  	       	c150debug->printf(C150APPLICATION,"EOF signaled on input");
		  	       	break;
		  	    } else {
		  	      	cerr << "pingstreamserver: unexpected 0 length read without EOF. Giving up!" << endl;
		  	      	return 8;
		  	    }
	  	    }
  
		  // Clean up the message
	  	  	incomingMessage[readlen] = '\0'; // make sure null terminated
	  	  	string incoming(incomingMessage); // Convert to C++ string ...it's slightly
	  	                                    // easier to work with, and cleanString
	  	                                    // expects it
	  	    cleanString(incoming);
            c150debug->printf(C150APPLICATION,"Successfully read %d bytes. Message=\"%s\"",
  			    readlen, incoming.c_str());
  
  			string response = "You said " + incoming;
  			if (incoming=="ping" || incoming == "Ping" || incoming == "PING") 
  				response += " and I say PONG. Thank you for playing!";
  			else
  				response += ". Don't you know how to play ping pong?";
  
  			c150debug->printf(C150APPLICATION,"Responding with message=\"%s\"",
  			    				response.c_str());
  			sock -> write(response.c_str(), response.length()+1);
  		}
        c150debug->printf(C150APPLICATION,"Calling C150StreamSocket::close");
        sock -> close();
       }
     }
     catch (C150NetworkException e) {
       c150debug->printf(C150ALWAYSLOG,"Caught C150NetworkException: %s\n",
			 e.formattedExplanation().c_str());
       cerr << argv[0] << ": caught C150NetworkException: " << e.formattedExplanation() << endl;
     }
     return 4;
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

