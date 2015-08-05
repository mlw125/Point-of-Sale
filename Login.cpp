// Matthew Williams 7/16/2015, modified 8/04/2015
#include "Login.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <ctype.h>
#include <sstream>
#include <iomanip>
using namespace std;

Login::Login()
{
	// read usernames from the file, maybe add qualifier to signify position i.e. manager or lowly employee
	// for placement of file see Menu contructor comment
	fstream loginFile("Logins.txt");

	string nameData = "";
	string passwordData = "";
	char rankData = ' ';

	// read the file and store the data into vectors, one for username and one for passwords
	while (loginFile >> nameData >> passwordData >> rankData)
	{
		nameList.push_back(nameData);
		passwordList.push_back(passwordData);
		rankList.push_back(rankData);
	} // end while
	loginFile.close();
} // end Login Constructor

string Login::getEmployee()
{
	return userName;
} // end getEmployee()

  // this searches to see if the user is already in the stored uernames and passwords
bool Login::searchUser(string name, string pass)
{
	// will loop through the size of the vectors
	for (unsigned int x = 0; x < nameList.size(); x++)
		// if both the username and corresponding password are found then return true
		if (name == nameList[x] && pass == passwordList[x])
		{
			userName = name;
			password = pass;
			rank = rankList[x];
			return true;
		}// end if
		 // end for
	return false;
} // end searchUser()

  // add the username to the list
void Login::setEmployee(string user)
{
	nameList.push_back(user);
} // end setEmployee()

  // add the password to the list
void Login::setPassword(string pass)
{
	passwordList.push_back(pass);
} // end setPassword()

  // set the rank of the employee
void Login::setRank(char position)
{
	// capitalize the char and push it onto the list
	position = toupper(position);
	rankList.push_back(position);
} // end setRank()

  // get the rank of the employee from the list
char Login::getRank(string user)
{
	for (unsigned int x = 0; x < nameList.size(); x++)
		if (user == nameList[x])
		return rankList[x];
	return 'E';

} // end getRank()

  // Login deconstructor will submit all new users to the file
Login::~Login()
{
	ofstream LoginFile("Logins.txt");

	string nameData = "";
	string passwordData = "";
	char rankData = ' ';

	// red out the logins to the correct file
	for (unsigned int x = 0; x < nameList.size(); x++)
	{
		nameData = nameList[x];
		passwordData = passwordList[x];
		rankData = rankList[x];

		LoginFile << nameData << " " << passwordData << " " << rankData << endl;
	} // end for

	LoginFile.close();
} // end Login deconstructor