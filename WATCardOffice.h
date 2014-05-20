#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include <iostream>
#include <queue>
#include "Printer.h"
#include "Bank.h"
#include "WATCard.h"
#include "MPRNG.h"




using namespace std;


_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        //Args args;                         // call arguments (YOU DEFINE "Args")
        enum JobType { CREATE, TRANSFER };   // the type of Job
        JobType jobType;
        WATCard *card;
        unsigned int sid;
        unsigned int amount;
        WATCard::FWATCard result;                   // return future
        Job(JobType jobType, WATCard *card, unsigned int sid, unsigned int amount);
    };

    _Task Courier {
        unsigned int cid;
        WATCardOffice &office;
        Bank &bank;
        void main();
    public:

        Courier(unsigned int cid, WATCardOffice &office, Bank &bank);
        ~Courier();
     };                 // communicates with bank
    
    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    bool officeClosing;
    uCondition waitJobs;
    Courier **couriers;
    queue<Job *>jobs;
    void signalAll();
    void main();

  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    virtual ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};


#endif