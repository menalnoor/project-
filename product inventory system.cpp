#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Product 
{
private:
    string productName;
    int productID;
    double productPrice;
    int* stockQuantity;
    // Static variable
    static int instanceCount;  

public:
    // Default constructor
    Product();

    // Parameterized constructor
    Product(string name, int id, double price, int stock);

    // Copy constructor
    Product(const Product& other);

    // Destructor
    ~Product();

    // Getter and Setter or member functions
    string getProductName() const;
    void setProductName(const string& name);

    int getProductID() const;
    void setProductID(int id);

    double getProductPrice() const;
    void setProductPrice(double price);

    int getStockQuantity() const;
    void setStockQuantity(int stock);

    //static method
    static void totalProducts();


    void inputProductDetails();

   
    void displayProductDetails() const;

   
    static int addStock (const Product& p1, const Product& p2);

   
    static void writeToFile (const Product* products, int count);

   
    static void readFromFile (Product* products, int& count);

  
    static int getInstanceCount();
};

// Initializing static variable
int Product::instanceCount = 0;

//default 
Product::Product() : productName("Unknown"), productID(0), productPrice(0.0), stockQuantity(new int(0)) {
    instanceCount++;
}

//paramiterized 
Product::Product(string name, int id, double price, int stock)
    : productName(name), productID(id), productPrice(price), stockQuantity(new int(stock)) {
    instanceCount++;
}

// Copy constructor
Product::Product(const Product& other)
    : productName(other.productName), productID(other.productID), productPrice(other.productPrice),
      stockQuantity(new int(*(other.stockQuantity))) 
	  {
    instanceCount++;
}

// Destructor
Product::~Product() 
{
    delete stockQuantity; 
    instanceCount--;
}

// Getter and Setter methods
string Product::getProductName() const 
{
    return productName;
}

void Product::setProductName(const string& name) 
{
    productName = name;
}

int Product::getProductID() const 
{
    return productID;
}

void Product::setProductID(int id) 
{
    productID = id;
}

double Product::getProductPrice() const 
{
    return productPrice;
}

void Product::setProductPrice(double price) 
{
    productPrice = price;
}

int Product::getStockQuantity() const 
{
    return *stockQuantity;
}

void Product::setStockQuantity(int stock) 
{
    *stockQuantity = stock;
}

void Product::displayProductDetails() const 
{
    cout << "Product Name: " << productName << endl;
    cout << "Product ID: " << productID << endl;
    cout << "Product Price: " << productPrice << " PKR" << endl;
    cout << "Stock Quantity: " << *stockQuantity << endl;
}
int main() 
{
  
    Product p1("Laptop", 221489, 199999, 50);
    Product p2("Headphones", 231543, 19999, 150);
    Product p3("Shoes", 231609, 7999, 100);

  
    p1.displayProductDetails();
    p2.displayProductDetails();
    p3.displayProductDetails();

 
    return 0;
}
