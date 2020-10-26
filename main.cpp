#include "Account.h"
#include <iostream>
using namespace std;

int main()
{
	Account l_oAccount;
	char l_cSystemChoice;

	cout << "\n Banking Management System: \n";

	while (true)
	{
		cout << "\n\n \t\t ***************** Choose an option below ***************** : \n";
		cout << "a- Add new account : \n";
		cout << "b- Show all accounts : \n";
		cout << "c- Show account details : \n";
		cout << "d- Search account : \n";
		cout << "e- Update account : \n";
		cout << "f- Delete account : \n";
		cout << "Q- Quit : \n";
		cout << "Enter your choice : \n";

		cin >> l_cSystemChoice;
		char l_cLowerchoice = tolower(l_cSystemChoice);

		switch (l_cLowerchoice)
		{
			case 'a':
				cout << "\n\n \t #Add new account : " << endl;
				l_oAccount.addAccount();
				break;
			case 'b':
				cout << "\n\n \t #Show all accounts : " << endl;
				l_oAccount.ShowAllaccounts();
				break;
			case 'c':
				cout << "\n\n \t #Show account details : " << endl;
				l_oAccount.readAccountDetails();
				break;
			case 'd':
				cout << "\n\n \t #Search for accounts : " << endl;
				l_oAccount.searchAccounts();
				break;
			case 'e':
				cout << "\n\n \t #Update account : " << endl;
				l_oAccount.editAccount();
				break;
			case 'f':
				cout << "\n\n \t #Delete account : " << endl;
				l_oAccount.deleteAccount();
				break;
			case 'q':
				cout << "\n\n \t Good bye !!! " << endl;
				exit(0);
				break;
			default:
				cout << "\n\n \t Invalid choice !!! " << endl;
				break;
		}
	}
	
	system("pause");
	return 0;
}