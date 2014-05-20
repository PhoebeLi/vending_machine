#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include <iostream>
#include "Printer.h"
#include "Truck.h"
#include "NameServer.h"

using namespace std;


_Task BottlingPlant {
	Printer &printer;
	NameServer &nameServer;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;

	unsigned int products[4];
	Truck *truck;
	bool plantClosing;
    void main();
    unsigned int totalProducts();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    virtual ~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};


#endif