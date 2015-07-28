// Matthew Williams 7/16/2015, modified 7/22/2015

/*
This is what I have so far. I have tried to explain why I did what I did. Feel free to make changes and suggest new things.
*/

#ifndef PointOfSale_H
#define PointOfSale_H

#include <string>
#include <vector>
using namespace std;

class Login
{
      private:
         string userName;
         string password;
		 vector<string> nameList;
		 vector<string> passwordList;
	     vector<char> rankList;
      public:
		Login();
		~Login();
        string getEmployee();
		bool searchUser(string, string);
        void setEmployee(string);
        void setPassword(string);
		void setRank(char);
		char getRank(string);
}; // end Login

// test idea: class Employee : public Login
// then: class Manager : public Employee

class Employee
{
}; // end Employee

class Manager : public Employee
{
}; // end Manager

// The "main" part of the program as I see it. Will get information from the Menu class
// and display totals and change due.
class Register
{
	private:
		double total;
		vector<string> menuName;
		double itemPrice(int);
		vector<int> currentOrderNum;
		vector<string> currentOrderName;
	public:
		Register();
		~Register();
		void addToOrder(int);
		bool removeFromOrder(int);
		void showOrder();
		double getTotal();
		int getOrderSize();
		string getOrderItem(int);
		int getItemNumber(int);
}; // end Register

// the logging class will handle the storing of the transations.
class Logging
{
	private:
		//int orderNumber;
		vector<int> orderNum;
		vector<vector<string>> menuContents;
		vector<double> orderTotal;
		vector<double> orderChange;
		vector<int> currentOrderNum;
		vector<string> currentOrderName;

		vector<vector<string>> transMenu;
		vector<int> transNum;
		vector<double> transTotal;
		vector<double> transChange;
		vector<string> transEmployee;

	public:
		Logging();
		~Logging();
		void showOpenOrders();
		void addTransaction(int, string);
		void viewTransactions();
		void addOpenOrder(double, double);
		void addOrderMenu(int, string);
		bool closeOrder(int, string);
		int findIndex(int);
}; // end Logging


// As I saw this this will handle the items on the Menu and is able to be modified to
// to handle menu changes.
class Menu
{
	private:
		// the idea is that each vector will hold information from the menu.
		// This way we do not have to worry about arrays.
		vector<int> menuNumber;
		vector<string> menuItem;
		vector<double> menuPrice;
		int numItems;
	public:
		Menu();
		~Menu();
		bool addMenuItems(int, string, double);
		void showMenuItems();
		bool removeMenuItems(int);
		double searchPrice(int);
		int getMenuSize();
		int searchPosition(int);
		void sortMenu();
}; // end Menu

#endif
