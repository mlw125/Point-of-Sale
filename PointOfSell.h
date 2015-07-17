// Matthew Williams 7/16/2015

/*
This is what I have so far. I have tried to explain why I did what I did. Feel free to make changes and suggest new things.
*/

#ifndef PointOfSell_H
#define PointOfSell_H

#include <string>
#include <vector>
using namespace std;

// this will handle logon checks. I am not sure how we want to implement this, 
// maybe a text document (temporarily?) that handles the employees and perhaps position. 
class Login
{
      private:
              string userName;
              string password;
      public:
		Login();
        string getEmployee();
        string getPassword();
        void setEmployee(string);
        void setPassword(string);   
}; // end Login

// Not sure how to implement the User class and it's children yet
class User
{
}; // end User

class Employee : public User
{
}; // end Employee

class Manager : public User
{
}; // end Manager

// The "main" part of the program as I see it. Will get information from the Menu class
// and display totals and change due.
class Register
{
	private:
	public:
		int getMenuItem();
		bool openOrders();
		void closeOrder();
		void getOrder();
}; // end Register


// the logging class will handle the storing of the transations.
// I have left it alone until we decide how to implement it i.e. text vs database.
class Logging
{
	private:
	public:
		void addTransaction();
		void viewTransactions();
}; // end Logging


// As I saw this this will handle the items on the Menu and is able to be modified to
// to handle menu changes.
class Menu
{
	private:
		// the idea is that each vector will hold information from the menu.
		// This way we do not have to worry about arrays.
		vector<string> menuItem;
		vector<double> menuPrice;
		vector<string> menuNumber;
	public:
		void addMenuItems();
		void showMenuItems();
		void removeMenuItems();
}; // end Menu

#endif
