#include <iostream>
#include <string>
using namepace std;

class Login
{
      private:
      public:
        string getEmployee();
        string getPassword();
        void setEmplyee();
        void setPassword();
        bool loggedIn();             
}

class Register
{
      private:
      public:
            int getMenuItem();
            bool openOrders();
            void closeOrder();
            void getOrder();
	    double getChange();
}

// maybe abstract
class Logging
{
      private:
      public:
             void addTransaction();
             void viewTransactions();
}

class Menu
{
      private:
	      string menuList[];
      public:
 	void addMenuItems();
	void showMenuItems();
	void removeMenuItems();	
}

// abstract
class Error
{
}

class Tags
{
}

class User
{
}

class Employee : public User
{
}

class Manager : public User
{
}
