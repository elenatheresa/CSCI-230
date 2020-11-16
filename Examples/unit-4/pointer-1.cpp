#include <iostream>

using namespace std;

// Declare 2 integer variables.
int  var1,  var2;
// Declare 2 pointers to integer variables.
int *ptr1, *ptr2;

int main()
{
	// Initialize and display var1 and var2.
	var1 = 1;
	var2 = 2;
	cout << var1 << " " << var2 << endl;

	// Point to the memory locations of var1 and var2.
	ptr1 = &var1;
	ptr2 = &var2;
	cout << var1 << " " << var2 << endl;
	cout << *ptr1 << " " << *ptr2 << endl;

	// Set the memory location referenced by ptr2 (var2) to // 22.
	*ptr2 = 22;
	cout << var1 << " " << var2 << endl;
	cout << *ptr1 << " " << *ptr2 << endl;

	// Display the memory “addresses”.
	cout << ptr1 << " " << ptr2 << endl;

	// Since ptr1 and ptr2 reference var1 and var2, 
	// the following line essentially sets var1 = var2.
	*ptr1 = *ptr2;
	cout << var1 << " " << var2 << endl;
	cout << *ptr1 << " " << *ptr2 << endl;

	// The following 2 lines “undo” the var1 = var2.
	var1 = 1;
	var2 = 2;
	cout << var1 << " " << var2 << endl;
	cout << *ptr1 << " " << *ptr2 << endl;
}