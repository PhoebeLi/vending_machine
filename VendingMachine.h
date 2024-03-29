#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include <iostream>
#include "Printer.h"
#include "WATCard.h"
#include "NameServer.h"

_Task NameServer;

using namespace std;


_Task VendingMachine {
    Printer &printer;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int stocks[4]; // array of stockings 
    bool restocking;
    uCondition waitRestock;
    void signalAll();

    void main();
  public:
    enum Flavours { BLUES, CREAM, ROOT, JAZZ };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};


#endif