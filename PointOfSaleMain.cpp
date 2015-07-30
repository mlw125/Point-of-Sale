// Matthew Williams 7/16/2015, modified 7/30/2015

#include "PointOfSale.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
using namespace std;

// For handling the Main Menu of the register
void MainMenu(Login);
// The first part of the program that runs so to get which employee is logged in.
// should probably put into loop so when logging 
void LoginMenu();
// the RegisterMenu handles the taking of the orders, the total cost, and the chnage that is due at the end
// the orders need to be open when leaving this menu.
void RegisterMenu(Login);
// not implemented yet
void Transactions(Login);
// will handle everything related to modifying them enu
void FoodMenu(Login);
// will handle the viewing and closing of any open orders.
void OpenOrders(Login);

int main()
{
	// will loop forever since register will likely be just logged out of.
	while (1 != 2)
	{
		LoginMenu();
		cout << endl;
	} // end while
    
	system("pause");
    return 0;
} // end main

// now checks to see if user is on the list, not requirements for username or password.
// nor is there checking for duplicates yet.
void LoginMenu()
{
	int choice = 0;
	bool correct = false;
	Login employee;

	// code for hiding the password when user puts it in
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);

	// loops until correct is true, meaning the user has a correct account username and password.
	while (correct != true)
	{
		cout << "\nWhat would you like to do?\n";
		cout << "1. Login \n2. Create User\n";\
		cin >> choice;

		// if the user wants to log in
		if (choice == 1)
		{
			string user = "";
			string pass = "";

			cout << "\nPlease enter your username: ";
			cin >> user;

			// turning off echo for the console
			SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

			cout << "Please enter your password: ";
			cin >> pass;

			// turning on echo for the console
			SetConsoleMode(hStdin, mode);

			// see if the employee is on the list
			if (employee.searchUser(user, pass) == true)
			{
				correct = true;
			}
			else
				cout << "\nEmployee not found, try again\n";
		} // end if
		// if the user wants to make a new account
		else if (choice == 2)
		{
			string user = "";
			string pass = "";
			char rank = ' ';

			// input isername
			cout << "\nPlease enter your username: ";
			cin >> user;

			employee.setEmployee(user);

			// turning off echo for the console
			SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

			// input password
			cout << "Please enter your password: ";
			cin >> pass;

			employee.setPassword(pass);

			// turning on echo for the console
			SetConsoleMode(hStdin, mode);

			// input rank
			cout << "\nPlease enter an E for regular employee or a M for Manager: ";
			cin >> rank;

			employee.setRank(rank);
		} // end else if
		else
		{
			cout << "\nWrong input, try again.\n";
		} // end else
	} // end while
  
	MainMenu(employee);
} // end LoginMenu

// Main Menu for system
void MainMenu(Login employee)
{
	int choice = 0;
	while (choice != 5)
	{
		cout << "\n\nWhat would you like to do?\n";
		cout << "1. Take an Order \n2. Modify the Menu \n3. Close an Open Order \n4. View Transation Hisotry \n5. Quit\n";
		cin >> choice;

		// take an order, go to to RegisterMenu()
		if (choice == 1) // opening an order to complete
		{
			RegisterMenu(employee);
		} // end if
		else if (choice == 2) // can modify the menu, maybe require manager access
		{
			FoodMenu(employee);
		} // end else if
		// handles the viewing and closing of open orders
		else if (choice == 3)
		{
			OpenOrders(employee);
		} // end else if
		else if (choice == 4) // view the transactions on file
		{
			Transactions(employee);
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
		// used to get a discount, but only used on total, so can do individually or whole meal.
		else if (choice == 4)
		{
			//string tempUser = employee.getEmployee();
			//char tempRank = employee.getRank(tempUser);
			if (employee.getRank(employee.getEmployee())/*tempRank*/ == 'M')
			{
				double discount = 0.0;
				cout << "\nEnter the percentage discount: ";
				cin >> discount;

				currentTransaction.setDiscount(discount);
			} // end if
			else
			{
				cout << "\n\nYou are not high enough rank to do this.\n\n";
			} // end else
		} // end else if
		else if (choice == 5) // get the total price of the order and give the customer change and then leave to Main Menu
		{
			if (currentTransaction.getTotal() != 0.0)
			{
				// get the tax for the total
				double totalTax = currentTransaction.getTotal();
				double tax = 0.0825;
				double temp = currentTransaction.getTotal() * tax;
				totalTax += temp;

				double customerMoney = 0.0;
				cout << "\nThe amount due: $" << fixed << setprecision(2) << totalTax;
				cout << "\nAmount given: $";
				cin >> customerMoney;

				double changeDue = (customerMoney - currentTransaction.getTotal());
				cout << "Change Due: $" << fixed << setprecision(2) << changeDue << endl;
				Logging currentOrder;
				// to get the menu items that in the current order
				for (int x = 0; x < currentTransaction.getOrderSize(); x++)
				{
					string name = currentTransaction.getOrderItem(x);
					int num = currentTransaction.getItemNumber(x);
					currentOrder.addOrderMenu(num, name);
				} // end for

				// get the total and the customer's change
				currentOrder.addOpenOrder(totalTax, changeDue);
			} // end if
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

		// add something to the menu
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
		// remove something from the menu
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
		// go back
		else if (choice == 3)
		{
			
		} // end else if
		else
		{
			cout << "Wrong input, try again\n";
		} // end else
	} // end while
} // end FoodMenu

// this function will handle the viewing and closing of open orders
void OpenOrders(Login employee)
{
	Logging logOrder;

	int choice = 0;
	while (choice != 3)
	{
		cout << "\nWhat would you like to do?\n";
		cout << "1. View Open Orders \n2. Close an Order \n3. Go Back\n";
		cin >> choice;

		// if the user wants to view all open orders
		if (choice == 1)
		{
			logOrder.showOpenOrders();
		} // end if
		// if the user wants to close an open order
		else if (choice == 2)
		{
			int orderNum = 0;
			cout << "\nWhat order would you like to close?\n";
			cin >> orderNum;

			string employeeLog = employee.getEmployee();
			if (logOrder.closeOrder(orderNum, employeeLog))
				cout << "\nOrder Closed\n";
		} // end else if
		// if the user wants to go back
		else if (choice == 3)
		{
			choice = 3;
		} // end else if
		else
		{
			cout << "\n\nWrong input, try again\n\n";
		} // end else
	} // end while
} // end OpenOrders()

// Transactions will handle the viewing of transactions and maybe other related things.
void Transactions(Login currentUser)
{
	// display all transactions on file
	Logging log;
	log.viewTransactions();
} // end Transactions()