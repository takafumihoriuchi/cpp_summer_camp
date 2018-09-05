#include <iostream>
#include "clock.h"
using namespace std;

int tenpuzzle(int n);

int main()
{
	int n, count;
	cin >> n;

	start_counter();
	// ===== BEGIN =====
	count = tenpuzzle(n);
	// ===== END =====
	print_counter();
	cout << count << endl;
}