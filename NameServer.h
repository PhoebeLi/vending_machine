#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include <iostream>
#include "Printer.h"

_Task VendingMachine;

using namespace std;


_Task NameServer {
    Printer &printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    unsigned int machinePos;

    VendingMachine **machineList;
    unsigned int *positions;
    bool closing;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    virtual ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};


#endif