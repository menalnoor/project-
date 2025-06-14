#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount 
{
protected:
    string accountNumber;
    double balance;

public:
    BankAccount() : balance(0) {}
    BankAccount(string accNo, double bal) : accountNumber(accNo), balance(bal) {}

    virtual void deposit(double amount) 
	{
        balance += amount;
    }

    virtual void withdraw(double amount) 
	{
        if (balance >= amount)
            balance -= amount;
        else
            cout << "Insufficient funds.\n";
    }

    virtual void calculateInterest() = 0;

    virtual void display() const 
	{
        cout << "Account Number: " << accountNumber << "\nBalance: " << balance << endl;
    }

    virtual void saveToFile() = 0;

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount 
{
    double interestRate;

public:
    SavingsAccount(string accNo, double bal, double rate = 0.05)
        : BankAccount(accNo, bal), interestRate(rate) {}

    void calculateInterest() override 
	{
        double interest = balance * interestRate;
        balance += interest;
        cout << "Interest added: " << interest << endl;
    }

    void saveToFile() override 
	{
        ofstream fout("savings_accounts.txt", ios::app);
        fout << accountNumber << " " << balance << " " << interestRate << endl;
        fout.close();
    }

    void display() const override 
	{
        cout << "\n--- Savings Account ---\n";
        BankAccount::display();
        cout << "Interest Rate: " << interestRate * 100 << "%\n";
    }
};

class CurrentAccount : public BankAccount 
{
    double allowance;

public:
    CurrentAccount(string accNo, double bal, double allow = 1000)
        : BankAccount(accNo, bal), allowance(allow) {}

    void calculateInterest() override 
	{
        cout << "No interest for current accounts.\n";
    }

    void saveToFile() override 
	{
        ofstream fout("checking_accounts.txt", ios::app);
        fout << accountNumber << " " << balance << " " << allowance << endl;
        fout.close();
    }

    void display() const override 
	{
        cout << "\n--- Current Account ---\n";
        BankAccount::display();
        cout << "Allowance: " << allowance << endl;
    }
};

class FixedDepositAccount : public BankAccount 
{
    int maturityPeriod;
    bool matured;

public:
    FixedDepositAccount(string accNo, double bal, int maturity)
        : BankAccount(accNo, bal), maturityPeriod(maturity), matured(false) {}

    void markAsMatured() 
	{
        matured = true;
    }

    void calculateInterest() override 
	{
        double interest = balance * 0.05 * maturityPeriod;
        balance += interest;
        cout << "Fixed deposit interest added: " << interest << endl;
    }

    void withdraw(double amount) override 
	{
        if (matured) {
            BankAccount::withdraw(amount);
        } else {
            cout << "Cannot withdraw before maturity period.\n";
        }
    }

    void saveToFile() override 
	{
        ofstream fout("fixed_deposit_accounts.txt", ios::app);
        fout << accountNumber << " " << balance << " " << maturityPeriod << " " << matured << endl;
        fout.close();
    }

    void display() const override 
	{
        cout << "\n--- Fixed Deposit Account ---\n";
        BankAccount::display();
        cout << "Maturity Period: " << maturityPeriod << " months\n";
        cout << "Matured: " << (matured ? "Yes" : "No") << endl;
    }
};

void loadAccountsFromFile(BankAccount* accounts[], int& count) 
{
    ifstream fin;
    string accNo;
    double bal;
    double extra;
    int maturity;
    int matured;

    fin.open("savings_accounts.txt");
    while (fin >> accNo >> bal >> extra) 
	{
        accounts[count++] = new SavingsAccount(accNo, bal, extra);
    }
    fin.close();

    fin.open("checking_accounts.txt");
    while (fin >> accNo >> bal >> extra) 
	{
        accounts[count++] = new CurrentAccount(accNo, bal, extra);
    }
    fin.close();

    fin.open("fixed_deposit_accounts.txt");
    while (fin >> accNo >> bal >> maturity >> matured) 
	{
        FixedDepositAccount* acc = new FixedDepositAccount(accNo, bal, maturity);
        if (matured) acc->markAsMatured();
        accounts[count++] = acc;
    }
    fin.close();

    cout << count << " accounts loaded.\n";
}

void menu() 
{
    BankAccount* accounts[100];
    int count = 0;
    loadAccountsFromFile(accounts, count);

    int choice;
    do 
	{
        cout << "\n====== Online Banking Menu ======\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Calculate Interest\n";
        cout << "6. Mark FD Accounts as Matured\n";
        cout << "7. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) 
		{
            string accNo;
            double bal;
            cout << "Enter account number and balance: ";
            cin >> accNo >> bal;
            accounts[count] = new SavingsAccount(accNo, bal);
            accounts[count]->saveToFile();
            count++;
            cout << "Savings account created.\n";

        } 
		else if (choice == 2) 
		{
            string accNo;
            double bal;
            cout << "Enter account number and balance: ";
            cin >> accNo >> bal;
            accounts[count] = new CurrentAccount(accNo, bal);
            accounts[count]->saveToFile();
            count++;
            cout << "Current account created.\n";

        } 
		else if (choice == 3) 
		{
            string accNo;
            double bal;
            int period;
            cout << "Enter account number, balance, and maturity period (in months): ";
            cin >> accNo >> bal >> period;
            accounts[count] = new FixedDepositAccount(accNo, bal, period);
            accounts[count]->saveToFile();
            count++;
            cout << "Fixed Deposit account created.\n";

        } 
		else if (choice == 4) 
		{
            for (int i = 0; i < count; i++)
                accounts[i]->display();

        } else if (choice == 5) 
		{
            for (int i = 0; i < count; i++)
                accounts[i]->calculateInterest();

        } else if (choice == 6) 
		{
            for (int i = 0; i < count; i++) 
			{
                FixedDepositAccount* fd = dynamic_cast<FixedDepositAccount*>(accounts[i]);
                if (fd != nullptr) 
				{
                    fd->markAsMatured();
                    cout << "FD Account marked as matured.\n";
                }
            }
        }

    } while (choice != 7);

    for (int i = 0; i < count; i++)
        delete accounts[i];
}

int main() {
    menu();
    return 0;
}
