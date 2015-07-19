// Matthew Williams 7/16/2015, modified 7/19/2015
// David Bumgarner  Modified and expanded 7/17/15
#include "PointOfSell.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Login Functions
Login::Login()
{
	fstream loginFile;
	string fileData;
	loginFile.open("Logins.txt");
	//Not currently working
	/*while (!loginFile.eof())
	{
		loginFile >> fileData;
		nameList.push_back(fileData);
		loginFile >> fileData;
		passwordList.push_back(fileData);
	}
	*/loginFile.close();
} // end Login Constructor

string Login::getEmployee()
{
	return userName;
} // end getEmployee()

string Login::getPassword()
{
	return password;
} // end getPassword()

void Login::setEmployee(string user)
{
     userName = user;
} // end setEmployee()

void Login::setPassword(string pass)
{
	password = pass;
} // end setPassword()

// User Functions
// Manager Functions
// Employee Prices

// Register Functions

// this function will return the price of the selected menu item
double Register::itemPrice(int menuItem)
{
	Menu menu;
	return 10.00;//menu.searchPrice(menuItem);
} // end itemPrice

// this function cumulates the total cost
void Register::addToOrder(int menuNum)
{
	total += itemPrice(menuNum);
	currentOrder.push_back(menuNum);
} // end addToOrder

// this function returns the total cost
double Register::getTotal()
{
	return total;
} // end getTotal

// Menu Functions
Menu::Menu()
{
	// will try to something similiar to Login contructor by reading file, assuming someone can get it to work.
} // end Menu contructor

void Menu::addMenuItems()
{

}

void Menu::showMenuItems()
{
	// displays all menu items with format being number, item, then price.
	// the second loop is to display 3 items on one line to save room.
	for (int x = 0; x < numItems; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			cout << endl << menuNumber[x] << ". " << menuItem[x] << " $" << menuPrice[x];
			x++;
			cout << " " << menuNumber[x] << ". " << menuItem[x] << " $" << menuPrice[x];
			x++;
			cout << " " << menuNumber[x] << ". " << menuItem[x] << " $" << menuPrice[x] << endl;
		} // end for
	} // end for
} // end showMenuItems()

void Menu::removeMenuItems()
{

}

double Menu::searchPrice(int menuNum)
{
	return 10.00;
}