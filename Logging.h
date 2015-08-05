// Matthew Williams 7/16/2015, modified 8/04/2015

#ifndef Logging_H
#define Logging_H

#include <string>
#include <vector>
using namespace std;

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

#endif
