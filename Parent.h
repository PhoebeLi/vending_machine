#ifndef __PARENT_H__
#define __PARENT_H__

#include <iostream>
#include "Printer.h"
#include "Bank.h"
#include "MPRNG.h"

using namespace std;


_Task Parent {
	Printer &printer;
	Bank &bank;
	unsigned int numStudents;
	unsigned int parentalDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};


#endif