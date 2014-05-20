#ifndef __PRINTER_H__
#define __PRINTER_H__

//#include "global.h"
#include <iostream>
#include <cassert>
#include <map>
#include <vector>


using namespace std;
_Cormonitor Printer {
	void main();
public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    virtual ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
private:

  void printHeader();
  void flashMap(bool isDotFlash = false);
  void insertData();
  bool canInsertData();
  unsigned int upperRangTranslation(unsigned int k);

	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	unsigned int kind;
	unsigned int lid;
	char state;
	int value1;
	int value2;

  std::map<unsigned int , 
            std::map< unsigned int , 
                      pair<char, 
                            pair<unsigned int , unsigned int > 
                          > 
                    > 
          > dataMap;
};

#endif /* __PRINTER_H__ */