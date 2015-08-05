// Matthew Williams 7/16/2015, modified 8/04/2015
#include "Register.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <ctype.h>
#include <sstream>
#include <iomanip>
using namespace std;

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
	string name = menuName[menuNum - 1];
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
		cout << currentOrderNum[x] << " " << currentOrderName[x] << "$ " << itemPrice(currentOrderNum[x]) << " | ";
		/*		if ((x % 2) == 0 && x != 0)
		cout << endl;*/
	} // end for
	cout << "\nCurrent Total: $" << fixed << setprecision(2) << total << endl;
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
} // end getItemNumber

void Register::setDiscount(double discount)
{
	discount /= 100;
	double temp = 0.0;
	temp = total * discount;
	total -= temp;
} // close setDiscount()