// Matthew Williams 7/16/2015, modified 8/04/2015
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