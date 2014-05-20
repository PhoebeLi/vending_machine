#include <iostream>
#include "NameServer.h"
#include "VendingMachine.h"

using namespace std;



/******************** NameServer::NameServer ********************
 Purpose:   the constructor for NameServer
            
 
 ***************************************************************/

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ):
printer(prt),
numVendingMachines(numVendingMachines),
numStudents(numStudents),
machinePos(0)
{
	machineList = new VendingMachine *[numVendingMachines];
	positions = new unsigned int[numStudents];
	for (unsigned int i = 0; i < numStudents; ++i)
	{
		positions[i] = i % numVendingMachines;
	} // for
}



/******************** NameServer::NameServer ********************
 Purpose:   the destructor for NameServer
            
 
 ***************************************************************/

NameServer::~NameServer() {
	delete [] machineList;
	delete [] positions;
	printer.print(Printer::NameServer, 'F' );
}


/******************** NameServer::VMregister ***********************
 Purpose:   Vending machines call VMregister to register themselves 
 			so students can subsequently locate them.


Returns:   VendingMachine * (a VendingMachine)

 *******************************************************************/

void NameServer::VMregister( VendingMachine *vendingmachine ) {
	printer.print(Printer::NameServer, 'R', vendingmachine->getId() );
	machineList[machinePos] = vendingmachine;
	machinePos ++;
	assert(machinePos <= (numVendingMachines + 1));
}




/******************** NameServer::getMachine *********************
 Purpose:   A student calls getMachine to find a vending machine. 
 			Then name server cycles through the vending machines 
 			separately for each student starting from the initial 
 			position via modulo incrementing to ensure a student 
 			has a chance to visit every machine. 

Returns:   VendingMachine * (a VendingMachine)

 ****************************************************************/

VendingMachine * NameServer::getMachine( unsigned int id ) {
	VendingMachine *machine = machineList[positions[id]];
	printer.print(Printer::NameServer, 'N', id, machine->getId());
	positions[id] = (positions[id]+1) % numVendingMachines;
	return machine;
}



/*********************** NameServer::main *************************
 Purpose:   The truck calls getMachineList to obtain an array of 
 			pointers to vending machines so it can visit each 
 			machine to deliver new soda.

Returns:   VendingMachine ** (a list of VendingMachines)

 ****************************************************************/

VendingMachine ** NameServer::getMachineList() {
	return machineList;
}



/*********************** NameServer::main ****************************
 Purpose:   the NameServer task main.
            it prints start message,
            yields a random number of times, between 0 and 19 inclusive,
            and then vote at the vote-tallier.

Returns:   void

 ****************************************************************/

void NameServer::main() {
	printer.print(Printer::NameServer, 'S' );
	for ( ;; )
	{
		_Accept(~NameServer) {			
			break;
		} or _Accept(VMregister) {

		} or _Accept(getMachineList) {
			
		} or _Accept(getMachine) {

		} // _Accept
	}
}