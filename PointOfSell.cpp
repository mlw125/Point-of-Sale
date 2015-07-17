// Matthew Williams 7/16/2015
// David Bumgarner  Modified and expanded 7/17/15
#include "PointOfSell.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Login Functions
Login::Login()
{
	userName = "";
    password = "";
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
} // end setPassword()

void Login::setPassword(string pass)
{
	password = pass;
} // end setPassword()