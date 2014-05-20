#include "Printer.h"

/***************** Printer::main **********************
 Purpose:   Coroutine main of Cormonitor Printer

 ******************************************************/
void Printer::main() {
    printHeader();
    for(;;){
        if (!canInsertData()) {
            flashMap();
        }
        if (state == 'F' && !dataMap.empty()) {
            flashMap();
        }
        insertData();
        if (state == 'F') {
            flashMap(true);
        }
        suspend();
    }
}


/***************** Printer::_printHeader ****************
 Purpose:   printer the header of program
 return:  void
 ******************************************************/
void Printer::printHeader(){
    cout<<"Parent\tWATOff\tNames\tTruck\tPlant";
    for (unsigned int i = 0; i < this->numStudents; ++i) {
        cout << "\t" << "Stud" << i;
    }
    for (unsigned int i = 0; i < this->numVendingMachines; ++i) {
        cout << "\t" << "Mach" << i ;
    }
    for (unsigned int i = 0; i < this->numCouriers; ++i) {
        cout << "\t" << "Cour" << i;
    }
    cout << endl;
    cout <<"*******";
    for (unsigned int i = 0; i < (4 + numStudents + numVendingMachines + numCouriers); ++i)
    {
        cout  << "\t" <<"*******";
    }
    cout << endl;
}


/***************** Printer::_upperRangTranslation ****************
 Purpose:   translatable how many time need to print for each Kind
 return:    number of time (unsigned int)
 ******************************************************/
unsigned int Printer::upperRangTranslation(unsigned int k){
    switch (k){
        case ((unsigned int) Printer::Student):
            return this->numStudents;
        case ((unsigned int) Printer::Vending):
            return this->numVendingMachines;
        case ((unsigned int) Printer::Courier):
            return this->numCouriers;
        default:
            return 1;
    }
}

/***************** Printer::_flashMap ****************
 Purpose:   print the contain of map and clears it
 return:    void
 ******************************************************/
void Printer::flashMap(bool isDotFlash){
    // goes though 8 kind of value
    for (unsigned int k = 0; k < (3 + 5); ++k) {
        // if the value exist print its value, otherwise print a tab
        if (this->dataMap.find(k) != this->dataMap.end()) {
            // if k is in upper range of the enum, which mean there could be multiple instance of the value
            if (k == ((unsigned int) Printer::Student) ||
                k == ((unsigned int) Printer::Vending) ||
                k == ((unsigned int) Printer::Courier) ) {
                // for the kind k find how many of those possible value could exits
                unsigned int times = upperRangTranslation(k);
                // print that many kind
                for (unsigned int i = 0; i < times; ++i) {
                    if (dataMap[k].find(i) != dataMap[k].end()){
                        // output the char
                        cout << dataMap[k][i].first;
                        if (dataMap[k][i].second.first != ((unsigned int)-1)) {
                            // first number
                            cout << dataMap[k][i].second.first;
                            if (dataMap[k][i].second.second != ((unsigned int)-1)) {
                                // second number
                                cout << "," <<dataMap[k][i].second.second;
                            }
                        }
                    } else if (isDotFlash) {
                        // if it is a dot flash
                        cout << "...";
                    }
                    cout << "\t";
                }
            } else {
                // other wise it in lower range and should only have one instance
                unsigned int i = 0;
                if (dataMap[k].find(i) != dataMap[k].end()){
                    // output the char
                    cout << dataMap[k][i].first;
                    if (dataMap[k][i].second.first != ((unsigned int)-1)) {
                        // first number
                        cout << dataMap[k][i].second.first;
                        if (dataMap[k][i].second.second != ((unsigned int)-1))
                        {
                            // second number
                            cout << "," <<dataMap[k][i].second.second;
                        }
                    }
                } else if (isDotFlash) {
                    cout << "...";
                }
                cout << "\t";
            }
            
        } else if (isDotFlash) {
            // if nothing is found should either print dots or a tab
            if (k == ((unsigned int) Printer::Student) ||
                k == ((unsigned int) Printer::Vending) ||
                k == ((unsigned int) Printer::Courier) ) {
                unsigned int times = upperRangTranslation(k);
                for (unsigned int i = 0; i < times; ++i) {
                    cout << "...";
                    cout << "\t";
                }
            }else {
                cout << "...";
                cout << "\t";
            }
        }else {
            // if nothing is found should either print dots or a tab
            if (k == ((unsigned int) Printer::Student) ||
                k == ((unsigned int) Printer::Vending) ||
                k == ((unsigned int) Printer::Courier) ) {
                unsigned int times = upperRangTranslation (k);
                for (unsigned int i = 0; i < times; ++i) {
                    cout << "\t";
                }
            }else{
                cout << "\t";
            }
        }
    }
    cout << endl;
    dataMap.clear();
    
}


/***************** Printer::_insertData ****************
 Purpose:   insert data into the map
 return:  void
 ******************************************************/
void Printer::insertData(){
    static int counter = 0;
    static char last_State = this->state;
    if (last_State != this->state) {
        counter =0;
        last_State= this->state;
    }else{
        counter++;
        if (counter > 200) exit(1);
    }
    
    if (dataMap.find(kind) == dataMap.end()) {
        // if the kind entry doesnt exist in the map
        dataMap[kind] = std::map<unsigned int, pair<char,
        pair<unsigned int , unsigned int >
        >
        > ();
    }
    // if there isnt a idea for it create one
    if (dataMap[kind].find(lid) == dataMap[kind].end()) {
        dataMap[kind][lid] = pair<char,
        pair <unsigned int , unsigned int > > (
                                               state,
                                               pair <unsigned int , unsigned int >(
                                                                                   value1, value2
                                                                                   )
                                               );
        
    } else {
        // some thing went really wrong.
        assert(false);
    }
}


/***************** Printer::_canInsertData ****************
 Purpose:   if with current number can be inserted into the map
 return:  result (bool)
 ******************************************************/
bool Printer::canInsertData(){
    if (!dataMap.empty()) {
        if (dataMap.find(kind) != dataMap.end()) {
            if (kind <= ((unsigned int) BottlingPlant)) {
                return false;
            } else {
                if (!(dataMap[kind].find(lid) == dataMap[kind].end())) {
                    return false;
                }
            }
        }
    }
    return true;
}


/***************** Printer::Printer ****************
 Purpose:   the constructor
 ******************************************************/

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
: numStudents(numStudents), numVendingMachines(numVendingMachines),
numCouriers(numCouriers) {
    
}


/***************** Printer::Printer ****************
 Purpose:   the destructor
 ******************************************************/

Printer::~Printer(){
    if (!dataMap.empty()) {
        flashMap();
    }
    cout << "***********************" << endl;
}

/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, char state ) {
    this->kind = static_cast<unsigned int>(kind);
    this->state = state;
    this->lid = 0;
    this->value1 = (unsigned int)-1;
    this->value2 = (unsigned int)-1;
    
    resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, char state, int value1 ) {
    this->kind = static_cast<unsigned int>(kind);
    this->state = state;
    this->lid = 0;
    this->value1 = value1;
    this->value2 = (unsigned int)-1;
    
    resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, char state, int value1, int value2 ) {
    this->kind = static_cast<unsigned int>(kind);
    this->lid = 0;
    this->state = state;
    this->value1 = value1;
    this->value2 = value2;
    
    resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, unsigned int lid, char state ) {
    this->kind = static_cast<unsigned int>(kind);
    this->lid = lid;
    this->state = state;
    this->value1 = (unsigned int)-1;
    this->value2 = (unsigned int)-1;
    
    resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    this->kind = static_cast<unsigned int>(kind);
    this->lid = lid;
    this->state = state;
    this->value1 = value1;
    this->value2 = (unsigned int)-1;
        
    resume();
}



/***************** Printer::print ****************
 Purpose:   print to the printer with given arguments
 ******************************************************/
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    this->kind = static_cast<unsigned int>(kind);
    this->lid = lid;
    this->state = state;
    this->value1 = value1;
    this->value2 = value2;
    
    resume();
}
