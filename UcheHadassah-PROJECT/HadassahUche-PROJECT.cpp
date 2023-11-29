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
const int MAX = 500;
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
	char phoneNo[30];
	char address[300];
	char city[50];
	char postCode[10];
	Date birthDay;
	int accountNo;
	bool isOpen;
    static int counter;
};
int Account::counter = 101;
//Function Prototypes
void OpenAcct(Account[],int);
void CloseAcct(Account[],int,int);
void Deposit(Account[]);
void Withdraw(Account[]);
void AcctInfo(Account[]);
void PrintAllAcct(Account[]);
void Search(Account[]);

int main()
{
	char Option;
	static int TotalAccount = 0;
	Account account[MAX];
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
		cout << "\nEnter the operation you wish to perform:";
		cin >> Option;

		if (Option == 'O' || Option == 'o')
		{
			TotalAccount++;
			OpenAcct(account, TotalAccount);
		}
		else if (Option == 'C' || Option == 'c')
		{
			int AccNum;
			cout << "Enter your account number:";
			cin >> AccNum;
			CloseAcct(account, AccNum, TotalAccount);
		}
	} while (Option != 'q'&& Option != 'Q');

}
void OpenAcct(Account newAcct[],int Total)
{
	int i = Total - 1;
		cin.ignore();
		cout << "Enter your first name:";
		cin.getline(newAcct[i].firstName,150);
		cout << "Enter your last name:";
		cin.getline(newAcct[i].lastName, 150);
		cout << "Enter your phone number:";
		cin.getline(newAcct[i].phoneNo, 30);
		cout << "Enter your street address:";
		cin.getline(newAcct[i].address, 50);
		cout << "Enter your city:";
		cin.getline(newAcct[i].city, 50);
		cout << "Enter your post code:";
		cin.getline(newAcct[i].postCode, 10);
		cout << "Enter your birthday."<< endl;
		cout << "Year:";
		cin >> newAcct[i].birthDay.year;
		cout << "Month:";
		cin >> newAcct[i].birthDay.month;
		cout << "Day:";
		cin >> newAcct[i].birthDay.day;
		cin.ignore();
		cout << "The account number is:" << newAcct[i].counter;
		newAcct[i].counter++;
}

void CloseAcct(Account account[],int Number, int Total)
{
	for (int i = 0; i < Total; i++)
	{
		if (account[i].accountNo == Number && account[i].isOpen)
		{
			cout << "Closing account " << Number;
			account[i].isOpen = false;
			return;
		}
    }
	cout << "Account " << Number << " not found!";
}

void PrintAllAcct(Account[])
{

}