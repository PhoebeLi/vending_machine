#include <iostream>
#include "BottlingPlant.h"


extern MPRNG mprng;
using namespace std;



/**************** BottlingPlant::BottlingPlant *******************
 Purpose:   the constructor for BottlingPlant
            
 
 ***************************************************************/

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):
printer(prt),
nameServer(nameServer),
numVendingMachines(numVendingMachines),
maxShippedPerFlavour(maxShippedPerFlavour),
maxStockPerFlavour(maxStockPerFlavour),
timeBetweenShipments(timeBetweenShipments),
plantClosing(false)
{
	this->truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
	for (int i = 0; i < 4; ++i)
	{
		products[i] = 0;
	} // for
}



/**************** BottlingPlant::BottlingPlant *******************
 Purpose:   the destructor for BottlingPlant
            
 
 ***************************************************************/


BottlingPlant::~BottlingPlant() {
	delete truck;
	printer.print(Printer::BottlingPlant, 'F');
}




/********************* BottlingPlant::getShipment *************************
 Purpose:   returns true if the bottling plant is closing down and cargo 
 			is not changed, and false otherwise with the shipment copied 
 			into the cargo array passed by the truck.
 			
Returns:   bool

 ****************************************************************************/

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (this->plantClosing) return true;
	for (int i = 0; i < 4; ++i)
	{
		cargo[i] = products[i];
	} // for
	return false;
	
}             	



/********************* BottlingPlant::totalProducts *************************
 Purpose:  returns the total number of products produced by BottlingPlant.
 			
Returns:   unsigned int

 ****************************************************************************/

unsigned int BottlingPlant::totalProducts() {
	return products[0] + products[1] + products[2] + products[3];
}



/****************************** BottlingPlant::main *********************************
 Purpose:   The BottlingPlant task main.
 			It prints the start message,
 			accepts calls to getShipment recursively,
 			and finishes when a call to desctructor occurred.
 			
Returns:   void

 ****************************************************************************/

void BottlingPlant::main() {
	printer.print(Printer::BottlingPlant, 'S');
	for ( ;; )
	{
		yield(timeBetweenShipments); // simulate producing time
		for (int i = 0; i < 4; ++i)
		{
			products[i] = mprng(maxShippedPerFlavour);
		} // for
		
		printer.print(Printer::BottlingPlant, 'G', this->totalProducts());
		_Accept(~BottlingPlant) {
			this->plantClosing = true;
			 _Accept(getShipment);	
			break;
		} or _Accept(getShipment) { 
			printer.print(Printer::BottlingPlant, 'P');
		} // _Accept
	} // for
}

