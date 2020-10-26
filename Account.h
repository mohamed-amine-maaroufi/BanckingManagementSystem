#pragma once
#include <string>
class Account {

public:
	void readDataFromConsole(); //this function to read the input text entred by user in console
	void addAccount();	 // this function to add new account in file
	int ShowAllaccounts(); // this function read all accounts from file and display them line by line in console // return number of accounts
	int readAccountDetails(); //this function to read details of a choosed account from a file then fill the membre variables with the retreived data
	void showAccount(); // this function to show details of a choosed account
	void searchAccounts(); // this function show all accounts contain the entred keyword by user, the serach is case sensitive
	void editAccount(); // this function to update details of a choosed account
	void deleteAccount(); //this function to delete account
	Account();
	~Account();

private:
	std::string m_sAccountNumber;
	std::string m_sFirstName;
	std::string m_sLastName;
	float m_fTotalBalance;
};