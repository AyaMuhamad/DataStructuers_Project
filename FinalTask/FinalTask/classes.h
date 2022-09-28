//*---------------Headers-----------------*

#include<bits/stdc++.h>

using namespace std;

//*---------------Global Functions-----------------*

void StartProgram();

void MainMenu();

bool CheckEmailValidation(string Email);

void Registration();

void Login();

void sellerMenu(); /// yet to complete

void customerMenu(); /// yet to complete

void credits();

//*---------------RateStruct-----------------*

struct Rate 
{
	int ID;

	double overAllRating;

	int numOfUsersRated;
};

//*---------------Classes-------------------*

class Seller
{
	int sellerID;

	string sellerName;

	string sellerEmail;

	string password;

	double rateOfSeller;

public:

	void setSellerID();

	void setSellerID(int selID);

	void setSellerName(string selName);

	void setSellerEmail(string selEmail);

	void setSellerPassword(string selPass);

	int getSellerID();

	string getSellerName();

	string getSellerEmail();

	string getSellerPassword();

	double getSellerRate();

	void setSellerRate();

	void setSellerRate(double rateOfSel);

	void SwitchSellerToCustomer();

	void addNewSeller();

	void loginAsSeller();

	void addNewProduct();

	bool CheckCustomerIsHere(string checkEmail);

	void rateOfNewSeller();

	void updateSellersRate(double CustomerRate, int SellerID);

	void displaySelfRate();
};

class Customer
{
	int customerID;

	string customerName;

	string customerEmail;

	string customerPassword;

	string customerAddress;

	string customerPhoneNumber;

public:

	void setcustomerID();

	void setcustomerID(int custID);

	void setCustomerName(string custName);

	void setCustomerEmail(string custEmail);

	void setCustomerPassword(string custPassword);

	void setCustomerAddress(string custAddress);

	void setCustomerPhoneNumber(string custPhoneNumber);

	int  getcustomerID();

	string getCustomerName();

	string getCustomerEmail();

	string getCustomerPassword();

	string getCustomerAddress();

	string getCustomerPhoneNumber();

	void switchCustomerToSeller();

	void addNewCustomer();

	void loginAsCustomer();

	void browseProductsByCategory(string categoryOfProduct);

	void browseProductsByName(string productName);

	void addProductToCart();

	bool CheckSellerIsHere(string checkEmail);

	void CheckBrowsing();

	void getHistoryOfCustomer();
};

class Product
{
	int productID;   

	string productName;

	string categoryOfProduct;

	double productQuantity;

	int productSellerID;

	double priceOfProduct;

	double rateOfProduct;

	int productCustomerID; 


public:

	void setProductID();

	void setProductID(int proID);

	void setProductName(string proName);

	void setcategoryOfProduct(string categoryOfPro);

	void setProductQuantity(double proQuantity);

	void setProductsellerID(int prosellerID);

	void setPriceOfProduct(double priceOfPro);

	void setProductRate(double rateOfPro);

	int getProductID();

	string getProductName();

	string getCategoryOfProduct();

	double getProductQuantity();

	int getProductSellerID();

	double getPriceOfProduct();

	double getProductRate();

	void rateOfNewProduct();

	void updateProductsRate(double CustomerRate, Product &prodObj);

	void setProductCustomerID(int prodCustomerID);

	int getProductCustomerID();

};

class CustomerCart
{
	list<Product>listOfProducts;

	double totalPrice = 0.0;

public:

	void setTotalPrice(double price, int amount);

	double getTotalPrice();

	void addProductToCart(int desiredQuantity, Product &prodObj);

	void displayTheTotalProducts();

	void deleteProductFromCart();

	void updateProductsOnMap();
	
	// special case : when we add a product to the cart we won't subtract anything from the original product quantity till the the confirm of buying the total cart.
						 // but if we added a product to the cart twice with a bigger total amount than the original product quantity, how would we handle this case ?
	
	/*
	first solution : we add 2 fun, both are modified funs from the fun "updateProducts" ...
					1- to subtract from the map after we add the product to the cart.
					2- to a reADD the quantity of the deleted product from the cart to the map again.
	
	second solution : it's 1 fun on the cart to update it every time we add a product to it ...
						which will check if there is a duplicate products (products that have the same name/ID)
						and add there amounts together then delete one of the duplicates and if the original product quantity
						was less than the total amount, it will refuse to add the same product for the second time.
	*/

};

template<class T>
class linkedList
{
	struct Node
	{

		T value;

		Node* next;

	};

	int count;

	Node* head;

	Node* tail;

public:

	linkedList(void);

	int Length();

	bool isEmpty();

	void InsertAt(int, T);

	void Append(T);

	T At(int);

	void DeleteAt(int);

	~linkedList(void);

};
