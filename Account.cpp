#include "Account.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>  

using namespace std;

Account::Account():m_sAccountNumber(""),m_sFirstName(""),m_sLastName(""),m_fTotalBalance(0.0)
{
	
}

Account::~Account()
{	
	
}


void Account::readDataFromConsole()
{
	cout << "\nEnter Account Number: ";
	cin >> m_sAccountNumber;
	cout << "\nEnter First Name: ";
	getline(cin >> std::ws, m_sFirstName);
	cout << "\nEnter Last Name: ";
	getline(cin >> std::ws, m_sLastName);
	cout << "\nEnter Balance: ";
	cin >> m_fTotalBalance;
	while (!cin.good())
	{
		cout << "\nYou entred bad number of balance, Enter the Balance again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> m_fTotalBalance;
	}
	cout << endl;
}


void Account::addAccount()
{	
	fstream l_fsFile;
	l_fsFile.exceptions(fstream::badbit);
	try
	{		
		l_fsFile.open("accounts.bank", ios::out|ios::app|ios::binary);
		if (l_fsFile.is_open())
		{
			readDataFromConsole();

			//if the file is empty, we dont't add the new line character "\n" at the begin of line
			string l_cNewline = "\n";
			l_fsFile.seekg(0, ios::end);
			if (l_fsFile.tellg() == 0) {
				l_cNewline = "";
			}

			string l_sRecord = l_cNewline + m_sAccountNumber + "|" + m_sFirstName + "|" + m_sLastName + "|" + to_string(m_fTotalBalance) + ";";
			l_fsFile << l_sRecord;
			l_fsFile.close();

			cout << "\n\n Account added with success" << endl;
		}
		else
		{
			cout << "Unable to open file for output.\n";
			return;
		}
	}
	catch (const fstream::failure& e)
	{
		cerr << "Exception opening/reading/closing file\n" << endl;
		cerr << e.what() <<endl;
	}

}

int Account::ShowAllaccounts()
{
	int l_iReturnLineNumber = 0;
	
	ifstream l_fsFile;
	l_fsFile.exceptions(ifstream::badbit);
	try
	{
		l_fsFile.open("accounts.bank", ios::in|ios::binary);
		if (l_fsFile.is_open())
		{			
			string l_sline;			
			while (getline(l_fsFile, l_sline)) {
				++l_iReturnLineNumber;
				cout << l_iReturnLineNumber << "- " << l_sline << endl;
			}

			if (l_iReturnLineNumber == 0)
			{
				cout << "\n \nEmpty File, there is no accounts !!!" << endl;
			}
			l_fsFile.close();
		}
		else
		{
			cout << "Unable to open file for output.\n";
			return 0;
		}

	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening/reading/closing file\n" << endl;
		cerr << e.what() << endl;
	}

	return l_iReturnLineNumber;
}

void Account::showAccount()
{
	cout << endl;
	cout << "################################################" << endl;
	cout << "Account Number: " << m_sAccountNumber << endl;
	cout << "First Name: " << m_sFirstName << endl;
	cout << "Last Name: " << m_sLastName << endl;
	cout << "Current Balance: $" << std::fixed << m_fTotalBalance << endl; //we use  std::fixed << ... to delete scientific notation of float number
	cout << "################################################" << endl;
}


int Account::readAccountDetails()
{
	int l_iReturnChoosedLineNumberByUser;

	int l_iAccountsNumber = ShowAllaccounts(); //display all accounts before choosing:
	if (l_iAccountsNumber == 0)
	{
		return 0;
	}
	
	cout << "\nEnter the number of line for the needed account : \n";
	cin >> l_iReturnChoosedLineNumberByUser;

	while (!cin.good())
	{
		cout << "\nInvalid choice, Enter a correct number of line for the needed account : \n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> l_iReturnChoosedLineNumberByUser;
	}


	ifstream l_fsFile;
	l_fsFile.exceptions(ifstream::badbit);
	try
	{
		l_fsFile.open("accounts.bank", ios::in|ios::binary);
		if (l_fsFile.is_open())
		{
			string l_sline = "";
			int l_iLineNumber = 0; 
			while (l_iLineNumber != l_iReturnChoosedLineNumberByUser &&  getline(l_fsFile, l_sline)) {
				//cout << l_iLineNumber  << "- "<< l_sline << endl;
				++l_iLineNumber;
			}

			if (l_iLineNumber == l_iReturnChoosedLineNumberByUser) {
				
				//split the retrevied line and fill the data to vector then membre variables
				char l_sdelimiter = '|';				

				// Vector of string to save tokens 
				vector <string> l_vTokens;

				// stringstream class check1 
				stringstream l_ssCheck(l_sline);

				string l_sToken;

				// Tokenizing w.r.t. space '|' 
				while (getline(l_ssCheck, l_sToken, l_sdelimiter))
				{
					l_vTokens.push_back(l_sToken);
				}

				//assigne the retrevied account data to membre variable
				m_sAccountNumber = l_vTokens[0];
				m_sFirstName = l_vTokens[1];
				m_sLastName = l_vTokens[2] ;
				m_fTotalBalance = stof(l_vTokens[3]);

				showAccount();

			}
			else {
				// The file contains fewer than two lines.
				cout << "The file contains fewer than " << l_iReturnChoosedLineNumberByUser << "\n";
				cout << "Choose a coorect number \n";
				return 0;
			}

			l_fsFile.close();
		}
		else
		{
			cout << "Unable to open file for output.\n";
			return 0;
		}

	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening/reading/closing file\n" << endl;
		cerr << e.what() << endl;
	}
	
	return l_iReturnChoosedLineNumberByUser;

}

void Account::searchAccounts()
{
	ifstream l_fsFile;

	try
	{
		l_fsFile.open("accounts.bank", ios::in|ios::binary);
		if (l_fsFile.is_open())
		{


			string l_sKeyWord = "";
			int l_iKeyWordExist = 0;
			cout << "\n\nEnter your key word to make a search : " << endl;		
			cin >> l_sKeyWord;
			cout << endl;

			int l_iLineNumberinFile = 0;
			string l_sline;
			while (getline(l_fsFile, l_sline)) 
			{
				++l_iLineNumberinFile;
				size_t l_szFound = l_sline.find(l_sKeyWord); //check if key word exist in the line 
				if (l_szFound != string::npos)
				{
					++l_iKeyWordExist;
					cout << l_iLineNumberinFile << "- " << l_sline << endl;
				}	
				
			}

			if (l_iKeyWordExist == 0)
			{
				cout << "This key Word \"" << l_sKeyWord << "\" not exist !!!" << endl;
				return;
			
			}

			if (l_iLineNumberinFile == 0)
			{
				cout << "\n \nEmpty File, there is no accounts !!!" << endl;
			}
			l_fsFile.close();

		}
		else
		{
			cout << "Unable to open file for output.\n";
			return;
		}
	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening/reading/closing file\n" << endl;
		cerr << e.what() << endl;
	}
	
}

void Account::editAccount()
{	
	int l_iChoosedLineNumberByUser = readAccountDetails();

	if (l_iChoosedLineNumberByUser == 0)
	{
		return;
	}
	else 
	{
		fstream l_fsFile;
		l_fsFile.exceptions(fstream::badbit);
		try
		{
			l_fsFile.open("accounts.bank", ios::in | ios::binary); //openfile for reading
			if (l_fsFile.is_open())
			{
				string l_sline = "";
				int l_iLineNumber = 0;
				vector<std::string> l_vLines;				

				//store all lines in vector, because we can't write and read from file at the same time
				while (getline(l_fsFile, l_sline))
				{
					++l_iLineNumber;
					l_vLines.push_back(l_sline);
				}

				l_fsFile.close(); //close file after reading

				cout << "\n\nEnter the new informations of the account :" << endl;
				readDataFromConsole();

				string l_cNewline = "\n";
				
				l_fsFile.open("accounts.bank", ios::out|ios::binary); //open file for writing, using the option ios::out to clear the old content of file and add the new content from the vector l_vLines

				//re-write the lines from vector to the file
				for (int i = 0; i < l_vLines.size(); ++i)
				{					
					if (i == l_iChoosedLineNumberByUser - 1)
					{	
						if (i == 0)
						{
							//we dont't add the new line character "\n" at the first line of file
							l_cNewline = "";
						}
						else
						{
							l_cNewline = "\n";
						}
						
						//add the new edited account
						l_sline = l_cNewline + m_sAccountNumber + "|" + m_sFirstName + "|" + m_sLastName + "|" + to_string(m_fTotalBalance) + ";";
					}
					else
					{
						if (i == 0)
						{
							//we dont't add the new line character "\n" at the first line of file
							l_cNewline = "";
						}
						else
						{
							l_cNewline = "\n";
						}
						l_sline = l_cNewline + l_vLines[i];
					}

					l_fsFile << l_sline;
				}

				l_fsFile.close();

				cout << "\n\n Account edited with success" << endl;
			}
			else
			{
				cout << "Unable to open file for output.\n";
				return;
			}

		}
		catch (const fstream::failure& e)
		{
			cerr << "Exception opening/reading/closing file\n" << endl;
			cerr << e.what() << endl;
		}

	}	
}


void Account::deleteAccount()
{
	int l_iChoosedLineNumberByUser = readAccountDetails();

	if (l_iChoosedLineNumberByUser == 0)
	{
		return;
	}
	else
	{
		fstream l_fsFile;
		l_fsFile.exceptions(fstream::badbit);
		try
		{
			l_fsFile.open("accounts.bank", ios::in | ios::binary); //openfile for reading
			if (l_fsFile.is_open())
			{
				string l_sline = "";
				int l_iLineNumber = 0;
				vector<std::string> l_vLines;

				//store all lines in vector, because we can't write and read from file at the same time
				while (getline(l_fsFile, l_sline))
				{
					++l_iLineNumber;
					if (l_iLineNumber == l_iChoosedLineNumberByUser)
					{
						continue;
					}
					else
					{
						l_vLines.push_back(l_sline);
					}
					
				}

				l_fsFile.close(); //close file after reading

				/*
				 write the data from vector to file
				*/
			
				l_fsFile.open("accounts.bank", ios::out | ios::binary); //open file for writing, using the option ios::out to clear the old content of file and add the new content from the vector l_vLines
				string l_cNewline = "\n";
				//re-write the lines from vector to the file
				for (int i = 0; i < l_vLines.size(); ++i)
				{					
					if (i == 0)
					{
						//we dont't add the new line character "\n" at the first line of file
						l_cNewline = "";
					}
					else
					{
						l_cNewline = "\n";
					}

					l_sline = l_cNewline + l_vLines[i];					

					l_fsFile << l_sline;
				}

				l_vLines.clear();
				l_fsFile.close(); //close file after writing

				cout << "\n\n Account deleted with success" << endl;
			}
			else
			{
				cout << "Unable to open file for output.\n";
				return;
			}

		}
		catch (const fstream::failure& e)
		{
			cerr << "Exception opening/reading/closing file\n" << endl;
			cerr << e.what() << endl;
		}

	}
}
