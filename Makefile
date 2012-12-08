# Makefile for COMP 150IDS RPC Samples
#
#    Copyright 2012 - Noah Mendelsohn
#
#
# Useful targets:
#
#
#    pingstreamclient  - demonstration message ping client using TCP streams
#    pingstreamserver  - demonstration message ping server
#    simplefunctionclient - sample RPC client
#    simplefunctionserver - sample RPC server
#    idldeclarationtst      - demonstrates the IDL parsing framework
#
#    clean       - clean out all compiled object and executable files
#    all         - (default target) make sure everything's compiled
#

# Do all C++ compies with g++
CPP = g++

# change following line if your rpgenerate is not in current directory
RPCSTUBGEN = ./stubgenerator
RPCPROXYGEN = ./proxygenerator
# Where the COMP 150 shared utilities live, including c150ids.a and userports.csv
# Note that environment variable COMP150IDS must be set for this to work!

C150LIB = $(COMP150IDS)/files/c150Utils/
C150AR = $(C150LIB)c150ids.a

# RPC framework is shared archive
C150IDSRPC = $(COMP150IDS)/files/RPC.framework/
C150IDSRPCAR = $(C150IDSRPC)c150idsrpc.a

CPPFLAGS = -g -Wall -Werror -I$(C150IDSRPC) -I$(C150LIB)
# CPPFLAGS = -g -Wall -Werror  -I$(C150LIB)


LDFLAGS = 
INCLUDES = $(C150LIB)c150streamsocket.h $(C150LIB)c150network.h $(C150LIB)c150exceptions.h $(C150LIB)c150debug.h $(C150LIB)c150utility.h $(C150LIB)c150grading.h $(C150IDSRPC)IDLToken.h $(C150IDSRPC)tokenizeddeclarations.h  $(C150IDSRPC)tokenizeddeclaration.h $(C150IDSRPC)declarations.h $(C150IDSRPC)declaration.h $(C150IDSRPC)functiondeclaration.h $(C150IDSRPC)typedeclaration.h $(C150IDSRPC)arg_or_member_declaration.h rpcproxyhelper.h rpcstubhelper.h TypeConverters.h simplefunction.idl arithmetic.idl floatarithmetic.idl 

all:  stubgenerator proxygenerator 

stubgenerator: stubgenerator.o TypeConverters.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o stubgenerator stubgenerator.o TypeConverters.o $(C150AR) $(C150IDSRPCAR)
	
proxygenerator: proxygenerator.o TypeConverters.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o proxygenerator proxygenerator.o TypeConverters.o $(C150AR) $(C150IDSRPCAR)	




	
#floatarithmeticclient: floatarithmeticclient.o rpcproxyhelper.o floatarithmetic.proxy.o TypeConverters.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
#	$(CPP) -o floatarithmeticclient floatarithmeticclient.o rpcproxyhelper.o floatarithmetic.proxy.o TypeConverters.o  $(C150AR) $(C150IDSRPCAR) 

	
#floatarithmeticserver: floatarithmetic.stub.o rpcserver.o rpcstubhelper.o arithmetic.o TypeConverters.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
#	$(CPP) -o floatarithmeticserver rpcserver.o floatarithmetic.stub.o floatarithmetic.o rpcstubhelper.o TypeConverters.o $(C150AR) $(C150IDSRPCAR) 	
	
	

%.stub.cpp: %.idl $(RPCSTUBGEN)
	$(RPCSTUBGEN) $<
	
%.proxy.cpp: %.idl $(RPCPROXYGEN)
	$(RPCPROXYGEN) $<

# make .o from .cpp

%.o:%.cpp  $(INCLUDES)
	$(CPP) -c  $(CPPFLAGS) $< 



# clean up everything we build dynamically (probably missing .cpps from .idl)
clean:
	 rm -f pingstreamclient pingstreamserver idldeclarationtst simplefunctionclient simplefunctionserver *.o


