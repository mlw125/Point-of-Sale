// Matthew Williams 7/16/2015, modified 8/04/2015
#include "Logging.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <ctype.h>
#include <sstream>
#include <iomanip>
using namespace std;

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
		convert << currentOrderNum[x] << " " << currentOrderName[x];
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
		// add the order to the transactions list
		addTransaction(orderIndex, employee);
		// erase the orders from the open orders list
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

	// add the order number to the list
	transNum.push_back(orderNum[orderIndex]);
	// add the order menu items to a list
	for (unsigned x = 0; x < menuContents[orderIndex].size(); x++)
	{
		tempMenu.push_back(menuContents[orderIndex][x]);
	} // end for
	  // push the list onto the vector
	transMenu.push_back(tempMenu);

	// get the total and change due
	transTotal.push_back(orderTotal[orderIndex]);
	transChange.push_back(orderChange[orderIndex]);

	// get the employee who closed the order
	transEmployee.push_back(employee);
} // end addTransaction()

int Logging::findIndex(int number)
{
	// search for the index of the order number
	for (unsigned int x = 0; x < orderNum.size(); x++)
	{
		if (orderNum[x] == number)
			return x;
	}
	return -1;
} // end findIndex

void Logging::viewTransactions()
{
	cout << endl;
	// this for loop will show all transactions from oldest to youngest
	for (unsigned int x = 0; x < transNum.size(); x++)
	{
		cout << "Order Number: " << transNum[x] << " Employee: " << transEmployee[x] << "\n";
		for (unsigned int y = 0; y < transMenu[x].size(); y++)
		{
			cout << "| " << transMenu[x][y] << "\n";
		} // end for
		cout << "Total: " << transTotal[x] << " " << "Change: " << transChange[x] << "\n";
		// for reading files, can likely be removed when databases implemented.
		cout << "----------------------------------------------------------\n";
	} // end for
} // end viewTransactions()