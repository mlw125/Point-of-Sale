// Matthew Williams 7/16/2015, modified 8/04/2015

#ifndef Menu_H
#define Menu_H

#include <string>
#include <vector>
using namespace std;

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
