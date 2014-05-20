TYPE:=INT

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -DTABLETYPE_${TYPE}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = Parent.o VendingMachine.o WATCard.o WATCardOffice.o Printer.o Student.o Bank.o NameServer.o BottlingPlant.o Truck.o config.o sodaDriver.o
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

.PHONY : clean

all : ${EXEC}					# build all executables

-include ImplType

ifeq (${IMPLTYPE},${TYPE})			# same implementation type as last time ?
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${TYPE},)					# no implementation type specified ?
# set type to previous type
TYPE=${IMPLTYPE}
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC}
${EXEC} :
	rm -f ImplType
	touch q2table.h
	${MAKE} ${EXEC} TYPE="${TYPE}"
endif
endif

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType
	sleep 2

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} *.class ImplType
