#include <iostream>
#include "Bank.h"

using namespace std;




/*************************** Bank::Bank ***********************
 Purpose:   the constructor for Bank
            
 
 **************************************************************/

Bank::Bank( unsigned int numStudents ):
numStudents(numStudents)
{
	balances = new unsigned int[numStudents];
	for (unsigned int i = 0; i < numStudents; ++i)
	{
		balances[i] = 0;
	} // for
}


/*************************** Bank::Bank ***********************
 Purpose:   the destructor for Bank
            
 
 **************************************************************/

Bank::~Bank() {
	delete [] balances;
}



/**************************** Bank::deposit ****************************
 Purpose:  The parent calls deposit to endow gifts to a specific student. 

Returns:   void

 ***********************************************************************/

void Bank::deposit( unsigned int id, unsigned int amount ) {
	balances[id] += amount;
	signalAll();
}



/*************************** Bank::withdraw ****************************
 Purpose:  A courier calls withdraw to transfer money on behalf of 
 			the WATCard office for a specific student. 

Returns:   void

 ***********************************************************************/

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (balances[id] - amount < 0) waitGift.wait();
	assert(!(balances[id] - amount < 0));
	balances[id] -= amount;
}



/************************** Bank::signalAll ****************************
 Purpose:  wake up all student tasks who are blocked and waiting for 
 			the truck to finish restocking.

Returns:   void

 ***********************************************************************/

void Bank::signalAll() {
	while (!waitGift.empty()) waitGift.signal();
}