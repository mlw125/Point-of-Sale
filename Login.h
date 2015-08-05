// Matthew Williams 7/16/2015, modified 8/04/2015

#ifndef Login_H
#define Login_H

#include <string>
#include <vector>
using namespace std;

class Login
{
private:
	string userName;
	string password;
	char rank;
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

#endif
