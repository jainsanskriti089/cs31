#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	int start; int end; int numDays; int startingMonth;
	string name;
	string luxCar;

	//get input
	cout << "Odometer at start: ";
	cin >> start;
	cout << "Odometer at end: ";
	cin >> end;
	int miles = end - start;
	cout << "Rental days: ";
	cin >> numDays;
	cin.ignore(1000, '\n');
	cout << "Customer name: ";
	getline(cin, name);
	cout << "Luxury car? (y/n): ";
	getline(cin, luxCar);
	cout << "Starting month (1=Jan, 2=Feb, etc.): ";
	cin >> startingMonth;
	cout << "---" << endl;

	//check input
	if (start < 0) {
		cout << "The starting odometer reading must not be negative." << endl;
		return 1;
	}
	if (end < start) {
		cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
		return 1;
	}
	if (numDays < 0) {
		cout << "The number of rental days must be positive." << endl;
		return 1;
	}
	if (name == "") {
		cout << "You must enter a customer name." << endl;
		return 1;
	}
	if (luxCar != "y" && luxCar != "n") {
		cout << "You must enter y or n." << endl;
		return 1;
	}
	if (startingMonth > 12 || startingMonth < 1) {
		cout << "The month number must be in the range 1 through 12." << endl;
		return 1;
	}

	double cost = 0;
	//calculate base cost
	if (luxCar == "y") {
		cost = 75 * numDays;
	}
	else {
		cost = 45 * numDays;
	}

	double mileCost = 0.27;
	if (startingMonth == 12 || (startingMonth >= 1 && startingMonth <= 3))
		mileCost = 0.33;

	if (miles < 100) {
		cost += miles * 0.33;
	}
	else if (miles < 500) {
		cost += 33 + (miles-100)*mileCost;
	}
	else {
		cost += 33 + (400) * mileCost + 0.21 * (miles - 500);
	}

	//print final cost
	cout << fixed << showpoint;
	cout << setprecision(2);
	cout << "The rental charge for " << name << " is $" << cost << endl;


	
}

/*
* determine how much to charge a car rental customer who has rented a car for a certain number of days and driven a certain number of miles
* things to collect:
*  starting odometer reading
*  ending odometer reading
*  rental days
*  customer name
*  starting month
*/