#include <iostream>
#include <string>
using namespace std;

// where the employee will log in
// the employee's username will be used for logging.
class Login
{
      private:
      public:
        string getEmployee();
        string getPassword();
        void setEmplyee();
        void setPassword();
        bool loggedIn();             
};

// the main part of the program, from here the employee will input the customer's menu choices.
// the employee can then get the get the math from 
class Register
{
      private:
      public:
            int getMenuItem();
            bool openOrders();
            void closeOrder();
            void getOrder();
	    double getChange();
};

// either use a database or store as text document
class Logging
{
      private:
      public:
             void addTransaction();
             void viewTransactions();
};

class Menu
{
      private:
	      string menuList[];
      public:
 	void addMenuItems();
	void showMenuItems();
	void removeMenuItems();	
};

// abstract
class Error
{
};

class Tags
{
};

class User
{
};

class Employee : public User
{
};

class Manager : public User
{
};
