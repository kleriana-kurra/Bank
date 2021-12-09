#include <iostream>
#include "bank.h"

using namespace std;

Bank :: Bank(const int &L, const int &K) : last_customer(1), curr_serving(1), K(K), openCashiers(0), lastOpenedCashier(-1), lastServedCashier(0)
{
    for (int i = 0; i < NUMBEROFCASHIERS; i++)
    {
        cashier[i] = new Cashier(L);
    }

    open(cashier[0], 0);
}

Bank :: ~Bank()
{
    for (int i = 0; i < NUMBEROFCASHIERS; i++)
        delete cashier[i];
}

bool Bank :: enter()
{
    if (check_to_open() == false) // den xriazete na anoiksw allo tameio.
    {
        last_customer++;
        return true;
    }
    else // prepei na anoiksw kainoyrio tameio
    {
        if (openCashiers == (NUMBEROFCASHIERS - 1)) // exw anoixei idi ola ta tameia.
        {
            cout << "Sorry you cannot enter until some customers are served!" << endl;
            return false;
        }
        open(cashier[lastOpenedCashier + 1], lastOpenedCashier + 1);
        last_customer++;
        return true;
    }
}

void Bank :: serve()
{
    if (openCashiers == 0)
    {
        open(cashier[0], 0);
        cout << "Customer no : " << curr_serving << " by cashier no : " << 0 << endl;
        cashier[0]->serve();
        lastServedCashier = 0;
        cashier[0]->free();
    }
    else
    {
        if (lastServedCashier == (NUMBEROFCASHIERS - 1))
        {
            cout << "Customer no : " << curr_serving << " by cashier no : " << 0 << endl;
            cashier[0]->serve();
            lastServedCashier = 0;
            cashier[0]->free();
        }
        else
        {
            cout << "Customer no : " << curr_serving << " by cashier no : " << lastServedCashier + 1 << endl;
            cashier[lastServedCashier + 1]->serve();
            lastServedCashier++;
            cashier[lastServedCashier + 1]->free();
        }
    }
    exit();
}

void Bank :: exit()
{
    curr_serving++;
    if(check_to_close ())
    {
        for(int i; i < NUMBEROFCASHIERS; i++)
        {
            if(cashier[i]->is_open() && cashier[i]->is_free())
            {
                cashier[i]->close();
                break;
            }
        }
    }
}

bool Bank :: check_to_open()
{
    if (waiting_customers() > (openCashiers * K))
        return true;
    return false;
}

bool Bank :: check_to_close()
{
    if (waiting_customers() <= ((openCashiers - 1) * K))
        return true;
    return false;
}

void Bank :: open(Cashier *cashier, const int &cashierNumber)
{
    cashier->open();
    openCashiers++;
    lastOpenedCashier = cashierNumber;
    cout << "The cashier : " << cashierNumber << " is open." << endl;
}

void Bank :: close(Cashier *cashier, const int &cashierNumber)
{
    cashier->close();
    openCashiers--;
    cout << "The cashier : " << cashierNumber << " is closed." << endl;
}
