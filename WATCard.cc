#include <iostream>
#include "WATCard.h"
using namespace std;


/********************** WATCard::WATCard *************************
 Purpose:   the constructor for WATCard
            
 
 ******************************************************************/

WATCard::WATCard():
balance(0) 
{}



/************************ WATCard::deposit ***********************
 Purpose:   A Courier calls deposit to transfer money from
 			bank account to WATCard.
            
 return:    void

 ******************************************************************/

void WATCard::deposit( unsigned int amount ) {
	this->balance += amount;
}



/************************ WATCard::withdraw ***********************
 Purpose:   A vending machine calls withdraw to charge the price
 			of a soda when a soda is purchased.
            
 return:    void

 ******************************************************************/

void WATCard::withdraw( unsigned int amount ) {
	this->balance -= amount;
}




/********************** WATCard::getBalance ***********************
 Purpose:   The Courier calls deposit to transfer money from
 			bank account to WATCard.
            
 return:    unsigned int

 ******************************************************************/

unsigned int WATCard::getBalance() {
	return this->balance;
}



WATCard::WATCard( const WATCard & other) :
	balance(other.balance)
{}


WATCard &WATCard::operator=( const WATCard & other) {
	this->balance = other.balance;
	return *this;
}