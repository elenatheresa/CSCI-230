#include <iostream>
#include <curses.h> 

using namespace std;

int i, x;

int main()
{
	int do_not_exit = 1;
	float value; char choice;
	float P, Q;

   	do {
		cout << "C – Clear screen.\n";
		cout << "P – Prompt for value.\n";
		cout << "S – Get SUM.\n";
   		cout << "F – Get FACTORIAL.\n";
        cout << "X - Exit.\n";
	   	cout << "Enter choice: ";
      	cin  >> choice;
	   	switch (choice) {
      		case 'C':
				system("clear");
				break;
      		case 'P':
	      		cout << "Enter a value: \n";
 				cin >> value;
	      		break;
      		case 'S':
            	P = 0.0;
				for (i = 1; i <= value; i++) {
     				P = P + float(i);
				}
	     		cout << "Sum: " << P << endl;
	      		break;
      		case 'F':
         		Q = 1.0;
				for (i = 1; i <= value; i++) {
     				Q = Q*float(i);
				}
	      		cout << "Factorial: " << Q << endl;
	      		break;
			case 'X':
	      		do_not_exit = 0;
	      		break;
			default:
           		cout << "Invalid choice\n";
   		}
	} while (do_not_exit);
}