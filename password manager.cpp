#include <iostream>
#include <fstream>
using namespace std;

class PasswordManager 
{
private:
    string username;
    string password;

public:
    void setData() 
	{
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }

    void saveToFile() 
	{
        ofstream outFile("passwords.txt", ios::app);
        if (outFile.is_open()) 
		{
            outFile << "Username: " << username << ", Password: " << password << endl;
            outFile.close();
            cout << "Data saved successfully!" << endl;
        } 
		else 
		{
            cout << "Error opening file!" << endl;
        }
    }

    void viewPasswords() 
	{
        string line;
        ifstream inFile("passwords.txt");
        if (inFile.is_open()) 
		{
            cout << "\nSaved Passwords:\n";
            while (getline(inFile, line)) 
			{
                cout << line << endl;
            }
            inFile.close();
        } 
		else 
		{
            cout << "No passwords found or file could not be opened." << endl;
        }
    }
};

int main() 
{
    PasswordManager pm;
    int choice;

    do 
	{
        cout << "\n---- Password Manager ----\n";
        cout << "1. Add New Password\n";
        cout << "2. View Saved Passwords\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                pm.setData();
                pm.saveToFile();
                break;
            case 2:
                pm.viewPasswords();
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } 
	while (choice != 3);

    return 0;
}