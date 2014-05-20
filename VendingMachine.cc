#include <iostream>
#include "VendingMachine.h"
using namespace std;


/*************** VendingMachine::VendingMachine ******************
 Purpose:   the constructor for VendingMachine
            
 
 ******************************************************************/

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ):
printer(prt),
nameServer(nameServer),
id(id),
sodaCost(sodaCost),
maxStockPerFlavour(maxStockPerFlavour),
restocking(false)
{
	for (int i = 0; i < 4; ++i) stocks[i] = 0;
	nameServer.VMregister(this); // register on nameServer
}


/*********************** VendingMachine::buy ****************************
 Purpose:  A student calls buy to obtain one of their favourite sodas. 
 			If the specified soda is unavailable, buy returns STOCK;
 			if the student has insufficient funds to purchase the soda, 
 			buy returns FUNDS; 
 			otherwise, the student’s WATCard is debited by the cost of 
 			a soda and buy returns BUY.


Returns:   Status

 ****************************************************************/

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
	if (restocking) waitRestock.wait();
	if (!stocks[flavour]) return STOCK;
	int balance = card.getBalance();
	if (sodaCost > balance) return FUNDS;
	stocks[flavour] -= 1;
	card.withdraw(sodaCost);
	printer.print( Printer::Vending, id, 'B', flavour, stocks[flavour] );
	return BUY;
}



/******************** VendingMachine::signalAll ****************************
 Purpose:   wake up all student tasks who are blocked and waiting for 
 			the truck to finish restocking.

Returns:   void

 ***********************************************************************/

void VendingMachine::signalAll() {
	while(!waitRestock.empty()) {
		waitRestock.signalBlock();
	} // while
}


/********************* VendingMachine::inventory **************************
 Purpose:   The truck calls inventory to return a pointer to an array 
 			containing the amount of each kind of soda currently in the 
 			vending machine. 
 			The truck uses this information to transfer into each machine 
 			as much of its stock of new soda as fits.

Returns:   pointer to unsigned ints (the inventory)

 **************************************************************************/

unsigned int * VendingMachine::inventory() {
	this->restocking = true;
	return this->stocks;
}


/*********************** VendingMachine::cost ***********************
 Purpose:  returns the cost of purchasing a soda for this machine. 

Returns:   unsigned int

 ********************************************************************/

unsigned int VendingMachine::cost() {
	return this->sodaCost;
}



/*********************** VendingMachine::getId **********************
 Purpose:  returns the identification number of the vending machine

Returns:   unsigned int

 ********************************************************************/

unsigned int VendingMachine::getId() {
	return this->id;
}




/*********************** VendingMachine::restocked ******************************
 Purpose:   called by the truck restocked to indicate the operation is complete,
 			after transferring new soda into the machine by directly modifying 
 			the array passed from inventory.  
 			The vending machine cannot accept buy calls during restocking. 

Returns:   void

 *****************************************************************************/

void VendingMachine::restocked() {
	this->restocking = false;
}



/************************** VendingMachine::main *******************************
 Purpose:   The VendingMachine task main.
			It prints start message,
			accept its member routines recursivley until destructor is called,
			and then prints out finish message.

Returns:   void

 ****************************************************************************/

void VendingMachine::main() {
	printer.print(Printer::Vending, id, 'S', sodaCost);
	for ( ;; )
	{
		_Accept(~VendingMachine) {
			printer.print(Printer::Vending, id, 'F' );
			break;
		} or _Accept(buy) {

		} or _Accept(inventory) {
			printer.print( Printer::Vending, id, 'r' );
		} or _Accept(restocked) {
			printer.print(Printer::Vending, id, 'R' );
			signalAll();
		} // _Accept
	}
}