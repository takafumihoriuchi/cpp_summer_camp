#include <iostream>
#include "clock.h"

int tenpuzzle(int n);
int main() {
	int n,count;
	std::cin >> n;

	start_counter();
	// ===== BEGIN =====
	count = tenpuzzle(n);
	// ===== END =====
	print_counter();
	std::cout << count << std::endl;
}
