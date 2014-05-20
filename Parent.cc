#include <iostream>
#include "Parent.h"
using namespace std;

extern MPRNG mprng;




/*************************** Parent::Parent ***********************
 Purpose:   the constructor for Parent
            
 
 **************************************************************/

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ): 
printer(prt),
bank(bank),
numStudents(numStudents),
parentalDelay(parentalDelay)
{}


/****************************** Parent::main *********************************
 Purpose:   The Parent task periodically gives a random amount of 
 			money [$1, $3] to a random student. Before each gift is transfered, 
 			the parent yields for parentalDelay times. (The parent is busy 
 			waiting for the call to its destructor.)

Returns:   void

 ****************************************************************************/

void Parent::main() {
	printer.print(Printer::Parent, 'S');
	for ( ;; )
	{
		_Accept(~Parent) {
			printer.print(Printer::Parent, 'F');
			break;
		} _Else {} // busy waiting for the call to desctructor
		unsigned int amount = mprng(1,3);
		unsigned int sid = mprng(0, numStudents-1);
		yield(parentalDelay);
		printer.print(Printer::Parent, 'D', sid, amount);
		bank.deposit(sid, amount);
	} // for
}