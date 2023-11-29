/*In this second programming assignment you will implement a simple bank 
application. Your bank application will support the following features:
ü Open a new account, i.e. register a new user. The information stored is: first name, 
last name, address, phone number, and birth date. The account is also assigned a 
unique account number. 
ü Close an account. All the information stored about the particular customer is 
deleted. 
ü Deposit a given amount to an account. The user has to provide the account 
number.
ü Withdraw a given amount from an account. The user has to provide the account 
number and at no time can the balance of the account be less than zero.
ü Display account information when given the account number.
ü Print all the accounts sorted on customer account number, or the amount in the 
account.
ü Search and display the accounts based on customer last name, or phone number.
ü Save all the accounts to a file and also allow to read in from a file
*/
#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
//Declaring the Date struct to hold all dates
struct Date
{
	int day;
	int month;
	int year;
};
//Declaring the Account struct for all accounts
struct Account
{
	char firstName[150];
	char lastName[150];
	char address[300];
	char phoneNo[30];
	Date birthDay;
	int accountNo;
};
//Function Prototypes
void OpenAcct(Account*);
void CloseAcct(Account*);
void Deposit(Account*);
void Withdraw(Account*);
void AcctInfo(Account*);
void PrintAllAcct(Account*);
void Search(Account*);

int main()
{
	char Option;
	do
	{
		//Display the menu
		cout << "\nMENU";
		cout << "\nO:Open Account";
		cout << "\nC:Close Account";
		cout << "\nW:Withdraw";
		cout << "\nA:Account Info";
		cout << "\nP:Print All Accounts";
		cout << "\nS:Search For Account";
		cout << "\nQ:Quit";
		cout << "\nEnter a choice:";
		cin >> Option;

	} while (Option != 'q');

}