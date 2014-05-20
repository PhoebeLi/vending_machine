#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;

class MPRNG {
  public:
    MPRNG( unsigned int seed = 1009 ) { srand( seed ); }// set seed
    void seed( unsigned int seed ) { srand( seed ); } // set seed
    unsigned int operator()() { return rand(); }  // [0,UINT_MAX]
    unsigned int operator()( unsigned int u ) { return operator()() % (u + 1); } // [0,u]
    unsigned int operator()( unsigned int l, unsigned int u ) { return operator()( u - l ) + l; } // [l,u]
};


MPRNG RAND;


class output
{
public:
  output(){
      cout << "SodaCost\t"<<                RAND(1,10)   <<endl ;
      cout << "NumStudents\t"<<             RAND(1,40)   <<endl ;
      cout << "MaxPurchases\t"<<            RAND(1,40)   <<endl ;
      cout << "NumVendingMachines\t"<<      RAND(1,40)   <<endl ;
      cout << "MaxStockPerFlavour\t"<<      RAND(1,40)   <<endl ;
      cout << "MaxShippedPerFlavour\t"<<    RAND(1,40)   <<endl ;
      cout << "TimeBetweenShipments\t"<<    RAND(1,10)   <<endl ;
      cout << "ParentalDelay\t"<<           RAND(1,10)   <<endl ;
      cout << "NumCouriers\t"<<             RAND(1,40)   <<endl ;
  }
  ~output(){};

};



int main(int argc, char **argv)
{
  RAND.seed(getpid());
  delete new output();

}
