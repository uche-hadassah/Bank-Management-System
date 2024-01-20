/*
Name:Uche Hadassah 
ID:U221N0883
==BANK MANAGEMENT SYSTEM PROJECT==
This project is an implementation of a bank management system
*/
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
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
    //constructors
    BankAccount();
    BankAccount(string firstName, string lastName, string address, string phoneNumber, Date birthDate);

    //Functions to perform operations on the account
    void deposit(double amount);
    void withdraw(double amount);
    void displayInfo() const;

    //All the Getters
    int getAccountNumber() const;
    double getBalance() const;
    string getFirstName() const;
    string getLastName() const;
    string getPhoneNumber() const;
    string getAddress() const;
    Date getBirthDate() const;
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

        // Attempt to open the file
        ifstream inFile(fileName);

        // Keep prompting the user for a valid filename until the file is successfully opened
        while (!inFile.is_open()) 
        {
            cerr << "Error: Cannot read in file!" << endl;
            cout << "Enter file name again: ";
            cin >> fileName;
            inFile.open(fileName);
        }
        readFromFile(accounts, numOfAccounts, fileName);
    }
    else 
    {
        cout << "Proceeding to menu....." << endl;
    }
    do 
    {
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

        //get user choice
        cout << "Enter your choice:";
        cin >> option;

        // Validate user input
        while (cin.fail() || (option != 'O' && option != 'o' && option != 'C' && option != 'c'
            && option != 'D' && option != 'd' && option != 'W' && option != 'w'
            && option != 'A' && option != 'a' && option != 'P' && option != 'p'
            && option != 'S' && option != 's' && option != 'Q' && option != 'q')) 
        {
            cout << "Invalid choice. Please enter a valid option: ";
            cin.clear();// Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cin >> option;// Try reading again
        }
        switch (option) 
        {
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
            //Save accounts after depositing money
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
            cout << "Thank you for using the bank application" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option:" << endl;
        }
    } while (option != 'q'&& option != 'Q');
	return 0;
}


//Implementation of the BankAccount class functions
BankAccount::BankAccount() {}
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

//Implementation for the getter functions
int BankAccount::getAccountNumber() const 
{
    return accountNumber;
}
double BankAccount::getBalance() const
{
    return balance;
}
string BankAccount::getFirstName() const
{
    return firstName;
}
string BankAccount::getLastName() const
{
    return lastName;
}
string BankAccount::getPhoneNumber() const
{
    return phoneNumber;
}
string BankAccount::getAddress() const
{
    return address;
}
Date BankAccount::getBirthDate() const
{
    return birthDate;
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

//Implementation for the closeAccount function
void closeAccount(BankAccount accounts[], int& numOfAccounts, int accountNumber)
{
    int index = -1;//Initialize to an invalid index

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

//Implementation for the deposit function
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

//Implementation for the withdraw function
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

//implementation for the displayAccountInfo function
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

//Implementation for the printAllAccounts function. Prints them all according to account number
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
    else 
    {
        cout << "No accounts to display." << endl;
    }
}

//Implementation for the searchByLastName function
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

//Implementation for the searchByPhoneNumber function
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

//Implementation for the searchAndDisplay function
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

//Implementation for the saveToFile function
void saveToFile(const BankAccount accounts[], int numOfAccounts, const string& filename)
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
                << accounts[i].getBirthDate().year << " "
                << accounts[i].getBirthDate().month << " "
                << accounts[i].getBirthDate().day << " "
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

//Implementation for the readFromFile function
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