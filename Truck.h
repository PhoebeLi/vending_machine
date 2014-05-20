#ifndef __TRUCK_H__
#define __TRUCK_H__

#include <iostream>
#include "Printer.h"
#include "NameServer.h"
#include "MPRNG.h"

_Task BottlingPlant;

using namespace std;


_Task Truck {
	Printer &printer;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int cargo[4];
	unsigned int remainingPickups();

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    virtual ~Truck();
};


#endif