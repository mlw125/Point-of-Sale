// Matthew Williams 7/16/2015, modified 7/22/2015
// David Bumgarner  Modified and expanded 7/17/15
#include "PointOfSale.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <ctype.h>
#include <sstream>
using namespace std;

// Login Functions
Login::Login()
{
	// read usernames from the file, maybe add qualifier to signify position i.e. manager or lowly employee
	// for placement of file see Menu contructor comment
	fstream loginFile("Logins.txt");

	string nameData = "";
	string passwordData = "";
	char rankData = ' ';

	// read the file and store the data into vectors, one for username and one for passwords
	while (loginFile >> nameData >> passwordData >> rankData)
	{
		nameList.push_back(nameData);
		passwordList.push_back(passwordData);
		rankList.push_back(rankData);
	} // end while
	loginFile.close();
} // end Login Constructor

string Login::getEmployee()
{
	return userName;
} // end getEmployee()

// this searches to see if the user is already in the stored uernames and passwords
bool Login::searchUser(string name, string pass)
{
	// will loop through the size of the vectors
	for (unsigned int x = 0; x < nameList.size(); x++)
		// if both the username and corresponding password are found then return true
		if (name == nameList[x] && pass == passwordList[x])
		{
			userName = name;
			password = pass;
			rank = rankList[x];
			return true;
		}// end if
	// end for
	return false;
} // end searchUser()

// add the username to the list
void Login::setEmployee(string user)
{
	nameList.push_back(user);
} // end setEmployee()

// add the password to the list
void Login::setPassword(string pass)
{
	passwordList.push_back(pass);
} // end setPassword()

// set the rank of the employee
void Login::setRank(char position)
{
	toupper(position);
	rankList.push_back(position);
} // end setRank()

// get the rank of the employee from the list
char Login::getRank(string user)
{
	for (unsigned int x = 0; x < nameList.size(); x++)
		if (user == nameList[x])
		return rankList[x];
	return 'E';

} // end getRank()

// Login deconstructor will submit all new users to the file
Login::~Login()
{
	ofstream LoginFile("Logins.txt");

	string nameData = "";
	string passwordData = "";
	char rankData = ' ';

	for (unsigned int x = 0; x < nameList.size(); x++)
	{
		nameData = nameList[x];
		passwordData = passwordList[x];
	
		rankData = rankList[x];

		LoginFile << nameData << " " << passwordData << " " << rankData << endl;
	} // end for

	LoginFile.close();
} // end Login deconstructor

// Employee Prices
// Manager Functions

// Register Functions
Register::Register()
{
	ifstream MenuFile("Menu.txt");

	// just to read data that is not need
	string junk1 = "", junk2 = "";
	// to get the names of menu items
	string nameData = "";

	// store the data into the name vector
	while (MenuFile >> junk1 >> nameData >> junk2)
	{
		menuName.push_back(nameData);
	} // end while
	MenuFile.close();

} // end Register Contructor


// may not be needed
Register::~Register()
{

} // end Register Contructor

// this function will return the price of the selected menu item
double Register::itemPrice(int menuItem)
{
	Menu menu;
	return menu.searchPrice(menuItem);
} // end itemPrice

// this function cumulates the total cost and adds an item to the order
void Register::addToOrder(int menuNum)
{
	// increment total cost and add the item number to the number vector
	total += itemPrice(menuNum);
	currentOrderNum.push_back(menuNum);

	// get the name for the coressponding item number and push that onto the name vector.
	string name = menuName[menuNum-1];
	currentOrderName.push_back(name);
} // end addToOrder()

// removes an item from the order
bool Register::removeFromOrder(int menuNum)
{
	// loop through the entire vector
	for (unsigned int x = 0; x < currentOrderNum.size(); x++)
	{
		// a temporary variable to hold data and compare it to the item number the user inputted
		int temp = currentOrderNum[x];
		if (temp == menuNum)
		{
			// if that item number is found then delete it from both vectors and decrement the cost.
			total -= itemPrice(menuNum);
			currentOrderNum.erase(currentOrderNum.begin() + x);
			currentOrderName.erase(currentOrderName.begin() + x);
			return true;
		} // end if
	} // end for
	return false;
} // end removeFromOrder()

// simply displays the current order, but just the number.
void Register::showOrder()
{
	cout << endl;
	// loop through the vectors and display their data in a somewhat legible way
	for (unsigned int x = 0; x < currentOrderNum.size(); x++)
	{
		cout << endl;
		cout << currentOrderNum[x] << " " << currentOrderName[x] << "$ " << itemPrice(currentOrderNum[x]) <<  " | ";
/*		if ((x % 2) == 0 && x != 0)
			cout << endl;*/
	} // end for
	cout << "\nCurrent Total: $" << total << endl;
} // end showOrder()

// this function returns the total cost
double Register::getTotal()
{
	return total;
} // end getTotal

// returns the size of the vectors
int Register::getOrderSize()
{
	return currentOrderName.size();
} // end getOrderSize()

string Register::getOrderItem(int x)
{
	return currentOrderName[x];
}

int Register::getItemNumber(int x)
{
	return currentOrderNum[x];
}

// Menu Functions
// the contructor will read from a file containing the menu items and store then in vectors to more easily work with
Menu::Menu()
{	
	// Now working, need to place this file in ex: PointOfSale\Project1
	ifstream MenuFile("Menu.txt");

	int numData = 0;
	string nameData = "";
	double priceData = 0.0;

	while (MenuFile >> numData >> nameData >> priceData)
	{
		menuNumber.push_back(numData);
		menuItem.push_back(nameData);
		menuPrice.push_back(priceData);
		numItems++;
	} // end while
	MenuFile.close();
} // end Menu contructor

// the deconstructor will read to a file by pulling stuff from the vectors
Menu::~Menu()
{
	ofstream MenuFile("Menu.txt");

	int numData = 0;
	string nameData = "";
	double priceData = 0.0;

	for (int x = 0; x < numItems; x++)
	{
		numData = menuNumber[x];
		nameData = menuItem[x];
		priceData = menuPrice[x];

		MenuFile << numData << " " << nameData << " " << priceData << endl;
	} // end for

	MenuFile.close();
} // end ~Menu()

// the functions will add a menu item to the menu if that number does not already exist
// maybe later do more checking for copies
bool Menu::addMenuItems(int num, string name, double price)
{
	// if the item number is not in the menu then add the new item to each vector
	if (searchPosition(num) == -1)
	{
		menuItem.push_back(name);
		menuPrice.push_back(price);
		menuNumber.push_back(num);
		numItems++;
		return true;
	} // end if
	else
		return false; // end else
} // end addMenuItems()

// displays all the data in the vectors to show the current menu
void Menu::showMenuItems()
{
	sortMenu(); // sorts the data so that it can be displayed correctly
	cout << endl;
	for (int x = 0; x < numItems; x++)
	{
		cout << menuNumber[x] << ". " << menuItem[x] << " $" << menuPrice[x] << " | ";
		if ((x % 2) == 0 && x != 0)
			cout << endl;
	} // end for
	cout << endl;
} // end showMenuItems()

// removes an item from the menu
bool Menu::removeMenuItems(int num)
{
	int removePosition = searchPosition(num);

	// if the item number is not in the menu then add the new item to each vector
	if (removePosition != -1)
	{
		menuItem.erase(menuItem.begin() + removePosition);
		menuPrice.erase(menuPrice.begin() + removePosition);
		menuNumber.erase(menuNumber.begin() + removePosition);
		numItems--;
		return true;
	} // end if
	else
		return false; // end else
} // end removeMenuItems()

// This function is used when getting totals for an order. Will return the price if that number is in the
// menu or otherwise return a -1 to signal it was not found.
double Menu::searchPrice(int menuNum)
{
	int getPricePosition = searchPosition(menuNum);
	if (getPricePosition != -1)
		return menuPrice[getPricePosition];
	else
		return getPricePosition;
}

// simply returns the size of the Menu vectors
int Menu::getMenuSize()
{
	return menuNumber.size();
} // end getMenuSize()

// searches for the position of the menu item's number, returns the position if found,
// otherwise return x.
int Menu::searchPosition(int num)
{
	for (int x = 0; x < numItems; x++)
	{
		if (menuNumber[x] == num)
			return x;
	} // end for
	return -1;
} // end searchPosition()

// sorts the menu via selection sort. I can't imagine the menu being that large so this should
// be fast enough.
void Menu::sortMenu()
{
	for (int x = 0; x < numItems; x++)
	{
		int minIndex = x; // holds the lowest index

		// searches for places that need swapping
		for (int y = x; y < numItems; y++)
			if (menuNumber[minIndex] > menuNumber[y])
				minIndex = y; // end if
		// end for

		// swap all the value to get to correct position
		int tempNum = menuNumber[x];
		menuNumber[x] = menuNumber[minIndex];
		menuNumber[minIndex] = tempNum;

		string tempItem = menuItem[x];
		menuItem[x] = menuItem[minIndex];
		menuItem[minIndex] = tempItem;

		double tempPrice = menuPrice[x];
		menuPrice[x] = menuPrice[minIndex];
		menuPrice[minIndex] = tempPrice;
	} // end for
} // end sortMenu()

//Logging Functions
Logging::Logging()
{
	ifstream openOrders("Orders.txt");
	int orderNumber = 0;
	string menuItems1 = "", menuItems2 = "";
	double total = 0;
	double change = 0;

	// for reading 'Order:'
	openOrders >> menuItems1;
	// this helps read the file until it is done
	while (!openOrders.eof())
	{
		// get the line 'Order Number: x' and put x into the order vector
		openOrders >> menuItems2 >> orderNumber;
		orderNum.push_back(orderNumber);

		// get the character '|'
		openOrders >> menuItems1;
		// a vector to hold the list of menu items
		vector<string> menuNames;

		// while the character is '|' get the menu items, will loop until menuItems == 'Total:'
		while (menuItems1 == "|")
		{
			// get the whole line after '|' and put that into menuNames
			openOrders >> menuItems2;
			openOrders >> menuItems1;
			menuItems2 += " ";
			menuItems2 += menuItems1;
			menuNames.push_back(menuItems2);
			// get the next character: either '|' or 'Total:'
			openOrders >> menuItems1;
		} // end while
		// push the list into the 2d vector
		menuContents.push_back(menuNames);

		// get the total and the line Change: x.xx
		openOrders >> total >> menuItems2 >> change;
		// push the total and the change into their vectors
		orderTotal.push_back(total);
		orderChange.push_back(change);

		// for reading '-----------------'
		openOrders >> menuItems1;
		// for reading 'Order:'
		openOrders >> menuItems1;
	} // end while
	openOrders.close();

	ifstream transactions("Transactions.txt");
	orderNumber = 0;
	menuItems1 = ""; 
	menuItems2 = "";
	total = 0;
	change = 0;

	// for reading 'Order:'
	transactions >> menuItems1;
	// while loop will collect all information stored in Transactions.txt
	while (!transactions.eof())
	{
		// get the line 'Order Number: x' and put x into the order vector
		transactions >> menuItems2 >> orderNumber;
		// get the employee username
		transactions >> menuItems1 >> menuItems2;
		transNum.push_back(orderNumber);
		transEmployee.push_back(menuItems2);

		// get the character '|'
		transactions >> menuItems1;
		// a vector to hold the list of menu items
		vector<string> menuNames;

		// while the character is '|' get the menu items, will loop until menuItems == 'Total:'
		while (menuItems1 == "|")
		{
			// get the whole line after '|' and put that into menuNames
			transactions >> menuItems2;
			transactions >> menuItems1;
			menuItems2 += " ";
			menuItems2 += menuItems1;
			menuNames.push_back(menuItems2);
			// get the next character: either '|' or 'Total:'
			transactions >> menuItems1;
		} // end while
		  // push the list into the 2d vector
		transMenu.push_back(menuNames);

		// get the total and the line Change: x.xx
		transactions >> total >> menuItems2 >> change;
		// push the total and the change into their vectors
		transTotal.push_back(total);
		transChange.push_back(change);

		// for reading '-----------------'
		transactions >> menuItems1;
		// for reading 'Order:'
		transactions >> menuItems1;
	} // end while
	transactions.close();
} // end Logging contructor

Logging::~Logging()
{
	if (orderNum.size() != 0)
	{
		ofstream openOrder("Orders.txt");
		// stores everything in order into the file
		for (unsigned int x = 0; x < orderNum.size(); x++)
		{
			openOrder << "Order Number: " << orderNum[x] << " \n";
			for (unsigned int y = 0; y < menuContents[x].size(); y++)
			{
				openOrder << "| " << menuContents[x][y] << "\n";
			} // end for
			openOrder << "Total: " << orderTotal[x] << " " << "Change: " << orderChange[x] << "\n";
			// for reading files, can likely be removed when databases implemented.
			openOrder << "----------------------------------------------------------\n";
		} // end for
		openOrder.close();
	} // end if

	if (transNum.size() != 0)
	{
		ofstream transactions("Transactions.txt");

		// this for loop will store all transactions from the vectors
		for (unsigned int x = 0; x < transNum.size(); x++)
		{
			transactions << "Order Number: " << transNum[x];
			transactions << " Employee: " << transEmployee[x] << "\n";
			for (unsigned int y = 0; y < transMenu[x].size(); y++)
			{
				transactions << "| " << transMenu[x][y] << "\n";
			} // end for
			transactions << "Total: " << transTotal[x] << " " << "Change: " << transChange[x] << "\n";
			// for reading files, can likely be removed when databases implemented.
			transactions << "----------------------------------------------------------\n";
		} // end for
		transactions.close();
	} // end if
}

// adds an open order
// randomly assigns a number to the order
void Logging::addOpenOrder(double getTotal, double change)
{
	// get a random number between 1 - 99 or something
	srand(time(0));
	int randomOrderNum = rand() % 100;
	vector<string> menuItems;

	// store the random order number
	orderNum.push_back(randomOrderNum);
	// get the menu item number and name and store convert them to strings, then store in vector
	for (unsigned int x = 0; x < currentOrderNum.size(); x++)
	{
		string result = "";
		ostringstream convert;
		// convert the numbers into strings since we don't care that they are numbers anymore 
		convert << currentOrderNum[x] << " " <<	currentOrderName[x];
		result = convert.str();
		menuItems.push_back(result);
	} // end for
	menuContents.push_back(menuItems);
	// store the total and the change
	orderTotal.push_back(getTotal);
	orderChange.push_back(change);

	// display the order number for purposes
	cout << "Order Number: " << randomOrderNum << endl;
} // end addOpenOrder

void Logging::addOrderMenu(int orderNumber, string orderName)
{
	currentOrderNum.push_back(orderNumber);
	currentOrderName.push_back(orderName);
} // end addOrderMenu()

void Logging::showOpenOrders()
{
	cout << endl;
	// this for loop will store all previously open orders before the current one
	for (unsigned int x = 0; x < orderNum.size(); x++)
	{
		cout << "Order Number: " << orderNum[x] << " \n";
		for (unsigned int y = 0; y < menuContents[x].size(); y++)
		{
			cout << "| " << menuContents[x][y] << "\n";
		} // end for
		cout << "Total: " << orderTotal[x] << " " << "Change: " << orderChange[x] << "\n";
		// for reading files, can likely be removed when databases implemented.
		cout << "----------------------------------------------------------\n";
	} // end for
} // end showOpenOrders

bool Logging::closeOrder(int orderNumber, string employee)
{
	int orderIndex = findIndex(orderNumber);
	if (orderIndex != -1)
	{
		addTransaction(orderIndex, employee);
		orderNum.erase(orderNum.begin() + orderIndex);
		menuContents.erase(menuContents.begin() + orderIndex);
		orderTotal.erase(orderTotal.begin() + orderIndex);
		orderChange.erase(orderChange.begin() + orderIndex);
		return true;
	} // end if
	else
	{
		return false;
	} // end else
} // end closeOrder()

void Logging::addTransaction(int orderIndex, string employee)
{
	vector<string> tempMenu;

	transNum.push_back(orderNum[orderIndex]);
	for (unsigned x = 0; x < menuContents[orderIndex].size(); x++)
	{
		tempMenu.push_back(menuContents[orderIndex][x]);
	} // end for
	transMenu.push_back(tempMenu);

	transTotal.push_back(orderTotal[orderIndex]);
	transChange.push_back(orderChange[orderIndex]);

	transEmployee.push_back(employee);
} // end addTransaction()

int Logging::findIndex(int number)
{
	for (unsigned int x = 0; x < orderNum.size(); x++)
	{
		if (orderNum[x] == number)
			return x;
	}
	return -1;
} // end findIndex