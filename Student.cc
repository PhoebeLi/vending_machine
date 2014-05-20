#include <iostream>
#include "Student.h"
#include "VendingMachine.h"
#include "WATCardOffice.h"

using namespace std;

extern MPRNG mprng;


/*********************** Student::Student **********************
 Purpose:   the constructor for Student
            
 
 ***************************************************************/

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ): 
printer(prt),
nameServer(nameServer),
cardOffice(cardOffice),
id(id),
maxPurchases(maxPurchases)
{}


/************* Student::~Student **************
 Purpose:   the desctructor for Student.

 ************************************************************/

Student::~Student() {
	delete this->card;
	printer.print(Printer::Student, id, 'F');
}


/************************************ Student::main ********************************
 Purpose:   The Student task main.
            A student begins by selecting a random number of bottles to purchase ,
            a random favourite flavour, creates a WATCard via the WATCardOffice 
            with a $5 balance, and obtains the location of a vending machine from 
            the name server.
            If there is not sufficient funds, the student will transfer money to its
            WATCard;
            If the vending machine is out of the student’s favourite flavour, the 
            student will obtain a new machine from the name server;
            otherwise, the student successfully bought a soda.

            If the WATCard is lost during transfer, the student must create a new WATCard 
            via the WATCardOffice with a $5 balance, and re-attempt to buy a soda.

            A student terminates after purchasing all the soda initially selected.

Returns:   void

 ***********************************************************************************/

void Student::main() {
	unsigned int numBottles = mprng(1,maxPurchases); // # bottles to buy
	VendingMachine::Flavours flavour = static_cast<VendingMachine::Flavours>(mprng(3));
	printer.print(Printer::Student, id, 'S', flavour, numBottles);
	
	WATCard::FWATCard fCard = cardOffice.create(id, 5);
	VendingMachine *machine = nameServer.getMachine(id);
	printer.print(Printer::Student, id, 'V', machine->getId());
	unsigned int cost = machine->cost();

	while (numBottles) // return after pruchasing all soda
	{
		yield(mprng(1,10));
		ACQUIRE_CARD:
		try {
			this->card = fCard();
		} catch(WATCardOffice::Lost e) {
			printer.print(Printer::Student, id, 'L');
			fCard = cardOffice.create(id, 5);
			goto ACQUIRE_CARD;
		} // try-catch
		
		VendingMachine::Status buyStatus = machine->buy(flavour, *card);
		switch (buyStatus) {
			case VendingMachine::BUY:
				printer.print(Printer::Student, id, 'B', card->getBalance());
				numBottles --;
				break;
			case VendingMachine::STOCK:
				machine = nameServer.getMachine(id); // go to new machine to buy soda
				printer.print(Printer::Student, id, 'V', machine->getId());
				break;
			case VendingMachine::FUNDS:
				fCard = cardOffice.transfer(id, cost+5, card);
				goto ACQUIRE_CARD;
				break;
			default:
				break;
		} // switch
	} // while
	
}

