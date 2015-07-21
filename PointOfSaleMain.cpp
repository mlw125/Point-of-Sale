// Matthew Williams 7/16/2015, modified 7/21/2015

#include "PointOfSale.h"
#include <iostream>
#include <string>
using namespace std;

// For handling the Main Menu of the register
void MainMenu(Login);
// The first part of the program that runs so to get which employee is logged in.
// should probably put into loop so when logging 
Login LoginMenu(Login &);
void RegisterMenu(Login);
void Transactions(Login);
void FoodMenu(Login);
void OpenOrders(Login);

int main()
{
	// will loop forever since register will likely be just logged out of.
	while (1 != 2)
	{
		Login employee;
		LoginMenu(employee);
		MainMenu(employee);
		cout << endl;
	} // end while
    
	system("pause");
    return 0;
} // end main

// currently very simple just gets a username and password, no checking of correctness.
// Maybe add menu to add, remove, and modify users.
Login LoginMenu(Login &employee)
{
  string user = "";
  string pass = "";
  
  cout << "Please enter your username: ";
  cin >> user;
  
  employee.setEmployee(user);
  
  cout << "Please enter your password: ";
  cin >> pass;
  
  employee.setPassword(pass);
  
  return employee;  
} // end LoginMenu

// Main Menu for system
void MainMenu(Login employee)
{
	int choice = 0;
	while (choice != 5)
	{
		cout << "\nWhat would you like to do?\n";
		cout << "1. Take an Order \n2. Modify the Menu \n3. Close an Open Order \n4. View Transation Hisotry \n5. Quit\n";
		cin >> choice;

		if (choice == 1) // opening an order to complete
		{
			RegisterMenu(employee);
		} // end if
		else if (choice == 2) // can modify the menu, maybe require manager access
		{
			// not completed
			FoodMenu(employee);
		} // end else if
		else if (choice == 3)
		{
			OpenOrders(employee);
		} // end else if
		else if (choice == 4) // view the transactions on file
		{
			// not completed
			//Transactions(employee, currentMenu);
		} // end else if
		else if (choice == 5) // sign out
		{
			cout << "\nLogging Out\n";
		} // end else if
		else // general catch
		{
			cout << "\nWrong Input\n";
		} // end else
	} // end while
} // end MainMenu

// The RegisterMenu will handle the orders 
void RegisterMenu(Login employee)
{
	Register currentTransaction;
	Menu currentMenu;
	int choice = 0;

	while (choice != -1)
	{
		// display the curent open order
		currentTransaction.showOrder();
		cout << "\nWhat would you like to do?\n";
		cout << "1. Add Item to Order \n2. Remove Item From Order \n3. View Menu \n4. Add Discount \n5. Complete Order\n";
		cin >> choice;

		if (choice == 1) // add a menu item to the order
		{
			int menuNum = 0;
			cout << "\nEnter the number of the Menu item you would like to add: \n";
			cin >> menuNum;

			int addSuccess = currentMenu.searchPosition(menuNum);
			if (addSuccess == -1)
				cout << "\nItem not found try again"; // end if
			else
				currentTransaction.addToOrder(menuNum); // end else
		} // end if
		else if (choice == 2) // remove an item from the menu
		{
			int menuNum = 0;
			cout << "\nEnter the number of the Menu item you would like to remove: \n";
			cin >> menuNum;

			bool removeSuccess = false;
			removeSuccess = currentTransaction.removeFromOrder(menuNum);
			if (removeSuccess == false)
				cout << "\nItem not found try again"; // end if
		} // end else if
		else if (choice == 3) // show the menu for the employee
		{
			currentMenu.showMenuItems();
		} // end else if
		else if (choice == 4) // will be used for discounts
		{

		} // end else if
		else if (choice == 5) // get the total price of the order and give the customer change and then leave to Main Menu
		{
			double customerMoney = 0.0;
			cout << "\nThe amount due: $" << currentTransaction.getTotal();
			cout << "\nAmount given: $";
			cin >> customerMoney;

			double changeDue = (customerMoney - currentTransaction.getTotal());
			cout << "Change Due: $" << changeDue << endl;
			currentTransaction.addOpenOrder(changeDue);
			choice = -1;
		} // end else if
		else
		{
			cout << "\nWrong Input, try again\n";
		} // end else
	} // end while
} // end RegisterMenu()

// The FoodMenu will handle everything to do with the modifying the menu
void FoodMenu(Login employee)
{
	Menu currentMenu;
	int choice = 0;

	while (choice != 3)
	{
		currentMenu.showMenuItems();
		cout << "\nWhat would you like to do?\n";
		cout << "1. Add to the Menu \n2. Remove from the Menu \n3. Go Back\n";
		cin >> choice;

		if (choice == 1)
		{
			int menuNum = 0;
			cout << "\nNumber in Menu:\n";
			cin >> menuNum;

			string menuName = "";
			cout << "\nName of item:\n";
			cin >> menuName;

			double menuPrice = 0.0;
			cout << "\nPrice of item:\n";
			cin >> menuPrice;

			bool addSuccess = currentMenu.addMenuItems(menuNum, menuName, menuPrice);
			if (addSuccess)
				cout << "\nItem added successfully.\n"; // end if
			else
				cout << "\nItem not added, try again.\n"; // end else
		} // end if
		else if (choice == 2)
		{
			int menuNum = 0;
			cout << "\nEnter the Menu Number of the item you wish to delete: \n";
			cin >> menuNum;

			bool removeSuccess = currentMenu.removeMenuItems(menuNum);
			if (removeSuccess)
				cout << "\nItem removed successfully.\n";
			else
				cout << "\nItem not removed, try again.\n";
		} // end else if
		else if (choice == 3)
		{
			
		} // end else if
		else
		{
			cout << "Wrong input, try again\n";
		} // end else
	} // end while
} // end FoodMenu

void OpenOrders(Login employee)
{
	Logging logOrder;

	int choice = 0;
	while (choice != 3)
	{
		cout << "\nWhat would you like to do?\n";
		cout << "1. View Open Orders \n2. Close an Order \n3. Go Back\n";

		if (choice == 1)
		{

		} // end if
		else if (choice == 2)
		{

		} // end else if
		else if (choice == 3)
		{

		} // end else if
		else
		{

		} // end else
	} // end while
} // end OpenOrders()

// Transactions will handle the viewing of transactions and maybe other related things.
void Transactions(Login currentUser)
{
	Menu currentMenu;

} // end Transactions()