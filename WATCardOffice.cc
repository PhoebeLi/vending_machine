#include <iostream>
#include <queue>
#include "WATCardOffice.h"

extern MPRNG mprng;
using namespace std;

/*************** WATCardOffice::WATCardOffice ******************
 Purpose:   the constructor for WATCardOffice
            
 
 ******************************************************************/

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ):
printer(prt),
bank(bank),
numCouriers(numCouriers),
officeClosing(false)
{
    couriers = new Courier*[numCouriers];
    for (unsigned int i = 0; i < numCouriers; ++i)
    {
        couriers[i] = new Courier(i, *this, bank);
    } // for
    printer.print(Printer::WATCardOffice, 'S');     
}



/************* WATCardOffice::~WATCardOffice **************
 Purpose:   the desctructor for WATCardOffice. 

 ************************************************************/

WATCardOffice::~WATCardOffice() {
    for (unsigned int i = 0; i < numCouriers; ++i)
    {
        delete couriers[i];
    } // for
    delete [] couriers;
    printer.print(Printer::WATCardOffice, 'F');
}



/*********************** WATCardOffice::main ****************************
 Purpose:   the WATCardOffice task main.
            it prints start message,
            yields a random number of times, between 0 and 19 inclusive,
            and then vote at the vote-tallier.

Returns:   void

 ****************************************************************/

void WATCardOffice::main() {
    for (;;)
    {
        _Accept(~WATCardOffice) {
            this->officeClosing = true;
            // this is not busy waiting since the for loop iterates numCourier times
            for (int i = 0; i < this->numCouriers; ++i)
            {
                _Accept(requestWork){} or _Else {}
            }
            this->signalAll();
            break;
        } or _Accept(create) {

        } or _Accept(transfer) {

        } or _Accept(requestWork) {

        } // _Accept
    } // for
}


/********************* WATCardOffice::create **********************
 Purpose:   A student performs an asynchronous call to create to 
            create a “real” WATCard with an initial balance.
            
 return:    FWATCard

 ******************************************************************/

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job * j = new Job(Job::CREATE, NULL, sid, amount); 
    jobs.push(j);
    printer.print(Printer::WATCardOffice, 'C', (int)sid, (int)amount);
    if (!waitJobs.empty()) waitJobs.signal();
    return j->result;              
}




/********************* WATCardOffice::transfer ********************
 Purpose:   A student performs an asynchronous call to transfer 
            when its WATCard indicates there is insufficient funds 
            to buy a soda. 
            
 return:    FWATCard

 ******************************************************************/

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Job * j = new Job(Job::TRANSFER, card, sid, amount);          
    jobs.push(j);
    printer.print(Printer::WATCardOffice, 'T', (int)sid, (int)amount);  
    if (!waitJobs.empty()) waitJobs.signal();
    return j->result;              
}





/****************** WATCardOffice::requestWork ********************
 Purpose:   Each courier task calls requestWork, blocks until a Job 
            request is ready, and then receives the next Job request 
            as the result of the call.
            
 return:    pointer to Job

 ******************************************************************/

WATCardOffice::Job * WATCardOffice::requestWork() {
    while (this->jobs.empty() && !officeClosing)
    {
        waitJobs.wait();
    } // while
    if (!officeClosing)
    {   
        Job * j = jobs.front();
        jobs.pop();
        printer.print(Printer::WATCardOffice, 'W');
        return j;
    } else {
        return NULL;
    } // if
}



/*************** WATCardOffice::signalAll ******************
 Purpose:   wake up all Couriers blocked on waiting list.
            
 return:    void

 ******************************************************************/

void WATCardOffice::signalAll() {
    while (!waitJobs.empty()) waitJobs.signalBlock();
}




/************* WATCardOffice::Courier::Courier **************
 Purpose:   the constructor for Courier. 

 ************************************************************/

WATCardOffice::Courier::Courier(unsigned int cid, WATCardOffice &office, Bank &bank):
cid(cid),
office(office),
bank(bank)
{}




/************* WATCardOffice::Courier::~Courier **************
 Purpose:   the desctructor for Courier. 

 ************************************************************/

WATCardOffice::Courier::~Courier() {
    office.printer.print(Printer::Courier, cid, 'F');
}




/*************** WATCardOffice::Courier::main ******************
 Purpose:   does the work for WATCardOffice
 return:    void

 ******************************************************************/

void WATCardOffice::Courier::main() {    
    office.printer.print(Printer::Courier, this->cid, 'S');
    for ( ;; )
    {           
        Job * j = office.requestWork();
        if (j == NULL) { 
            break;
        }
        if (j->jobType == Job::CREATE) {
            j->card = new WATCard();
        } // if
        office.printer.print(Printer::Courier, cid, 't', j->sid, j->amount);
        bank.withdraw(j->sid, j->amount); // get money from bank, block until enough balance
        j->card->deposit(j->amount);
        office.printer.print(Printer::Courier, cid, 'T', j->sid,j->amount);
        if (mprng(5) == 0) // card lost!
        {
            delete j->card;
            j->result.exception(new Lost());    
        } else {
            j->result.delivery(j->card);
        } // if
        delete j;
    } // for   
}



/****************** WATCardOffice::Job::Job ******************
 Purpose:   the constructor for Job. 

 ************************************************************/

WATCardOffice::Job::Job(JobType jobType, WATCard * card, unsigned int sid, unsigned int amount):
jobType(jobType),
card(card),
sid(sid),
amount(amount)
{}



