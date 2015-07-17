// Matthew Williams 7/16/2015

#include "PointOfSell.h"
#include <iostream>
#include <string>
using namespace std;

// For handling the Main Menu of the register
void Menu(Login);
// The first part of the program that runs so to get which employee is logged in.
// should probably put into loop so when logging 
Login LoginMenu(Login &);

//currently unused
void Register();
void logData();

int main()
{
	while (1 != 2)
	{
		Login employee;
		LoginMenu(employee);
		Menu(employee);
		cout << endl;
	}
    
	system("pause");
    return 0;
}

// currently very simple just gets a usrname and password, no checking of correctness.
// Passes Login object by reference to change the current data inside.
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
}

// in temporary state: making the username and password are passed along, probably don't need password.
void Menu(Login employee)
{
	cout << "\nUsername:" << employee.getEmployee();
	cout << "\nPassword:" << employee.getPassword() << endl;
}