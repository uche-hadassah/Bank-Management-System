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
	static int accountNo;
	bool isOpen;
};
int Account::accountNo = 101;
//Function Prototypes
void OpenAcct(Account[],int);
void CloseAcct(Account[],int,int);
void Deposit(Account[]);
void Withdraw(Account[]);
void AcctInfo(Account[]);
void PrintAllAcct(Account[],int);
void Search(Account[]);

int main()
{
	char Option;
	int TotalAccount = 0;
	Account account[MAX];
	do
	{
		//Display the menu
		cout << "MENU";
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
		else if (Option == 'A' || Option == 'a')
		{
			int AccNum;
			cout << "Enter your account number:";
			cin >> AccNum;
			AcctInfo(account, AccNum);
		}
		else if (Option == 'P' || Option == 'p')
		{
			PrintAllAcct(account, TotalAccount);
		}
		cout << endl;
	} while (Option != 'q'&& Option != 'Q');
}
//The function to open an account
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
		cout << "The account number is:" << newAcct[i].accountNo;
		newAcct[i].accountNo++;//Increment the account number for the next customer
		newAcct[i].isOpen = true;//made the account open
}

//The function to close an account
void CloseAcct(Account account[],int Number, int Total)
{

	int tot = Total - 1;
	for (int i = 0; i < tot; i++)
	{
		account[i].accountNo--;
		if (account[i].accountNo == Number && account[i].isOpen == true)
		{
			cout << "\nClosing account " << Number;
			account[i].isOpen = false;
			return;
		}
    }
	cout << "\nAccount " << Number << " not found!";
}

//this function allows the user to deposit money ito their account
void Deposit(Account account[],int Number)
{

}

//This function allows the user to withdraw money from their account. They are not allowed to withdraw more than they possess
void Withdraw(Account account[],int Number)
{

}

//this function allows the user to view their account info, including how much they have in the account
void AcctInfo(Account account[],int Number)
{

}
//This function prints all accounts
void PrintAllAcct(Account account[], int Total)
{
	cout << "\nFOR PRIVACY REASONS, THE PERSONAL ACCOUNT NUMBERS WILL NOT BE DISPLAYED!";
	for (int i = 0; i < Total; i++)
	{
		if(account[i].isOpen == true)//Ensures that only opened accounts are displayed
		{
			cout << "\nDetails for account " << i + 1;
			cout << "\nOwner name:" << account[i].lastName << " " << account[i].firstName;
			cout << "\nDOB:" << account[i].birthDay.day << "/" << account[i].birthDay.month << "/" << account[i].birthDay.year;
			cout << "\nPhone Number:" << account[i].phoneNo;
			cout << "\nAddress:" << account[i].address << "," << account[i].city << "," << account[i].postCode;
		}
	}
}

//This function allows the user to search for their account by their account number
void Search(Account account[],int Number)
{

}