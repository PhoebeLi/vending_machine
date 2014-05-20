#ifndef __BANK_H__
#define __BANK_H__

#include <iostream>

using namespace std;


_Monitor Bank {
	unsigned int numStudents;
	unsigned int *balances;
	uCondition waitGift;
	void signalAll();
  public:
    Bank( unsigned int numStudents );
    virtual ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};


#endif