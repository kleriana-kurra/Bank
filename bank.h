#ifndef BANK_H
#define BANK_H

#include <iostream>
#include "cashier.h"

using namespace std;
#define NUMBEROFCASHIERS 5

class Bank 
{
    int last_customer, curr_serving, K, openCashiers, lastOpenedCashier, lastServedCashier;
    Cashier *cashier[NUMBEROFCASHIERS];

    public : 
        Bank(const int &, const int &);
        ~Bank();

        bool enter();
        void serve();
        void exit();
        bool check_to_open();
        bool check_to_close();
        void open(Cashier *, const int &);
        void close(Cashier *, const int &);
        int waiting_customers(){return (last_customer - curr_serving);}
        int open_cashiers(){return openCashiers;}

        // void set(){}
        // void set(){}
        // void set(){}

        // string get() const{}
        // string get() const{}
        // int get() const{}
};

#endif