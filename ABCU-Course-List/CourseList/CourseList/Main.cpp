#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cstring>
#include "courselist.h"

// Roy Romero
// Course List Project 2
// Lets get it

using namespace std;

int main() {

	int initialInput;
	
	courselist course1;

	while (true) {
		course1.printMenu();
		//Using while loop for input validation
		cout << "Please enter input: ";
		while (!(cin >> initialInput)) {
			cout << "\nError, please enter proper input: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		course1.menuInput(initialInput);
		cout << "\n";




	}




	return 0;


}