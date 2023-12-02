/*This program is the implementation of a simple Bank Application
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
	double balance = 0.0;//I might need this when working with the deposit and withdraw functions
	static int accountNo;
	bool isOpen;
};
int Account::accountNo = 101;
//Function Prototypes
void OpenAcct(Account[],int);
void CloseAcct(Account[],int,int);
void Deposit(Account[],int,int,double);
void Withdraw(Account[],int,int,double);
void AcctInfo(Account[],int,int);
void PrintAllAcct(Account[],int);
void Search(Account[],int,int);

int main()
{
	char Option;
	int TotalAccount = 0;
	int AccNum;
	double amount;
	Account* account = new Account[MAX];
	do
	{
		//Display the menu
		cout << "MENU";
		cout << "\nO:Open Account";
		cout << "\nC:Close Account";
		cout << "\nD:Deposit";
		cout << "\nW:Withdraw";
		cout << "\nA:Account Info";
		cout << "\nP:Print All Accounts";
		cout << "\nS:Search For Account";
		cout << "\nQ:Quit";
		cout << "\nEnter the operation you wish to perform:";
		cin >> Option;
		switch(Option)

		{
		  case 'O':
		  case 'o':
				TotalAccount++;
				OpenAcct(account, TotalAccount);
				break;
		  case 'C':
		  case 'c':
				cout << "Enter your account number:";
				cin >> AccNum;
				CloseAcct(account, AccNum, TotalAccount);
				break;
		  case 'D':
			  case 'd':
				cout << "Enter your account number:";
				cin >> AccNum;
				cout << "You can only deposit up to $5000 at once.";
				cout << "How much will you like to deposit:";
				do
				{
					cin >> amount;
					while (amount < 0.1)
					{
						cout << "You cannot deposit $" << amount << ". Please enter a valid amount:";
						cin >> amount;
					}
					while (amount > 5000.0)
					{
						cout << "You can only deposit up to $5000 at once. Enter the amount you wish to deposit:";
						cin >> amount;
					}
				} while (amount < 0.1 || amount > 5000.0);
				Deposit(account, TotalAccount, AccNum, amount);
				break;
			  case 'W':
			  case 'w':
				cout << "Enter your account number:";
				cin >> AccNum;
				cout << "How much will you like to withdraw:";
				cin >> amount;
				if (amount == 0.0)
				{
					cout << "No money has been withdrawn.";
				}
				else
				{
					Withdraw(account, TotalAccount, AccNum, amount);
				}
				break;
			  case 'A':
			  case 'a':
				cout << "Enter your account number:";
				cin >> AccNum;
				AcctInfo(account, TotalAccount, AccNum);
				break;
			  case 'P':
			  case 'p':
				PrintAllAcct(account, TotalAccount);
				break;
			  case 'S':
			  case 's':
				cout << "Enter your account number:";
				cin >> AccNum;
				Search(account, TotalAccount, AccNum);
				break;
			  case 'Q':
			  case 'q':
				  cout << "Thank you for your time ^^";
				break;
			  default:
				cout << "\nInvalid option. Please enter a valid option from the menu:";
				break;
			cout << endl;
		}
	} while (Option != 'q' && Option != 'Q');
	delete[] account;
}

/*Open a new account, i.e. register a new user.The information stored is : first name,
last name, address, phone number, and birth date.The account is also assigned a
unique account number.*/
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
		do
		{
			cin >> newAcct[i].birthDay.year;
			while (newAcct[i].birthDay.year < 1 || newAcct[i].birthDay.year > 2023)
			{
				cout << "Invalid year! Please enter a valid year:";
				cin >> newAcct[i].birthDay.year;
				if (newAcct[i].birthDay.year > 2005)
				{
					cout << "Unfortunately, you are too young to open an account. Minimum age is 18 yrs";
					return;
				}
			}
		} while (newAcct[i].birthDay.year < 1 || newAcct[i].birthDay.year > 2023);//Validating user input for the year
		cout << "Month:";
		do
		{
			cin >> newAcct[i].birthDay.month;
			while (newAcct[i].birthDay.month < 1 || newAcct[i].birthDay.month > 12)
			{
				cout << "Invalid month.Please enter a valid month: ";
				cin >> newAcct[i].birthDay.month;
			}
		} while (newAcct[i].birthDay.month < 1 || newAcct[i].birthDay.month > 12);//Validating user input for the month
		cout << "Day:";
		if (newAcct[i].birthDay.year % 4 == 0 && newAcct[i].birthDay.month == 2)//Validating user input for feb. in a leap year
		{
			do
			{
				cin >> newAcct[i].birthDay.day;
				while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 29)
				{
					cout << "Invalid day.Please enter a valid day for february:";
					cin >> newAcct[i].birthDay.day;
				}
			} while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 29);
			cin.ignore();
		}
		else if (newAcct[i].birthDay.year % 4 != 0 && newAcct[i].birthDay.month == 2)//Validating user input for feb.
		{
			do
			{
				cin >> newAcct[i].birthDay.day;
				while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 28)
				{
					cout << "Invalid day.Please enter a valid day for february:";
					cin >> newAcct[i].birthDay.day;
				}
			} while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 28);
			cin.ignore();
		}
		else if (newAcct[i].birthDay.month == 4 || newAcct[i].birthDay.month == 6
			|| newAcct[i].birthDay.month == 9 || newAcct[i].birthDay.month == 11)//Validating user input for months ending at day 30
		{
			do
			{
				cin >> newAcct[i].birthDay.day;
				while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 30)
				{
					cout << "Invalid day.Please enter a valid day for this month:";
					cin >> newAcct[i].birthDay.day;
				}
			} while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 30);
			cin.ignore();
		}
		else //Validating user input for every other month
		{
			do
			{
				cin >> newAcct[i].birthDay.day;
				while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 31)
				{
					cout << "Invalid day.Please enter a valid day for this month:";
					cin >> newAcct[i].birthDay.day;
				}
			} while (newAcct[i].birthDay.day < 1 || newAcct[i].birthDay.day > 31);
			cin.ignore();
		}
		cout << "Your account number is:" << newAcct[i].accountNo;
		newAcct[i].accountNo++;//Increment the account number for the next customer
		newAcct[i].isOpen = true;//made the account open
}

/*Close an account. All the information stored about the particular customer is 
deleted. */
void CloseAcct(Account account[], int Number, int Total)
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

//this function allows the user to deposit money into their account
void Deposit(Account account[],int total,int Number,double amount)
{
	for (int i = 0; i < total; i++)
	{
		if (account[i].accountNo == Number && account[i].isOpen == true)
		{
			account[i].balance += amount;
			cout << "\n" << amount << " has been successfully deposited into your account.";
			cout << "\nCurrent balance:" << account[i].balance;
			return;
		}
    }
}

//This function allows the user to withdraw money from their account. They are not allowed to withdraw more than they possess
void Withdraw(Account account[], int total,int Number,double amount)
{
	for (int i = 0; i < total; i++)
	{
		if (account[i].accountNo == Number && account[i].isOpen == true)
		{
			do
			{
				while (account[i].balance < 0.1 && amount > 0.0)
				{
					cout << "\nInsufficient funds.";
					cout << "\nThe amount you can currently withdraw is " << account[i].balance;
					cout << "\nPlease enter a valid amount to withdraw:";
					cin >> amount;
				}
			} while (account[i].balance < 0.1 && amount > 0.0);//added verification of user input here, incase I forget it later
			account[i].balance -= amount;
			cout << "\n" << amount << " has been successfully withdrawn from your account.";
			cout << "Current balance:" << account[i].balance;
			return;
		}
	}
}

//this function allows the user to view their account info, including how much they have in the account
void AcctInfo(Account account[],int total,int Number)
{
	
	for (int i = 0; i < total; i++)
	{
		cout << "Account number at the beginning of the acct Info function" << account[i].accountNo;
		if (account[i].accountNo == Number && account[i].isOpen == true)
		{
			cout << "\nAccount Information for Account Number: " << account[i].accountNo;
			cout << "\nAccount Holder: " << account[i].firstName << " " << account[i].lastName;
			cout << "\nDate of Birth: " << account[i].birthDay.day << "/" << account[i].birthDay.month << "/" << account[i].birthDay.year;
			cout << "\nPhone Number: " << account[i].phoneNo;
			cout << "\nAddress: " << account[i].address << ", " << account[i].city << ", " << account[i].postCode;
			cout << "\nCurrent Balance: " << account[i].balance;
			return;
		}
	}
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
void Search(Account account[],int total,int Number)
{

}