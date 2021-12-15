#include <iostream>
#include "bank.h"

using namespace std;

Bank :: Bank(const int & L, const int & K) : last_customer(1), curr_serving(1), K(K), openCashiers(0), lastOpenedCashier(-1), lastServedCashier(-1)
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
    if (check_to_open() == false) // I don't have to open another cashier.
    {
        last_customer++;
        return true;
    }
    else // I have to open another cashier.
    {
        if(openCashiers != NUMBEROFCASHIERS) // I have cashier to open.
        {
            open(cashier[lastOpenedCashier + 1], lastOpenedCashier + 1);
            last_customer++;
            return true;
        }
        else // I have opened all the cashiers.
        {
            cout << "Sorry you cannot enter until some customers are served!" << endl;
            return false;
        }
    }
}

void Bank :: serve()
{
    if (openCashiers == 0) // All the cashiers are closed.
    {
        open(cashier[0], 0);
        cout << "Customer no : " << curr_serving << " by cashier no : " << 0 << endl;
        cashier[0]->serve();
        lastServedCashier = 0;
        if(cashier[0]->free() == false) // The cashier overworked so is close.
        {
            openCashiers--;
        }
    }
    else
    {
        int nextCashier;
        if (lastServedCashier == (NUMBEROFCASHIERS - 1)) // The last opened cashier is the last one.
        {
            nextCashier = 0;
        }
        else
        {
            nextCashier = lastServedCashier + 1;
        }

        for(int i = nextCashier; i < NUMBEROFCASHIERS; i++) 
        {
            if(cashier[i]->is_open() && cashier[i]->is_free()) // and the next cashier is open and free
            {
                cout << "Customer no : " << curr_serving << " by cashier no : " <<  i << endl;
                cashier[i]->serve();
                lastServedCashier = i;
                if(cashier[i]->free() == false) // The cashier overworked so is close.
                {
                    openCashiers--;
                }
                break;
            }
            
            if(i == (NUMBEROFCASHIERS - 1))
            {
                i = -1;
            }
        }
    }
    exit();
}

void Bank :: exit()
{
    curr_serving++;
    if(check_to_close())
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

void Bank :: open(Cashier *cashier, const int & cashierNumber)
{
    cashier -> open();
    openCashiers++;
    lastOpenedCashier = cashierNumber;
    cout << "The cashier : " << cashierNumber << " is open." << endl;
}

void Bank :: close(Cashier *cashier, const int & cashierNumber)
{
    cashier -> close();
    openCashiers--;
    cout << "The cashier : " << cashierNumber << " is closed." << endl;
}