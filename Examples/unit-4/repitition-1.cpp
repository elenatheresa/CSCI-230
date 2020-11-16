#include <iostream>
#include <curses.h> 

using namespace std;

int i, x;

int main()
{
// For loops
	cout << "start of 1st for loop" << endl;
	for (i = 0; i < 10; i++) cout << i << endl;
	cout << "end of 1st for loop" << endl;

	cout << "start of 2nd for loop" << endl;
	for (int i = 0; i < 10; i+=2) cout << i << endl;
	cout << "end of 2nd for loop" << endl;

	cout << "start of 3rd for loop" << endl;
	for (int i = 10; i >= 0; i--) cout << i << endl;
	cout << "end of 3rd for loop" << endl;
 
// While loops
	cout << "start of 1st while loop" << endl;
	x = 0;
	while (x < 10) {
   		cout << x << endl;
   		x++;
	}
	cout << "end of 1st while loop" << endl;

	// no loop
	cout << "start of 2nd while loop" << endl;
	x = 10;
	while (x < 10) {
   		cout << x << endl;
   		x++;
	}
	cout << "end of 2nd while loop" << endl;

	// infinite loop
	cout << "start of 3rd while loop" << endl;
	x = 0;
	while (x >= 0) {
   		cout << "infinite loop x=" << x++ << endl;
 	}

// Do while loops
	cout << "start of 1st do-while loop" << endl;
 	x = 0;
	do {
   		cout << x++ << endl;
	} while (x < 10);
	cout << "end of 1st do-while loop" << endl;

	cout << "start of 2nd do-while loop" << endl;
	x = 10;
	do {
   		cout << x++ << endl;
   	} while (x < 10); 
	cout << "end of 2nd do-while loop" << endl;

	cout << "start of 3rd do-while loop" << endl;
	x = 0;
	do {
   		cout << x++ << endl;
	} while (x > 0);

// Do while loops with switch
	int do_not_exit = 1;
	char choice;
   	do {
   		system("clear");
   		cout << "OPTIONS:\n";
   		cout << "L - Load a file.\n";
   		cout << "S - Save a file.\n";
   		cout << "P - Print a file.\n";
		cout << "? - Get help.\n";
		cout << "X - Exit.\n";
   		cout << "Enter choice: ";
   		cin  >> choice;
   		switch (choice) {
      		case 'L' :
  	      		cout << "Load a file.\n";
 	      		break;
      		case 'S' :
	      		cout << "Save a file.\n";
	      		break;
      		case 'P' :
	     		cout << "Print a file.\n";
	      		break;
      		case '?' :
	      		cout << "Offer help.\n";
	      		break;
			case 'X' :
	      		do_not_exit = 0;
	      		break;
			default:
           		cout << "Invalid choice\n";
   		}
	} while (do_not_exit);
}