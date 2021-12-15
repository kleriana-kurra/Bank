#include <iostream>
#include "bank.h"

using namespace std;


int main(int argc, char* argv[])
{
    cout << "                             --- THE PROGRAM STARTED ---                                 " << endl ;

	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       A. Nα δημιουργεί μια τράπεζα." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	int K = stoi(argv[1]), M = stoi(argv[2]), N = stoi(argv[3]), L = stoi(argv[4]);

    cout << "K = " << K << " M = " << M << " N = " << N << " L = " << L << endl;
	Bank bank(L, K);

	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       Β. Για κάθε " << N << " πελάτες που εισέρχονται στην τράπεζα αυτή να εξυπηρετεί όσους είναι δυνατό " << endl <<
			"                          με βάση τα ταμεία που είναι ανοικτά (αυτό εξαρτάται από το πλήθος " << N << " των πελατών που " << endl <<
    		"                          μπήκαν). Η διαδικασία αυτή να επαναλαμβάνεται " << M << " ϕορές." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	int notEnteredCustomers = 0, enteredCustomers = 0;
	for(int i = 0; i < M; i++) // M repeats
	{
		for(int j = 0; j < N; j++) // trying to enter N customers
		{
			if(bank.enter()) // If the customer can't enter the bank
			{
				enteredCustomers++;
			}
			else
				notEnteredCustomers++;
		}
	}

	cout << enteredCustomers << " entered the bank and " << notEnteredCustomers << " didn't entered the bank, so " << enteredCustomers << " will be served now." << endl;
	
	for(int i = 0; i < enteredCustomers; i++)
	{
		bank.serve();
	}

	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       Γ. Στη συνέχεια να εξυπηρετούνται όλοι οι υπόλοιποι πελάτες που περιμένουν να εξυπηρετηθούν." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	if(notEnteredCustomers == 0)
	{
		cout << "All the customers have entered the bank and served." << endl << endl;
	}

	while(notEnteredCustomers != 0)
	{
		int customersToEnter = notEnteredCustomers;
		int customersEntered = 0;
		for(int i = 0; i < customersToEnter; i++)
		{
			if(bank.enter())
			{
				customersEntered++;
				notEnteredCustomers--;
			}
		}

		for(int i = 0; i < customersEntered; i++)
		{
			bank.serve();
		}
	}

	cout << "                             --- THE PROGRAM ENDED ---                                 " << endl << endl ;
	return 0;
}