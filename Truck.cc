#include <iostream>
#include "Truck.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"
using namespace std;

extern MPRNG mprng;



/*********************** Truck::Truck **********************
 Purpose:   the constructor for Student
            
 
 ***********************************************************/

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
printer(prt),
nameServer(nameServer),
plant(plant),
numVendingMachines(numVendingMachines),
maxStockPerFlavour(maxStockPerFlavour)
{}


/*********************** Truck::~Truck **********************
 Purpose:   the destructor for Student
            
 
 ************************************************************/

Truck::~Truck() {
	printer.print(Printer::Truck, 'F');
}



/************************* Truck::remainingPickups ***************************
 Purpose:   returns the total number of soda remaining in the cargo of
 			the truck.
 			
Returns:   unsigned int

 ****************************************************************************/

unsigned int Truck::remainingPickups() {
	return cargo[0]+cargo[1]+cargo[2]+cargo[3];
}



/****************************** Truck::main *********************************
 Purpose:   The Truck task main.

 			
Returns:   void

 ****************************************************************************/

void Truck::main() {
	printer.print(Printer::Truck, 'S');
	for ( ;; )
	{
		yield(mprng(1, 10));
		VendingMachine **machineList = nameServer.getMachineList();
		if (plant.getShipment(this->cargo)) break; // Bottling plant closing down
		printer.print(Printer::Truck, 'P', remainingPickups());
		for (unsigned int i = 0; i < numVendingMachines; ++i)
		{
			unsigned int unfilled = 0;
			printer.print(Printer::Truck, 'd', (int)i, (int)remainingPickups());
			VendingMachine *machine = machineList[i];
			unsigned int *inventory = machine->inventory();
			for (unsigned int j = 0; j < 4; ++j)
			{	
				unsigned int remaining = inventory[j];
				unsigned int produced = this->cargo[j];
				if (produced == 0) continue;
				if ((this->maxStockPerFlavour - remaining) >= produced)
				{
					inventory[j] += produced;
					this->cargo[j] = 0;
					unfilled += maxStockPerFlavour - inventory[j];
				} else {
					inventory[j] += this->maxStockPerFlavour - remaining;
					this->cargo[j] -= this->maxStockPerFlavour - remaining;
				} // if	
			} // for
			if (unfilled) {
				printer.print(Printer::Truck, 'U', (int)machine->getId(), (int)unfilled);
			} // if
			printer.print(Printer::Truck, 'D', (int)i, (int)remainingPickups());
			machine->restocked(); // indicate finish restocking
			if (!remainingPickups()) break;
		} // for
	} // for
}