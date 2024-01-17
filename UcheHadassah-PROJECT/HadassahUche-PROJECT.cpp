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

struct Date
{
    int day;
    int month;
    int year;
};
class BankAccount 
{
public:
    //constructor
    BankAccount();
    BankAccount(string firstName, string lastName, string address, string phoneNumber, Date birthDate);
    //Functions to perform operations on the account
    void deposit(double amount);
    void withdraw(double amount);
    void displayInfo() const;
    //Getter for account number
    int getAccountNumber() const;
    //Getter for account balance
    double getBalance() const
    {
        return balance;
    }
    //Getter for last name and phone number
    string getFirstName() const
    {
        return firstName;
    }
    string getLastName() const
    {
        return lastName;
    }
    string getPhoneNumber() const
    {
        return phoneNumber;
    }
    string getAddress() const
    {
        return address;
    }
    Date getBirthDate() const
    {
        return birthDate;
    }
private:
    // Member variables
    static int nextAccountNumber;
    int accountNumber;
    string firstName;
    string lastName;
    string address;
    string phoneNumber;
   Date birthDate;
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
void searchAndDisplay(const BankAccount[], int);
void saveToFile(const BankAccount [], int , const string& );
void readFromFile(BankAccount [], int& , const string& );

int main()
{
    BankAccount accounts[maxAccounts];
    int numOfAccounts = 0;

    char option;

    cout << "Welcome" << endl;
    cout << "Would you like to read an account from a file (y/n)? ";
    cin >> option;

    if (option == 'y' || option == 'Y') 
    {
        string fileName;
        cout << "Enter file name: ";
        cin >> fileName;

        readFromFile(accounts, numOfAccounts, fileName);
    }
    else 
    {
        cout << "Alright" << endl;
    }
    do {
        //Display menu options
        cout << "\n===== BANK APPLICATION MENU ====="<<endl;
        cout << "O <-> Open Account" << endl;
        cout << "C <-> Close Account" << endl;
        cout << "D <-> Deposit Money" << endl;
        cout << "W <-> Withdraw Money" << endl;
        cout << "A <-> Display Account Information" << endl;
        cout << "P <-> Print All Accounts" << endl;
        cout << "S <-> Search For Account" << endl;
        cout << "Q <-> Quit" << endl;
        cout << "Enter your choice:";
        cin >> option;
        switch (option) {
        case 'O':
        case 'o':
            openAccount(accounts, numOfAccounts);
            //save accounts to file after opening an account
            saveToFile(accounts, numOfAccounts, "accounts.txt");
            break;
        case 'C':
        case 'c':
            //Assuming the user knows the account number
            int accountNumberToClose;
            cout << "Enter the account number to close:";
            cin >> accountNumberToClose;
            closeAccount(accounts, numOfAccounts, accountNumberToClose);
            break;
        case 'D':
        case 'd':
            // Assuming the user knows the account number for deposit
            int accountNumberToDeposit;
            double depositAmount;
            cout << "Enter the account number to deposit into:";
            cin >> accountNumberToDeposit;
            cout << "Enter the amount you wish to deposit:";
            cin >> depositAmount;
            deposit(accounts, numOfAccounts, accountNumberToDeposit, depositAmount);
            //Save accounts after depositing money
            saveToFile(accounts, numOfAccounts, "accounts.txt");
            break;
        case 'W':
        case 'w':
            // Assuming the user knows the account number for withdrawal
            int accountNumberToWithdraw;
            double withdrawAmount;
            cout << "Enter the account number to withdraw from:";
            cin >> accountNumberToWithdraw;
            cout << "Enter the amount you wish to withdraw:";
            cin >> withdrawAmount;
            withdraw(accounts, numOfAccounts, accountNumberToWithdraw, withdrawAmount);
            //save accounts after depositing money
            saveToFile(accounts, numOfAccounts, "accounts.txt");
            break;
        case 'A':
        case 'a':
            // Assuming the user knows the account number for display
            int accountNumberToDisplay;
            cout << "Enter the account number to display: ";
            cin >> accountNumberToDisplay;
            displayAccountInfo(accounts, numOfAccounts, accountNumberToDisplay);
            break;
        case 'P':
        case 'p':
            printAllAccounts(accounts, numOfAccounts);
            break;
        case 'S':
        case 's':
            searchAndDisplay(accounts, numOfAccounts);
            break;
        case 'Q':
        case 'q':
            cout << "Thank you for your time ^^" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (option != 'q'&& option != 'Q');
	return 0;
}

BankAccount::BankAccount(){}

//Implementation of the BankAccount class functions
BankAccount::BankAccount(string firstName, string lastName, string address, string phoneNumber,Date birthDate)
    :accountNumber(nextAccountNumber++),firstName(firstName), lastName(lastName),
    address(address), phoneNumber(phoneNumber),birthDate(birthDate),balance(0.0){}
void BankAccount::deposit(double amount)
{
    balance += amount;
}
void BankAccount::withdraw(double amount)
{
    if (balance >= amount)
    {
        balance -= amount;
    }
    else
    {
        cout << "Insufficient Funds." << endl;
    }
}
void BankAccount::displayInfo() const
{
    cout << "Account Number: " << accountNumber << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Address: " << address << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Birth Date: " << birthDate.day <<"/"<< birthDate.month<<"/"<< birthDate.year << endl;
    cout << "Balance: $" << balance << endl;
}

//Implementation of the getter function
int BankAccount::getAccountNumber() const 
{
    return accountNumber;
}

//Implementation for the openAccount function
void openAccount(BankAccount accounts[], int& numOfAccounts)
{
    if (numOfAccounts < maxAccounts)
    {
        string firstName, lastName, address, phoneNumber;
        Date birthDate;
        cin.ignore();
        cout << "Enter your first name:";
        getline(cin,firstName);
        cout << "Enter your last name:";
        getline(cin, lastName);
        cout << "Enter your address:";
        getline(cin, address);
        cout << "Enter your phone number:";
        cin >> phoneNumber;
        cout << "Enter your birth date-"<< endl;
        cout << "Year:";
        do
        {
            cin >> birthDate.year;
            while (birthDate.year < 1924 || birthDate.year > 2024)
            {
                cout << "Invalid year! Please enter a valid year:";
                cin >> birthDate.year;
            }
        } while (birthDate.year < 1924 || birthDate.year > 2024);//Validating user input for the year
        if (birthDate.year > 2006)
        {
            cout << "Unfortunately, you are too young to open an account. Minimum age is 18 yrs"<< endl;
            return;
        }
        cout << "Month:";
        do
        {
            cin >> birthDate.month;
            while (birthDate.month < 1 || birthDate.month > 12)
            {
                cout << "Invalid month.Please enter a valid month: ";
                cin >> birthDate.month;
            }
        } while (birthDate.month < 1 || birthDate.month > 12);//Validating user input for the month
        cout << "Day:";
        if (birthDate.year % 4 == 0 && birthDate.month == 2)//Validating user input for feb. in a leap year
        {
            do
            {
                cin >> birthDate.day;
                while (birthDate.day < 1 || birthDate.day > 29)
                {
                    cout << "Invalid day.Please enter a valid day for february:";
                    cin >> birthDate.day;
                }
            } while (birthDate.day < 1 || birthDate.day > 29);
            cin.ignore();
        }
        else if (birthDate.year % 4 != 0 && birthDate.month == 2)//Validating user input for feb.
        {
            do
            {
                cin >> birthDate.day;
                while (birthDate.day < 1 || birthDate.day > 28)
                {
                    cout << "Invalid day.Please enter a valid day for february:";
                    cin >> birthDate.day;
                }
            } while (birthDate.day < 1 || birthDate.day > 28);
            cin.ignore();
        }
        else if (birthDate.month == 4 || birthDate.month == 6
            || birthDate.month == 9 || birthDate.month == 11)//Validating user input for months ending at day 30
        {
            do
            {
                cin >> birthDate.day;
                while (birthDate.day < 1 || birthDate.day > 30)
                {
                    cout << "Invalid day.Please enter a valid day for this month:";
                    cin >> birthDate.day;
                }
            } while (birthDate.day < 1 || birthDate.day > 30);
            cin.ignore();
        }
        else //Validating user input for every other month
        {
            do
            {
                cin >> birthDate.day;
                while (birthDate.day < 1 || birthDate.day > 31)
                {
                    cout << "Invalid day.Please enter a valid day for this month:";
                    cin >> birthDate.day;
                }
            } while (birthDate.day < 1 || birthDate.day > 31);
            cin.ignore();
        }
        accounts[numOfAccounts] = BankAccount(firstName, lastName, address, phoneNumber, birthDate);
        numOfAccounts++;
        cout << "\nYour account has been opened successfully. Account number: " << accounts[numOfAccounts - 1].getAccountNumber() << endl;
    }
    else
    {
        cout << "\nError: Maximum number of accounts reached." << endl;
    }
}

void closeAccount(BankAccount accounts[], int& numOfAccounts, int accountNumber)
{
    int index = -1;//Initialize to an invalid index
    for (int i = 0; i < numOfAccounts; i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber) 
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        //shift remaining elements to fill the gap
        for (int i = index; i < numOfAccounts - 1; i++)
        {
            accounts[i] = accounts[i + 1];
        }
        //decrement the number of accounts
        numOfAccounts--;
        cout << "Your account has been closed successfully." << endl;
    }
    else
    {
        cout << "Error: Account not found!" << endl;
    }
}

void deposit(BankAccount accounts[], int numOfAccounts, int accountNumber, double amount)
{
    int index = -1;//initialize to an invalid index
    //Find the index of the account with a given account number
    for (int i = 0; i < numOfAccounts; i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        //perform the deposit
        accounts[index].deposit(amount);
        cout << "Deposit successful. New balance: " << accounts[index].getBalance() << endl;
    }
    else
    {
        cout << "Error: Account not found!" << endl;
    }
}

void withdraw(BankAccount accounts[], int numOfAccounts, int accountNumber, double amount)
{
    int index = -1;//initialize to an invalid index
    //Find the index of the account with a given account number
    for (int i = 0; i < numOfAccounts; i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        //perform the withdrawal
        accounts[index].withdraw(amount);
        cout << "Withdrawal successful. New balance: " << accounts[index].getBalance() << endl;
    }
    else
    {
        cout << "Error: Account not found!" << endl;
    }
}

void displayAccountInfo(const BankAccount accounts[], int numOfAccounts, int accountNumber)
{
    int index = -1;  // Initialize to an invalid index

    // Find the index of the account with the given account number
    for (int i = 0; i < numOfAccounts; i++) 
    {
        if (accounts[i].getAccountNumber() == accountNumber) 
        {
            index = i;
            break;
        }
    }

    if (index != -1) 
    {
        // Display account information
        accounts[index].displayInfo();
    }
    else 
    {
        cout << "Error: Account not found." << endl;
    }
}

void printAllAccounts(const BankAccount accounts[], int numOfAccounts) 
{
    if (numOfAccounts > 0) 
    {
        cout << "All Accounts:" << endl;
        for (int i = 0; i < numOfAccounts; i++) 
        {
            cout<< "-------------------------" << endl;
            accounts[i].displayInfo();
        }
        cout << "-------------------------" << endl;
    }
    else {
        cout << "No accounts to display." << endl;
    }
}

void searchByLastName(const BankAccount accounts[], int numOfAccounts, const string& lastName)
{
    bool found = false;
    cout << "Search Results for Last Name '" << lastName << "':" << endl;
    for (int i = 0; i < numOfAccounts; i++) 
    {
        if (accounts[i].getLastName() == lastName) 
        {
            accounts[i].displayInfo();
            found = true;
        }
    }
    if (!found) 
    {
        cout << "No accounts found with the last name '" << lastName << "'." << endl;
    }
}

void searchByPhoneNumber(const BankAccount accounts[], int numOfAccounts, const string& phoneNumber)
{
    bool found = false;
    cout << "Search Results for Phone Number '" << phoneNumber << "':" << endl;
    for (int i = 0; i < numOfAccounts; i++)
    {
        if (accounts[i].getPhoneNumber() == phoneNumber)
        {
            accounts[i].displayInfo();
            found = true;
        }
    }
    if (!found)
    {
        cout << "No accounts found with the phone number '" << phoneNumber << "'." << endl;
    }
}

void searchAndDisplay(const BankAccount accounts[], int numOfAccounts)
{
    int choice;
    cout << "Search by:" << endl;
    cout << "1 <-> Last name" << endl;
    cout << "2 <-> Phone number" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        string searchLastName;
        cout << "Enter the last name to search:";
        cin >> searchLastName;
        searchByLastName(accounts, numOfAccounts, searchLastName);
        break;
    }
    case 2:
    {
        string searchPhoneNumber;
        cout << "Enter the phone number to search:";
        cin >> searchPhoneNumber;
        searchByPhoneNumber(accounts, numOfAccounts, searchPhoneNumber);
        break;
    }
    default:
        cout << "Invalid choice." << endl;
    }
}

void saveToFile(const BankAccount accounts[], int numOfAccounts, const std::string& filename)
{
    ofstream outFile(filename);
    if (outFile.is_open()) 
    {
        for (int i = 0; i < numOfAccounts; i++) 
        {
            outFile << accounts[i].getAccountNumber() << " "
                << accounts[i].getFirstName() << " "
                << accounts[i].getLastName() << " "
                << accounts[i].getAddress() << " "
                << accounts[i].getPhoneNumber() << " "
                << accounts[i].getBirthDate().day << " "
                << accounts[i].getBirthDate().month << " "
                << accounts[i].getBirthDate().year << " "
                << accounts[i].getBalance() << endl;
        }

        outFile.close();
        cout << "Accounts saved to file successfully." << endl;
    }
    else 
    {
        cout << "Error: Unable to open file for saving." << endl;
    }
}

void readFromFile(BankAccount accounts[], int& numOfAccounts, const string& filename)
{
    ifstream inFile(filename);
    if (inFile.is_open()) 
    {
        // Reset the number of accounts
        numOfAccounts = 0;

        while (inFile) 
        {
            // Read account details from file
            string firstName, lastName, address, phoneNumber;
            Date birthDate;
            double balance;

            inFile >> firstName >> lastName >> address >> phoneNumber >> birthDate.day >> birthDate.month >> birthDate.year >> balance;

            accounts[numOfAccounts] = BankAccount(firstName, lastName, address, phoneNumber, birthDate);
            accounts[numOfAccounts].deposit(balance);  // Initially deposit the balance
            numOfAccounts++;
        }

        inFile.close();
        cout << "Account info is read in." << endl;
    }
    else 
    {
        cout << "Error: Cannot read in file!" << endl;
    }
}