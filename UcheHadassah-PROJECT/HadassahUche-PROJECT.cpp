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
REQUIREMENTS
a) Your code has to be:
- well-structured (indention, etc)
- well-commented(at the top of the file, before each function, and for
“important” parts of the code)
- define variables, constants, etc following the programming style suggested
by the book
b) No global variables
c) Each operation of the application has to be handled by a separate function
d) All functions have to appear after main
e) Your program should be able to handle any user input. In case the user input is
wrong you should print an error message before displaying the menu again.
f) To store the customer information you can choose to use either a struct or a class.
To store all the accounts you can choose to use an array or a Vector. For the strings
you can use either a c-string or the string class. You are also free to use exception
handling.*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//Global constant
const int maxAccounts = 100;

class BankAccount 
{
public:
    //constructor
    BankAccount(string firstName, string lastName, string address, string phoneNumber, string birthDate);
    //Functions to perform operations on the account
    void deposit(double amount);
    void withdraw(double amount);
    void displayInfo();
    //Getter for account number
    int getAccountNumber() const;
private:
    // Member variables
    static int nextAccountNumber;
    int accountNumber;
    string firstName;
    string lastName;
    string address;
    string phoneNumber;
    string birthDate;
    double balance;
};

//Initializing the static member variable
int BankAccount::nextAccountNumber = 1;

//Function Prototypes
void openAccount(BankAccount[], int&);
void closeAccount(BankAccount[], int&, int);
void deposit(BankAccount[], int, int, double);
void withdraw(BankAccount[], int, int, double);
void displayAccountInfo(const BankAccount[], int, int);
void printAllAccounts(const BankAccount[], int);
void searchByLastName(const BankAccount [], int , const string& );
void searchByPhoneNumber(const BankAccount [], int , const string& );
void saveToFile(const BankAccount [], int , const string& );
void readFromFile(BankAccount [], int& , const string& );

int main()
{
    
	return 0;
}

//Implementation of the BankAccount class functions
BankAccount::BankAccount(string firstName, string lastName, string address, string phoneNumber,string birthDate)
    :accountNumber(nextAccountNumber++),firstName(firstName), lastName(lastName),
    address(address), phoneNumber(phoneNumber),birthDate(birthDate),balance(0.0){}
void BankAccount::deposit(double amount)
{
    balance += amount;
    cout << "Successful Deposit. New balance: " << balance << endl;
}
void BankAccount::withdraw(double amount)
{
    if (balance >= amount)
    {
        balance -= amount;
        cout << "Successful Withdrawal. New balance: " << balance << endl;
    }
    else
    {
        cout << "Insufficient Funds." << endl;
    }
}
void BankAccount::displayInfo() 
{
    cout << "Account Number: " << accountNumber << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Address: " << address << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Birth Date: " << birthDate << endl;
    cout << "Balance: " << balance << endl;
}

//Implementation of the getter function
int BankAccount::getAccountNumber() const 
{
    return accountNumber;
}
