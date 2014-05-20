#include <iostream>
#include <sstream>
#include <fstream>
#include "WATCardOffice.h"
#include "Student.h"
#include "MPRNG.h"
#include "Bank.h"
#include "Parent.h"
#include "WATCard.h"
#include "config.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"
#include "Printer.h"

#include <unistd.h>
using namespace std;

MPRNG mprng;

void uMain::main() {
	//error checking
	string configFile = "soda.config";
	int seed = getpid();
	switch (argc) {
        case 3:
        	configFile = argv[1];
          	seed = atoi(argv[2]);
          	if (seed <= 0)
          	{
          		osacquire(cerr) << "Usage: ./soda_64 [ config-file [ random-seed (> 0) ] ]" << endl;
          		exit(1);
          	}
        break;
        case 2:
        	configFile = argv[1];
        break;
        case 1:
        break;
        default:
        	osacquire(cerr) << "Usage: ./soda_64 [ config-file [ random-seed (> 0) ] ]" << endl;
        	exit(1);
    } // switch

    mprng.seed(seed);
	ConfigParms cparms;
    processConfigFile(configFile.c_str(), cparms);

	// create things in order
	Printer printer( cparms.numStudents, cparms.numVendingMachines, cparms.numCouriers );
	Bank bank(cparms.numStudents);
	Parent parent(printer, bank, cparms.numStudents, cparms.parentalDelay);
	WATCardOffice cardOffice(printer, bank, cparms.numCouriers);
	NameServer nameServer( printer, cparms.numVendingMachines, cparms.numStudents );
	
	VendingMachine *machines[cparms.numVendingMachines];
	Student *students[cparms.numStudents];
	
	for (unsigned int i = 0; i < cparms.numVendingMachines; ++i)
	{
		machines[i] =  new VendingMachine( printer, nameServer, i, cparms.sodaCost,
cparms.maxStockPerFlavour );
	} // for
	
	BottlingPlant *bottlingPlant = new BottlingPlant( printer, nameServer, cparms.numVendingMachines,
cparms.maxShippedPerFlavour, cparms.maxStockPerFlavour,
cparms.timeBetweenShipments );

	for (unsigned int i = 0; i < cparms.numStudents; ++i)
	{
		students[i] = new Student( printer, nameServer, cardOffice, i,
cparms.maxPurchases );
	} // for

    for (unsigned int i = 0; i < cparms.numStudents; ++i) {
        delete students[i];
    } // for

    delete bottlingPlant;

    for (unsigned int i = 0; i < cparms.numVendingMachines; ++i) {
        delete machines[i];
    } // for
}





















