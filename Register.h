// Matthew Williams 7/16/2015, modified 8/04/2015

#ifndef Register_H
#define Register_H

#include <string>
#include <vector>
using namespace std;

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
	void setDiscount(double);
	int getOrderSize();
	string getOrderItem(int);
	int getItemNumber(int);
}; // end Register

#endif
