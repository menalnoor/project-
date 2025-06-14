#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CAPACITY = 10; 

class Address 
{
private:
    string street;
    string city;
    string state;

public:
    Address(const string &st = "", const string &ct = "", const string &stt = "")
        : street(st), city(ct), state(stt) {}

    void setAddress(const string &st, const string &ct, const string &stt) 
	{
        street = st;
        city = ct;
        state = stt;
    }

    void displayAddress() const 
	{
        cout << "Address: " << street << ", " << city << ", " << state << endl;
    }

    void saveToFile(ofstream &outFile) const 
	{
        outFile << street << endl << city << endl << state << endl;
    }

    void loadFromFile(ifstream &inFile) 
	{
        getline(inFile, street);
        getline(inFile, city);
        getline(inFile, state);
    }

    friend ostream &operator<<(ostream &out, const Address &address) 
	{
        out << "Address: " << address.street << ", " << address.city << ", " << address.state;
        return out;
    }
};

template <typename T>
class Person 
{
protected:
    string name;
    T age;  

public:
    Person(const string &n = "", T a = 0) : name(n), age(a) {}

    virtual void setPersonDetails(const string &n, T a) 
	{
        name = n;
        age = a;
    }

    virtual void displayPersonDetails() const 
	{
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    virtual ~Person() {}
};

// Chef Class (Inheritance)
class Chef : public Person<int> 
{
private:
    int chefID;

public:
    Chef(const string &n = "", int a = 0, int id = 0) : Person<int>(n, a), chefID(id) {}

    void setChefDetails(const string &n, int a, int id) 
	{
        setPersonDetails(n, a);
        chefID = id;
    }

    void displayPersonDetails() const override 
	{
        Person<int>::displayPersonDetails();
        cout << "Chef ID: " << chefID << endl;
    }

    void saveToFile(ofstream &outFile) const 
	{
        outFile << chefID << endl << name << endl << age << endl;
    }

    void loadFromFile(ifstream &inFile) 
	{
        inFile >> chefID;
        inFile.ignore();
        getline(inFile, name);
        inFile >> age;
    }

    virtual ~Chef() {}
};

template <typename PriceType, typename QuantityType>
class Dish 
{
private:
    int dishCode;
    string dishName;
    PriceType dishPrice;   
    QuantityType dishQuantity; 

public:
    Dish(int code = 0, const string &name = "", PriceType price = 0.0, QuantityType quantity = 0)
        : dishCode(code), dishName(name), dishPrice(price), dishQuantity(quantity) {}

    void setDishDetails(int code, const string &name, PriceType price, QuantityType quantity) 
	{
        dishCode = code;
        dishName = name;
        dishPrice = price;
        dishQuantity = quantity;
    }

    void displayDish() const 
	{
        cout << "Dish Code: " << dishCode << ", Name: " << dishName
             << ", Price: $" << dishPrice << ", Quantity: " << dishQuantity << endl;
    }

    void saveToFile(ofstream &outFile) const 
	{
        outFile << dishCode << endl << dishName << endl << dishPrice << endl << dishQuantity << endl;
    }

    void loadFromFile(ifstream &inFile) 
	{
        inFile >> dishCode;
        inFile.ignore();
        getline(inFile, dishName);
        inFile >> dishPrice >> dishQuantity;
    }

    int getDishCode() const { return dishCode; }

    friend ostream &operator<<(ostream &out, const Dish<PriceType, QuantityType> &dish) 
	{
        out << "Dish Code: " << dish.dishCode << ", Name: " << dish.dishName
            << ", Price: $" << dish.dishPrice << ", Quantity: " << dish.dishQuantity;
        return out;
    }
};

class Restaurant 
{
private:
    Address address;
    Chef chef;
    Dish<float, int> dishes[MAX_CAPACITY]; 
    int dishCount;

public:
    static int restaurantCount; 
    Restaurant() : dishCount(0) 
	{
        ++restaurantCount;
    }

    ~Restaurant() 
	{
        --restaurantCount;
    }

    void setRestaurantAddress(const string &st, const string &ct, const string &stt) 
	{
        address.setAddress(st, ct, stt);
    }

    void setChefDetails(const string &name, int age, int id) 
	{
        chef.setChefDetails(name, age, id);
    }

    void addDish() 
	{
        if (dishCount >= MAX_CAPACITY) 
		{
            cout << "Cannot add more dishes. Restaurant is at full capacity!" << endl;
            return;
        }

        int code, quantity;
        string name;
        float price;

        cout << "Enter Dish Code: ";
        cin >> code;
        cin.ignore();
        cout << "Enter Dish Name: ";
        getline(cin, name);
        cout << "Enter Dish Price: ";
        cin >> price;
        cout << "Enter Dish Quantity: ";
        cin >> quantity;

        dishes[dishCount].setDishDetails(code, name, price, quantity);
        dishCount++;
        cout << "Dish added successfully!" << endl;
    }

    void viewDishes() const 
	{
        if (dishCount == 0) 
		{
            cout << "No dishes available!" << endl;
            return;
        }

        for (int i = 0; i < dishCount; i++) 
		{
            cout << "Dish " << i + 1 << ": ";
            dishes[i].displayDish();
        }
    }

    void searchDish() const 
	{
        int code;
        cout << "Enter Dish Code to search: ";
        cin >> code;

        for (int i = 0; i < dishCount; i++) 
		{
            if (dishes[i].getDishCode() == code) 
			{
                dishes[i].displayDish();
                return;
            }
        }

        cout << "Dish not found!" << endl;
    }

    void updateDish() 
	{
        int code;
        cout << "Enter Dish Code to update: ";
        cin >> code;

        for (int i = 0; i < dishCount; i++) {
            if (dishes[i].getDishCode() == code) 
			{
                string name;
                float price;
                int quantity;

                cout << "Enter New Dish Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter New Dish Price: ";
                cin >> price;
                cout << "Enter New Dish Quantity: ";
                cin >> quantity;

                dishes[i].setDishDetails(code, name, price, quantity);
                cout << "Dish updated successfully!" << endl;
                return;
            }
        }

        cout << "Dish not found!" << endl;
    }

    void saveToFile() const 
	{
        ofstream outFile("RestaurantData.txt");
        if (!outFile) 
		{
            cout << "Error opening file for saving!" << endl;
            return;
        }

        address.saveToFile(outFile);

        chef.saveToFile(outFile);

        outFile << dishCount << endl;
        for (int i = 0; i < dishCount; i++) 
		{
            dishes[i].saveToFile(outFile);
        }

        outFile.close();
        cout << "Restaurant data saved successfully!" << endl;
    }

    void loadFromFile() {
        ifstream inFile("RestaurantData.txt");
        if (!inFile) {
            cout << "Error opening file for loading!" << endl;
            return;
        }

        // Load address
        address.loadFromFile(inFile);

        chef.loadFromFile(inFile);

        inFile >> dishCount;
        inFile.ignore();
        for (int i = 0; i < dishCount; i++) 
		{
            dishes[i].loadFromFile(inFile);
        }

        inFile.close();
        cout << "Restaurant data loaded successfully!" << endl;
    }
};

int Restaurant::restaurantCount = 0;

int main() 
{
    Restaurant res;
    int choice;

    do 
	{
        cout << "\nRestaurant Management System\n";
        cout << "1. Set Restaurant Address\n";
        cout << "2. Set Chef Details\n";
        cout << "3. Add Dish\n";
        cout << "4. View Dishes\n";
        cout << "5. Search Dish\n";
        cout << "6. Update Dish\n";
        cout << "7. Save Data\n";
        cout << "8. Load Data\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                {
                    string street, city, state;
                    cout << "Enter street: ";
                    cin.ignore();
                    getline(cin, street);
                    cout << "Enter city: ";
                    getline(cin, city);
                    cout << "Enter state: ";
                    getline(cin, state);
                    res.setRestaurantAddress(street, city, state);
                    break;
                }
            case 2:
                {
                    string name;
                    int age, id;
                    cout << "Enter chef name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter chef age: ";
                    cin >> age;
                    cout << "Enter chef ID: ";
                    cin >> id;
                    res.setChefDetails(name, age, id);
                    break;
                }
            case 3:
                res.addDish();
                break;
            case 4:
                res.viewDishes();
                break;
            case 5:
                res.searchDish();
                break;
            case 6:
                res.updateDish();
                break;
            case 7:
                res.saveToFile();
                break;
            case 8:
                res.loadFromFile();
                break;
            case 9:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } 
	while (choice != 9);

    return 0;
}

