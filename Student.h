#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <iostream>
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "WATCard.h"
#include "MPRNG.h"

using namespace std;



_Task Student {
	Printer &printer;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;
	unsigned int maxPurchases;
	WATCard *card;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
    virtual ~Student();
};


#endif