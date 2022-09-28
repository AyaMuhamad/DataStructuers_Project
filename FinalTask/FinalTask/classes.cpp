#include "classes.h"

//*------------------------------------Global Objects and Structures----------------------------------------*

Seller sellerObj;

linkedList<Seller>sellerLinkedList;

//vector<string> sellerPassword;

Customer customerObj;

linkedList<Customer>customerLinkedList;

//vector<string> customerPassword;

Product productObj;

CustomerCart cartObj;

vector<Product> Vectors;

multimap <string, Product> sellerProducts;

//*---------------Sellers Rate-----------------*

vector<Rate> sellersRate;

//*---------------Products Rate-----------------*

vector<Rate> productsRate;


//*---------------History-----------------*

linkedList<Product>HistoryOfCustomer;


//*------------------------------------Global Functions----------------------------------------*


void StartProgram()
{
	//*------------------------------------Seller----------------------------------------*

	int sellerID;

	string sellerName, sellerEmail, sellerPassword;

	ifstream inSeller("Seller.txt");

	while (inSeller >> sellerID >> sellerName >> sellerEmail >> sellerPassword)
	{
		sellerObj.setSellerID(sellerID);

		sellerObj.setSellerName(sellerName);

		sellerObj.setSellerEmail(sellerEmail);

		sellerObj.setSellerPassword(sellerPassword);

		sellerLinkedList.Append(sellerObj);

	}

	inSeller.close();

	//*------------------------------------customer----------------------------------------*

	int customerID;

	string customerName, customerEmail, customerPassword, customerAddress, customerPhoneNumber;

	ifstream inCustomer("Customer.txt");

	while (inCustomer >> customerID >> customerName >> customerEmail >> customerPassword >> customerAddress >> customerPhoneNumber)
	{
		customerObj.setcustomerID(customerID);

		customerObj.setCustomerName(customerName);

		customerObj.setCustomerEmail(customerEmail);

		customerObj.setCustomerPassword(customerPassword);

		customerObj.setCustomerAddress(customerAddress);

		customerObj.setCustomerPhoneNumber(customerPhoneNumber);

		customerLinkedList.Append(customerObj);

	}

	inCustomer.close();

	//*-------------------------------------Seller Products---------------------------------------*

	int productID, productSellerID;

	string productName, categoryOfProduct;

	double productQuantity, priceOfProduct;


	ifstream inSellerProducts("SellerProducts.txt");

	while (inSellerProducts >> productID >> productName >> categoryOfProduct >> productQuantity >> productSellerID >> priceOfProduct)
	{

		productObj.setProductID(productID);

		productObj.setProductName(productName);

		productObj.setcategoryOfProduct(categoryOfProduct);

		productObj.setProductQuantity(productQuantity);

		productObj.setProductsellerID(productSellerID);

		productObj.setPriceOfProduct(priceOfProduct);

		sellerProducts.insert(pair<string, Product>(categoryOfProduct, productObj));

	}

	inSellerProducts.close();

	//*-------------------------------------Seller Rate---------------------------------------*

	//sellerObj.updateSellersRate();

	ifstream inSellersRate;

	inSellersRate.open("SellersRate.txt");

	Rate selRate;

	while (inSellersRate >> selRate.ID >> selRate.overAllRating >> selRate.numOfUsersRated)
	{
		sellersRate.push_back(selRate);
	}

	inSellersRate.close();

	//*-------------------------------------Product Rate---------------------------------------*

	//productObj.updateProductsRate();

	ifstream inProductsRate;

	inProductsRate.open("ProductsRate.txt");

	Rate prodRate;

	while (inProductsRate >> prodRate.ID >> prodRate.overAllRating >> prodRate.numOfUsersRated)
	{
		productsRate.push_back(prodRate);
	}

	inProductsRate.close();

	for (int i = 0; i < productsRate.size(); i++)
	{
		for (auto j = sellerProducts.begin(); j != sellerProducts.end(); j++)
		{
			if (productsRate[i].ID == j->second.getProductID())
			{
				j->second.setProductRate(productsRate[i].overAllRating);
			}
		}
	}

	//*-------------------------------------History---------------------------------------*

	int historyProductID, historyProductSellerID, historyProductCustomerID;
	
	string historyProductName, historyCategoryOfProduct;
	
	double historyPriceOfProduct, historyRateOfProduct, historyProductQuantity;

	ifstream inCustomerProduct("CustomerProducts.txt");

	while (inCustomerProduct >> historyProductID >> historyProductName >> historyCategoryOfProduct >> historyProductQuantity >> historyProductSellerID >> historyPriceOfProduct >> historyRateOfProduct >> historyProductCustomerID)
	{

		productObj.setProductID(historyProductID);

		productObj.setProductName(historyProductName);

		productObj.setcategoryOfProduct(historyCategoryOfProduct);

		productObj.setProductQuantity(historyProductQuantity);

		productObj.setProductsellerID(historyProductSellerID);

		productObj.setPriceOfProduct(historyPriceOfProduct);

		productObj.setProductRate(historyRateOfProduct);

		productObj.setProductCustomerID(historyProductCustomerID);

		HistoryOfCustomer.Append(productObj);

	}

	inCustomerProduct.close();

}

void MainMenu() {

	cout << "Press ( 1 ) to Register\n";

	cout << "Press ( 2 ) to Login\n";

	cout << "Press ( 3 ) to show credits\n";

	int choice;

	cin >> choice;

	system("CLS");

	if (choice == 1)
		Registration();
	else if (choice == 2)
		Login();
	else if (choice == 3)
		credits();
	else
	{
		cout << "Enter valid number !\n";
		MainMenu();
	}
}

bool CheckEmailValidation(string Email)
{
	int counterAt = 0, counterDot = 0;

	for (int i = 0; i < Email.length(); i++)
	{
		if (Email[i] == '@')
		{
			counterAt++;
		}
		else if (Email[i] == '.')
		{
			counterDot++;
		}
	}

	if (counterAt == 1 && counterDot == 1)
		return true;
	else
		return false;
}

void Registration() {

	cout << "Press ( 1 ) to register as a seller\n";

	cout << "Press ( 2 ) to register as a customer\n";

	int choice;

	cin >> choice;

	system("CLS");

	if (choice == 1)
		sellerObj.addNewSeller();
	else if (choice == 2)
		customerObj.addNewCustomer();
	else
	{
		cout << "Enter valid number !\n";
		Registration();
	}

	Login();
}

void Login() {

	cout << "Press ( 1 ) to login as a seller\n";

	cout << "Press ( 2 ) to login as a customer\n";

	int choice;

	cin >> choice;

	system("CLS");

	if (choice == 1)
		sellerObj.loginAsSeller();
	else if (choice == 2)
		customerObj.loginAsCustomer();
	else
	{
		cout << "Enter valid number !\n";
		Login();
	}

}

void sellerMenu() {

	cout << "\nPress ( 1 ) to add products\n";

	cout << "Press ( 2 ) to switch from seller to customer\n";

	cout << "Press ( 3 ) to display self rate.\n";

	cout << "Press ( 4 ) to logout\n";

	int choice;

	cin >> choice;

	system("CLS");

	if (choice == 1)
		sellerObj.addNewProduct();
	else if (choice == 2)
		sellerObj.SwitchSellerToCustomer();
	else if (choice == 3)
		sellerObj.displaySelfRate();
	else if (choice == 4)
		MainMenu();
	else
	{
		cout << "Enter valid number !\n";
		sellerMenu();
	}
}

void customerMenu() {

	cout << "Press ( 1 ) to switch from customer to seller\n";

	cout << "Press ( 2 ) to browse products\n";

	cout << "Press ( 3 ) to display your product cart\n";

	cout << "press ( 4 ) to display history of your cart\n";

	cout << "Press ( 5 ) to logout\n";


	int choice;

	cin >> choice;

	system("CLS");

	if (choice == 1)
		customerObj.switchCustomerToSeller();
	else if (choice == 2)
		customerObj.CheckBrowsing();
	else if (choice == 3)
		cartObj.displayTheTotalProducts();
	else if (choice == 4)
		customerObj.getHistoryOfCustomer();
	else if (choice == 5)
		MainMenu();
	else
	{
		cout << "Enter valid number !\n";
		sellerMenu();
	}

}

void credits()
{
	cout << "1- Ahmed Nasr Mohamed.\n";

	cout << "2- Assem Mosa Badr.\n";

	cout << "3- Abdullah Halawany.\n";

	cout << "4- Aya Mohammed.\n";

	cout << "5- Abdelrahman Mousa.\n";

	cout << "6- Ahmed Hany Ibrahim.\n\n";

	MainMenu();
}

/*---------------------SellerClass---------------------*/

void Seller::setSellerID()
{
	srand(sellerLinkedList.Length());
	sellerID = rand() % 10000;
}

void Seller::setSellerID(int selID)
{
	sellerID = selID;
}

void Seller::setSellerPassword(string selPass)
{
	password = selPass;
}

void Seller::setSellerName(string selName)
{
	sellerName = selName;
}

void Seller::setSellerEmail(string selEmail)
{
	sellerEmail = selEmail;
}

void Seller::setSellerRate()
{

}

void Seller::setSellerRate(double rateOfSel)
{
	rateOfSeller = rateOfSel;
}

int Seller::getSellerID()
{
	return sellerID;
}

string Seller::getSellerName()
{
	return sellerName;
}

string Seller::getSellerEmail()
{
	return sellerEmail;
}

string Seller::getSellerPassword()
{
	return password;
}

double Seller::getSellerRate()
{
	if (rateOfSeller >= 0 && rateOfSeller <= 5)
		return rateOfSeller;
	else
		return 0;
}

void Seller::SwitchSellerToCustomer()
{
	if (CheckCustomerIsHere(sellerObj.getSellerEmail()))
	{
		customerMenu();
	}
	else
	{
		string Address, phoneNumber;

		customerObj.setcustomerID(sellerObj.getSellerID());

		customerObj.setCustomerName(sellerObj.getSellerName());

		customerObj.setCustomerEmail(sellerObj.getSellerEmail());

		cout << "Enter your Address : ";

		cin >> Address;

		customerObj.setCustomerAddress(Address);

		cout << "Enter your  Phone Number: ";

		cin >> phoneNumber;

		customerObj.setCustomerPhoneNumber(phoneNumber);

		customerLinkedList.Append(customerObj);

		system("CLS");

		customerMenu();
	}
}

void Seller::addNewSeller()
{
	
	string selName, selEmail, selPass;

	cout << "Enter Seller Name :  ";

	cin >> selName;

	cout << "Enter Seller Email :  ";

	while (true)
	{
		cin >> selEmail;

		if (CheckEmailValidation(selEmail))
		{
			break;
		}
		else
		{
			cout << "Please Enter valid Email as *****@gmail.com\n";
		}
	}

	cout << "Enter Seller Password :  ";

	while (true)
	{
		cin >> selPass;

		if (selPass.length() >= 4)
		{
			cout << "Registration Successfully ....!\n";

			break;
		}
		else
		{
			cout << "Invalid password, The password must be atleast 4 characters or numbers :\n";
		}
	}

	sellerObj.setSellerID();

	sellerObj.setSellerName(selName);

	sellerObj.setSellerEmail(selEmail);

	sellerObj.setSellerPassword(selPass);

	fstream outSeller("Seller.txt", ios::app);

	outSeller << sellerObj.getSellerID() << " " << selName << " " << selEmail << " " << selPass << endl;

	outSeller.close();

	sellerLinkedList.Append(sellerObj);

	rateOfNewSeller();

}

void Seller::loginAsSeller()
{
	string enteredEmail, enteredPassword;

	int loginCounter = 0;

	checkPoint:

	cout << "Enter your Email : ";

	cin >> enteredEmail;

	while (!CheckEmailValidation(enteredEmail))
	{
		cout << "Please Enter valid Email as *****@gmail.com OR Register now ....!\n";

		cout << "Press 1 to try another Email.\n Press 2 to return to Home Page.\n";

		int choice;

		cin >> choice;

		if (choice == 1)
			loginAsSeller();
		else if (choice == 2)
			MainMenu();
		else
		{
			cout << "Enter Valid Choice !!\n";
		}
	}

	bool sellerExistence = false;

	bool password = false;

	cout << "Enter your Password : ";

	cin >> enteredPassword;

	for (int i = 0; i < sellerLinkedList.Length(); i++)
	{
		sellerObj = sellerLinkedList.At(i);

		if (sellerObj.getSellerEmail() == enteredEmail)
		{
			sellerExistence = true;
			
			for (int j = 0; j < sellerLinkedList.Length(); j++) // if we made the password on a separate file
			{
				if (sellerObj.getSellerPassword() == enteredPassword)
				{
					password = true;

					break;
				}
			}

			break; // case he didn't find the password, i don't want more iterations for the sellerEmail
		}
	}
	if (sellerExistence && password)
	{
		cout << "\nLogin Successfuly ...!\n" << "Hello " << sellerObj.getSellerName() << " !\n\n";

		sellerMenu();
	}
	else
	{
		int choice;

		cout << "***** The Email you've entered is isn't registered or the password isn't correct, Please enter a registered Email with correct password or Register now ! *****\n\n";

		while (loginCounter < 2)
		{
			loginCounter++;

			cout << "Press ( 1 ) to Try another Email\n";

			cout << "Press ( 2 ) to Register\n";

			cout << "Press ( 3 ) to Go back to the main menu\n";

			cin >> choice;

			if (choice == 1)
				goto checkPoint;
			else if (choice == 2)
				Registration();
			else if (choice == 3)
				MainMenu();
			else
			{
				system("CLR");

				cout << "Enter valid number !\n\n";

				loginCounter--;
			}

		}

		cout << "Your login attempts have reached their max, try again later\n OR if u don't have an account you can register now.\n";

		cout << "Press ( 1 ) to Register now\n";

		cout << "Press ( 2 ) to go back to the main menu\n";

		cin >> choice;

		if (choice == 1)
			Registration();
		else if (choice == 2)
			MainMenu();
		else
		{
			cout << "Enter valid number !\n";
		}
	}
}

void Seller::addNewProduct()
{
	Product p;

	cout << "You can add a product to one of the below Categors :\n 1. clothes\n 2. fruits\n 3. vegetables\n 4. electric machines\n 5. others\n\n";

	string productName, categoryOfProduct;

	double productQuantity, priceOfProduct;

	cout << "Enter Name Of Product :\n"; cin >> productName;

	cout << "Enter Quantity Of Product :\n"; cin >> productQuantity;

	while (productQuantity <= 0)
	{
		cout << "Invalid Quantity ... Please enter quantity above 0\n";
		cin >> productQuantity;
	}

	cout << "Enter Price Of Product Per Unit :\n"; cin >> priceOfProduct;

	cout << "Enter Category Of Product :\n"; cin >> categoryOfProduct;
		
	while (true)
	{

		if (categoryOfProduct == "clothes")
		{
			sellerProducts.insert(pair<string, Product>("clothes", p));
			break;
		}
		else if (categoryOfProduct == "fruits")
		{
			sellerProducts.insert(pair<string, Product>("fruits", p));
			break;
		}
		else if (categoryOfProduct == "vegetables")
		{
			sellerProducts.insert(pair<string, Product>("vegetables", p));
			break;
		}
		else if (categoryOfProduct == "elactric machines")
		{
			sellerProducts.insert(pair<string, Product>("elactric machines", p));
			break;
		}
		else if (categoryOfProduct == "others")
		{
			sellerProducts.insert(pair<string, Product>("others", p));
			break;
		}
		else
		{
			cout << "Invalid Category , Pleass enter valid category...!\n";
			cin >> categoryOfProduct;

		}
	}

	p.setProductID();

	p.setProductName(productName);

	p.setProductQuantity(productQuantity);

	p.setcategoryOfProduct(categoryOfProduct);

	p.setPriceOfProduct(priceOfProduct);

	p.setProductsellerID(sellerObj.getSellerID());

	p.rateOfNewProduct();

	fstream outSellerProducts("SellerProducts.txt", ios::app);

	outSellerProducts << p.getProductID() << " " << productName << " " << categoryOfProduct << " " << productQuantity << " " << p.getProductSellerID() << " " << priceOfProduct << endl;

	outSellerProducts.close();

	cout << "\n***** Added Succesfully ! *****";

	sellerMenu();
}

bool Seller::CheckCustomerIsHere(string checkEmail)
{
	Customer customerTemp;

	for (int i = 0; i < customerLinkedList.Length(); i++)
	{
		customerTemp = customerLinkedList.At(i);

		if (customerTemp.getCustomerEmail() == checkEmail)
		{
			return true;
		}
	}

	return false;
}

void Seller::rateOfNewSeller()
{
	Rate selRate{ sellerID,0,0 };

	sellersRate.push_back(selRate);
}

void Seller::updateSellersRate(double CustomerRate, int SellerID)
{

	//	newRate = ((Overall Rating * Total Rating) + new Rating) / (Total Rating + 1)

	for (auto i = sellersRate.begin(); i != sellersRate.end(); i++)
	{
		if (SellerID == i->ID)
		{
			i->overAllRating = ((i->overAllRating * i->numOfUsersRated) + CustomerRate) / (i->numOfUsersRated + 1);

			setSellerRate(i->overAllRating);

			i->numOfUsersRated++;
		}
	}

	ofstream fileObj;

	fileObj.open("SellersRate.txt", ios::trunc);

	if (fileObj.is_open()) {

		for (auto i = sellersRate.begin(); i != sellersRate.end(); i++)
		{
			fileObj << i->ID << " " << i->overAllRating << " " << i->numOfUsersRated << endl;
		}
	}

	fileObj.close();
}

void Seller::displaySelfRate()
{
	for (auto i = sellersRate.begin(); i != sellersRate.end(); i++)
	{
		if (sellerObj.getSellerID() == i->ID)
		{
			cout << "\n\n\t\t||  My rate is : " << i->overAllRating << "  ||\n\n";
		}
	}

	customerMenu();
}

/*---------------------CustomerClass---------------------*/

void Customer::setcustomerID()
{
	srand(customerLinkedList.Length());
	customerID = rand() % 99999;
}

void Customer::setcustomerID(int custID)
{
	customerID = custID;
}

void Customer::setCustomerName(string custName)
{
	customerName = custName;
}

void Customer::setCustomerEmail(string custEmail)
{
	customerEmail = custEmail;
}

void Customer::setCustomerPassword(string custPassword)
{
	customerPassword = custPassword;
}

void Customer::setCustomerAddress(string custAddress)
{
	customerAddress = custAddress;
}

void Customer::setCustomerPhoneNumber(string custPhoneNumber)
{
	customerPhoneNumber = custPhoneNumber;
}

int Customer::getcustomerID()
{
	return customerID;
}

string Customer::getCustomerName()
{
	return customerName;
}

string Customer::getCustomerEmail()
{
	return customerEmail;
}

string Customer::getCustomerPassword()
{
	return customerPassword;
}

string Customer::getCustomerAddress()
{
	return customerAddress;
}

string Customer::getCustomerPhoneNumber()
{
	return customerPhoneNumber;
}

void Customer::switchCustomerToSeller()
{
	if (CheckSellerIsHere(customerObj.getCustomerEmail()))
	{
		sellerMenu();
	}
	else
	{
		sellerObj.setSellerID(customerObj.getcustomerID()); /// we need overloading function for setSellerID :))))).

		sellerObj.setSellerName(customerObj.getCustomerName());

		sellerObj.setSellerEmail(customerObj.getCustomerEmail());

		sellerLinkedList.Append(sellerObj);

		sellerMenu();
	}
}

void Customer::addNewCustomer()
{

	string customerName, customerEmail, customerPassword, customerAddress, customerPhoneNumber;

	cout << "Enter Customer Name :  ";

	cin >> customerName;

	cout << "Enter Customer Email :  ";

	while (true)
	{
		cin >> customerEmail;

		if (CheckEmailValidation(customerEmail))
			break;
		else
		{
			cout << "Please Enter valid Email as *****@gmail.com" << endl;
		}
	}

	cout << "Enter Customer Password :  ";

	while (true)
	{
		cin >> customerPassword;

		if (customerPassword.length() >= 4)
			break;
		else
		{
			cout << "Invalid password, The password must be atleast 4 characters or numbers :\n";
		}
	}

	cout << "Enter Customer Address :  ";

	cin >> customerAddress;

	cout << "Enter Customer Phone Number : ";

	cin >> customerPhoneNumber;


	cout << "\nRegistration Successfully ....!\n\n";


	customerObj.setcustomerID();

	customerObj.setCustomerName(customerName);

	customerObj.setCustomerEmail(customerEmail);

	customerObj.setCustomerPassword(customerPassword);

	customerObj.setCustomerAddress(customerAddress);

	customerObj.setCustomerPhoneNumber(customerPhoneNumber);

	fstream outCustomer("Customer.txt", ios::app);

	outCustomer << customerObj.getcustomerID() << " " << customerName << " " << customerEmail << " " << customerPassword << " " << customerAddress << " " << customerPhoneNumber << endl;

	outCustomer.close();

	customerLinkedList.Append(customerObj);

}

void Customer::loginAsCustomer()
{
	string enteredEmail, enteredPassword;

	int loginCounter = 0;

	checkpoint:

	cout << "Enter your Email : ";

	cin >> enteredEmail;

	while(!CheckEmailValidation(enteredEmail))
	{
		cout << "Please Enter valid Email as *****@gmail.com OR Register now ....!\n";

		cout << " Press 1 to try another Email.\n Press 2 to return to Home Page.\n";

		int choice;

		cin >> choice;

		if (choice == 1)
			loginAsCustomer();
		else if (choice == 2)
			MainMenu();
		else
		{
			cout << "Enter Valid Choice !!\n";
		}
	}
	
	bool customerExistence = false;

	bool password = false;

	cout << "Enter your Password : ";

	cin >> enteredPassword;

	for (int i = 0; i < customerLinkedList.Length(); i++)
	{
		customerObj = customerLinkedList.At(i);

		if (customerObj.getCustomerEmail() == enteredEmail)
		{
			customerExistence = true;

			for (int j = 0; j < customerLinkedList.Length(); j++) // if we made the password on a separate file
			{
				if (customerObj.getCustomerPassword() == enteredPassword)
				{
					password = true;

					break;
				}
			}

			break; // case he didn't find the password, i don't want more iterations for the customerEmail
		}
	}
	if (customerExistence && password)
	{
		cout << "\nLogin Successfuly ...!\n" << "Hello " << customerObj.getCustomerName() << " !\n\n";

		customerMenu();
	}
	else
	{
		int choice;

		cout << "***** The Email you've entered is isn't registered or the password isn't correct, Please enter a registered Email with correct password or Register now ! *****\n";

		while (loginCounter < 2)
		{
			loginCounter++;

			cout << "\nPress ( 1 ) to Try another Email\n";

			cout << "Press ( 2 ) to Register\n";

			cout << "Press ( 3 ) to Go back to the main menu\n";

			cin >> choice;

			if (choice == 1)
				goto checkpoint;
			else if (choice == 2)
				Registration();
			else if (choice == 3)
				MainMenu();
			else
			{
				system("CLR");

				cout << "Enter valid number !\n\n";

				loginCounter--;
			}

		}

		cout << "Your login attempts have reached their max, try again later\n OR if u don't have an account you can register now.\n\n";

		cout << "Press ( 1 ) to Register now\n";

		cout << "Press ( 2 ) to go back to the main menu\n";

		cin >> choice;

		if (choice == 1)
			Registration();
		else if (choice == 2)
			MainMenu();
		else
		{
			cout << "Enter valid number !\n";
		}
	}
}

void Customer::browseProductsByCategory(string categoryOfProduct)
{
	bool productExistence = false;

	multimap<string, Product> tempMap;

	sort(productsRate.begin(), productsRate.end(), [](const auto& i, const auto& j) { return i.overAllRating > j.overAllRating; });

	cout << "\nFor The Catgory ( " << categoryOfProduct << " )\n\n";

	for (auto i = sellerProducts.begin(); i != sellerProducts.end(); i++)
	{
		if (i->first == categoryOfProduct)
		{
			productExistence = true;

			tempMap.insert(pair<string,Product>(i->first,i->second));
		}
	}

	for (int i = 0; i < productsRate.size(); i++)
	{
		for (auto j = tempMap.begin(); j != tempMap.end(); j++)
		{
			if (j->second.getProductID() == productsRate[i].ID)
			{
				if (j->second.getProductQuantity() == 0)
					continue;

				cout << "\nthe product Name Is: " << j->second.getProductName() << "\nThe Product ID Is : " << j->second.getProductID() << "\nThe Available Quantity is : " << j->second.getProductQuantity() << "\nThe Product Price Is : " << j->second.getPriceOfProduct() << "\nThe Product Rate is : " << j->second.getProductRate() << "\n\n";
			}
		}
	}

	int choice;

	while (true)
	{
		if (!productExistence)
		{
			cout << "\n\n||||| There's no products in this category yet. |||||\n\n"; // this message is repeated when an Invalid number is entered

			cout << "Press 1 to keep browsing for products.\nPress 2 to return to the Home Page\n\n";

			cin >> choice;

			system("CLS");

			if (choice == 1)
				CheckBrowsing();
			else if (choice == 2)
				customerMenu();
			else
				cout << "enter valid number...!\n\n";
		}
		else
		{
			cout << "Press 1 to add this product to your cart.\nPress 2 to keep browsing for products.\nPress 3 to return to the Home Page\n\n"; // this message is repeated when an Invalid number is entered

			cin >> choice;

			if (choice == 1)
				addProductToCart();
			else if (choice == 2)
				CheckBrowsing();
			else if (choice == 3)
				customerMenu();
			else
				cout << "enter valid number...!\n\n";
		}
	}
}

void Customer::browseProductsByName(string productName)
{

	for (auto i = sellerProducts.begin(); i != sellerProducts.end(); i++)
	{
		if (i->second.getProductName() == productName)
		{
			if (i->second.getProductQuantity() == 0) /// 1st solution
				continue;
			/*
				else if(i->second.getProductQuantity() == 0)   // 2nd solution
				{
					cout << " Out of Stock ";	
				}
			*/

			cout << "\n\nFor the product Name : " << i->second.getProductName() << "\nThe Product ID Is : " << i->second.getProductID() << "\nThe Product Price Is : " << i->second.getPriceOfProduct()<< "\nThe Product Category Is : " << i->first << "\nThe Available Quantity is : " << i->second.getProductQuantity() << "\nThe Rate is : " << i->second.getProductRate() << "\n\n";
		}
	}

	int choice;

	while (true)
	{
		cout << "Press 1 to add this product to your cart.\nPress 2 to keep browsing for products.\nPress 3 to return to the Home Page\n\n";

		cin >> choice;

		if (choice == 1)
			addProductToCart();
		else if (choice == 2)
			CheckBrowsing();
		else if (choice == 3)
			customerMenu();
		else
			cout << "enter valid number...!\n\n";
	}

}

void Customer::addProductToCart()
{
	int num;

	bool exist = false;

	cout << " -----Enter the product ID that you want to add to cart---- \n";

	cin >> num;

	Product *productTemp = new Product;

	for (auto i = sellerProducts.begin(); i != sellerProducts.end(); i++)
	{
		if (i->second.getProductID() == num)
		{
			exist = true;

			productTemp = &i->second;

			break;
		}
	}

	double amount = 0;

	if (exist)
	{
		cout << "-----Yes Exist----\n";

		cout << "Enter Amount that you want to Buy : ";

		cin >> amount;

		cartObj.addProductToCart(amount, *productTemp);
	}
	else
	{
		cout << "----NOT FOUND-----\n";

		cout << "Please enter valid ID...!\n ";

		delete productTemp;

		addProductToCart();
	}
}

bool Customer::CheckSellerIsHere(string checkEmail)
{
	for (int i = 0; i < sellerLinkedList.Length(); i++)
	{
		sellerObj = sellerLinkedList.At(i);

		if (sellerObj.getSellerEmail() == checkEmail)
		{
			return true;
		}
	}
	return false;
}

void Customer::CheckBrowsing()
{

	system("CLS");

	cout << "Press ( 1 ) to Browse Products By it's Category\n";

	cout << "Press ( 2 ) to Browse Products By it's Name\n";

	cout << "Press ( 3 ) to Display All products in your cart\n";

	string name;

	int number;

	cin >> number;

	switch (number)
	{
	case 1:

		cout << "Enter catrgory of product that you want to search : ";

		cin >> name;

		browseProductsByCategory(name);

		break;

	case 2:

		cout << "Enter name of product that you want to search : ";

		cin >> name;

		browseProductsByName(name);

		break;
	case 3:

		cartObj.displayTheTotalProducts();

		break;

	default:

		cout << "WRONG CHOICE :(\n";

		CheckBrowsing();
	}
}

void Customer::getHistoryOfCustomer()
{
	Product tempProduct;

	bool history = false;

	int historyCounter = 0;

	for (int i = 0; i < HistoryOfCustomer.Length(); i++)
	{
		tempProduct = HistoryOfCustomer.At(i);

		if (tempProduct.getProductCustomerID() == customerObj.getcustomerID())
		{
			historyCounter++;

			if (historyCounter == 1)
			{
				cout << "\t\t\t The history products you have bought before \n\n";

				cout << "\n The product Name \t The Product ID \t The Product Price \t The Product Category  \t The Quantity" << "\n\n";
			}
			history = true;

			cout << "\t" << tempProduct.getProductName() << "\t\t\t" << tempProduct.getProductID() << "\t\t\t" << tempProduct.getPriceOfProduct() << "\t\t\t" << tempProduct.getCategoryOfProduct() << "\t\t\t" << tempProduct.getProductQuantity() << endl;
		}
	}

	if (!history)
		cout << "\n\nYou have no history to be shown.\n\n";
	else
		cout << "\n\n";

	customerMenu();
}

/*---------------------ProductClass---------------------*/


void Product::setProductID()
{
	srand(sellerProducts.size()); // Product linked list size.

	productID = rand() % 10000;
}

void Product::setProductID(int proID)
{
	productID = proID;
}

void Product::setProductName(string proName)
{
	productName = proName;
}

void Product::setcategoryOfProduct(string categoeyOfPro)
{
	categoryOfProduct = categoeyOfPro;
}

void Product::setProductQuantity(double proQuantity)
{
	productQuantity = proQuantity;
}

void Product::setProductsellerID(int prosellerID)
{
	productSellerID = prosellerID;
}

void Product::setPriceOfProduct(double priceOfPro)
{
	priceOfProduct = priceOfPro;
}

void Product::setProductRate(double rateOfPro)
{
	rateOfProduct = rateOfPro;
}

int Product::getProductID()
{
	return productID;
}

string Product::getProductName()
{
	return productName;
}

string Product::getCategoryOfProduct()
{
	return categoryOfProduct;
}

double Product::getProductQuantity()
{
	return productQuantity;
}

int Product::getProductSellerID()
{
	return productSellerID;
}

double Product::getPriceOfProduct()
{
	return priceOfProduct;
}

double Product::getProductRate()
{
	if (rateOfProduct >= 0 && rateOfProduct <= 5)
		return rateOfProduct;
	else
		return 0;
}

void Product::rateOfNewProduct()
{
	Rate prodRate { productID, 0, 0 };

	productsRate.push_back(prodRate);
}

void Product::updateProductsRate(double CustomerRate, Product &prodObj)
{

	//	newRate = ((Overall Rating * Total Rating) + new Rating) / (Total Rating + 1)

	for (auto i = productsRate.begin(); i != productsRate.end(); i++)
	{
		if (prodObj.getProductID() == i->ID)
		{
			i->overAllRating = ((i->overAllRating * i->numOfUsersRated) + CustomerRate) / (i->numOfUsersRated + 1);

			setProductRate(i->overAllRating);

			i->numOfUsersRated++;
		}
	}

	ofstream fileObj;

	fileObj.open("ProductsRate.txt", ios::trunc);

	if (fileObj.is_open()) {

		for(auto i = productsRate.begin(); i != productsRate.end(); i++)
		{
			fileObj << i->ID << " " << i->overAllRating << " " << i->numOfUsersRated << endl;
		}
	}

	fileObj.close();
}

void Product::setProductCustomerID(int prodCustomerID)
{
	productCustomerID = prodCustomerID;
}

int Product::getProductCustomerID()
{
	return productCustomerID;
}

/*---------------------CustomerCartClass---------------------*/
void CustomerCart::setTotalPrice(double price, int amount)
{
	totalPrice += (price * amount);
}

double CustomerCart::getTotalPrice()
{
	return totalPrice;
}

void CustomerCart::addProductToCart(int desiredQuantity, Product& prodObject)
{
	int totalDesiredQuantity = 0;

	bool rateOptionOfProduct = true;

	bool rateOptionOfSeller = true;

	if (!listOfProducts.empty())
	{
		totalDesiredQuantity = desiredQuantity;

		for (auto i = listOfProducts.begin(); i != listOfProducts.end(); i++)
		{
			if (i->getProductID() == prodObject.getProductID())
			{
				totalDesiredQuantity += i->getProductQuantity();

				rateOptionOfProduct = false;

				rateOptionOfSeller = false;
			}
		}
	}

	if (totalDesiredQuantity > prodObject.getProductQuantity() || desiredQuantity > prodObject.getProductQuantity())
	{
		cout << "\n*****Sorry, the available quantity of this product is less than the desired quantity..This item won't be added to your cart . *****\n\nthe total desired quantity now is : " << totalDesiredQuantity << "\n\nthe object quantity is : " << prodObject.getProductQuantity() << "\n\nthe desired quantity is : " << desiredQuantity << "\n\n";
	}
	else
	{
		Product productTemp;

		productTemp = prodObject;

		//cout << "\n\nthe total desired quantity now is : " << totalDesiredQuantity << "\n\nthe object quantity is : " << prodObject.getProductQuantity() << "\n\nthe desired quantity is : " << desiredQuantity << "\n\n";

		productTemp.setProductQuantity(desiredQuantity);

		listOfProducts.push_back(productTemp);

		cout << "\nThis product was added successfully to your cart !\n";

		while (rateOptionOfProduct || rateOptionOfSeller)
		{
			int choice;

			cout << "\nIf u like this product or this seller go and rate any or both of them now\n";

			cout << "1-Rate the product.\n2-Rate the seller.\n3-return to the main menu.\n";

		inValidChoice:

			cin >> choice;

			system("CLS");

			if (choice == 1)
			{
				if (rateOptionOfProduct)
				{
					rateOptionOfProduct = false;

					double rate;

					cout << "Please enter a rate for the product between 1 and 5 : ";

				checkPoint1:

					cin >> rate;

					if (rate >= 1 && rate <= 5)
					{
						prodObject.updateProductsRate(rate, prodObject);

						cout << "\nThanks for your interest and rate :) .\n\n";
					}
					else
					{
						cout << "Invalid range, please enter a rate in the specified range : ";
						goto checkPoint1;
					}
				}
				else
					cout << "\nYou've entered a rate for this product before.\n";
			}
			else if (choice == 2)
			{
				if (rateOptionOfSeller)
				{
					rateOptionOfSeller = false;

					double rate;

					cout << "Please enter a rate for the seller between 1 and 5 : ";

				checkPoint2:

					cin >> rate;

					if (rate >= 1 && rate <= 5)
					{
						sellerObj.updateSellersRate(rate, prodObject.getProductSellerID());

						cout << "\nThanks for your interest and rate :) .\n\n";
					}
					else
					{
						cout << "Invalid range, please enter a rate in the specified range : ";
						goto checkPoint2;
					}
				}
				else
					cout << "\nYou've entered a rate for this seller before.\n";
			}
			else if (choice == 3)
				customerMenu();
			else
			{
				cout << "\nPlease enter a valid choice.\n";
				goto inValidChoice;
			}
		}

		customerMenu();
	}
}


void CustomerCart::displayTheTotalProducts()
{
	if (listOfProducts.empty())
	{
		cout << "********** Your cart is empty. **********\n\n";

		customerMenu();
	}
	else
	{
		totalPrice = 0;

		int numOfProduct = 1;

		cout << "************************** Your cart content **************************\n\n";

		cout <<  "Name of Product " << "\t" << "Category Of Product" << "\t" << "Quantity" << "\t" << "Price/unit" << "\t" << "Product Seller ID" << "\t" << "Product ID\n\n";

		for (list<Product>::iterator i = listOfProducts.begin(); i != listOfProducts.end(); i++, numOfProduct++)
		{
			cout << numOfProduct << "- " << i->getProductName() << "\t\t" << i->getCategoryOfProduct() << "\t\t\t" << i->getProductQuantity() << "\t\t" << i->getPriceOfProduct() << "\t\t" << i->getProductSellerID() << "\t\t\t" << i->getProductID() << "\n\n";

			setTotalPrice(i->getPriceOfProduct(), i->getProductQuantity());
		}
	}

	cout << "\nThe total price of your cart is : " << getTotalPrice();

	int choice;

	while (true)
	{
		cout << "\n\n Press 1 to return to the Main Menu.\n press 2 to keep browsing.\n press 3 to confirm buying these products.\n Press 4 to delete product from the cart.\n";

		cin >> choice;

		if (choice == 1)
			customerMenu();
		else if (choice == 2)
		{
			customerObj.CheckBrowsing();
		}
		else if (choice == 3)
		{
			cout << "\nPurchasing Succeeded !\n";

			cout << "\nThe total price of your cart is : " << getTotalPrice() << "\n\n";

			updateProductsOnMap();

			Product prodTemp;

			for (auto i = listOfProducts.begin(); i != listOfProducts.end(); i++) 
			{
				prodTemp.setProductID(i->getProductID());
				prodTemp.setProductName(i->getProductName());
				prodTemp.setcategoryOfProduct(i->getCategoryOfProduct());
				prodTemp.setProductQuantity(i->getProductQuantity());
				prodTemp.setProductsellerID(i->getProductSellerID());
				prodTemp.setPriceOfProduct(i->getPriceOfProduct());
				prodTemp.setProductRate(i->getProductRate());
				prodTemp.setProductCustomerID(customerObj.getcustomerID());

				HistoryOfCustomer.Append(prodTemp);

				fstream outCustomerProducts("CustomerProducts.txt", ios::app);

				outCustomerProducts << i->getProductID() << " " << i->getProductName() << " " << i->getCategoryOfProduct() << " " << i->getProductQuantity() << " " << i->getProductSellerID() << " " << i->getPriceOfProduct() << " " << i->getProductRate() << " " << customerObj.getcustomerID() << endl;

				outCustomerProducts.close();

			}

			listOfProducts.clear();

			customerMenu();
		}
		else if (choice == 4)
		{
			deleteProductFromCart();

			cout << "\nProduct was deleted Successfully !\n";

			customerMenu();
		}
	}
}

void CustomerCart::deleteProductFromCart()
{
	if (listOfProducts.empty())
	{
		cout << "********** Your cart is empty. **********\n";
		
		customerMenu();
	}
	
	int index;

	cout << "\nPlease, enter the index number of product you want to delete or press '0' to return : ";

	cin >> index;

	if (index == 0)
	{
		displayTheTotalProducts();
	}
	else if (index >= 1 && index <= listOfProducts.size())
	{

		list<Product>::iterator it = listOfProducts.begin();

		advance(it, index - 1);

		listOfProducts.erase(it);
	}
	else
	{
		cout << "enter valid number !\n";
		deleteProductFromCart();
	}
}

void CustomerCart::updateProductsOnMap()
{
	for (auto i = listOfProducts.begin(); i != listOfProducts.end(); i++)
	{
		for (auto j = sellerProducts.begin(); j != sellerProducts.end(); j++)
		{
			if (j->second.getProductID() == i->getProductID())
			{
				/*if (j->second.getProductQuantity() - i->getProductQuantity() == 0)
				{
					sellerProducts.erase(j);
				}
				else*/
				j->second.setProductQuantity(j->second.getProductQuantity() - i->getProductQuantity());
			}
		}
	}

	int productID, productSellerID;

	string productName, categoryOfProduct;

	double productQuantity, priceOfProduct;

	ofstream outSellerProducts("SellerProducts.txt", ios::trunc);

	for (auto i = sellerProducts.begin(); i != sellerProducts.end(); i++)
	{
		if (i->second.getProductQuantity() == 0)
			continue;

		outSellerProducts << i->second.getProductID() << " " << i->second.getProductName() << " " << i->first << " " << i->second.getProductQuantity() << " " << i->second.getProductSellerID() << " " << i->second.getPriceOfProduct() << endl;
	}

	outSellerProducts.close();
}

/*---------------------ImplementLinkedListClass---------------------*/

template<class T>
linkedList<T>::linkedList()
{
	head = tail = 0;
	count = 0;
}

template <class T>
int linkedList<T>::Length()
{
	return count;
}

template<class T>
bool linkedList<T>::isEmpty()
{
	return count == 0;
}

template<class T>
void linkedList<T>::InsertAt(int pos, T  val)
{
	assert(pos >= 0 && pos <= count);
	if (pos == count) // to insert at last of my list 
	{
		Append(val);
	}

	else
	{
		Node* tmp = head;
		Node* newNode = new Node;
		if (pos == 0)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			for (int i = 0; i < pos - 1; i++)
				tmp = tmp->next;
			newNode->next = tmp->next;
			tmp->next = newNode;
		}
		newNode->value = val;
		count++;
	}
}

template <class T>
void linkedList<T>::Append(T newValue)
{
	Node* newNode = new Node;
	newNode->value = newValue;
	if (head == 0)
	{
		head = tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	count++;
}

template <class T>
T linkedList<T>::At(int pos)
{
	assert(pos >= 0 && pos < count);
	Node* tmp = head;
	for (int i = 0; i < pos; i++)
	{
		tmp = tmp->next;
	}
	return tmp->value;
}

template<class T>
void linkedList<T>::DeleteAt(int pos)
{
	assert(pos >= 0 && pos < count);
	Node* tmp = head;
	if (pos == 0)
	{
		head = head->next;
		delete tmp;
	}
	else
	{
		for (int i = 0; i < pos - 1; i++)
		{
			tmp = tmp->next;
		}
		Node* del = tmp->next;
		tmp->next = del->next;
		delete del;
		if (pos == count - 1)
		{
			tail = tmp;
		}
	}
	count--;
}

template<class T>
linkedList<T>::~linkedList()
{
	while (count != 0)
	{
		DeleteAt(0);
	}
}