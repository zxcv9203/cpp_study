#include <iostream>

int main() {
	int *p = new int;
	int a = 5;
	*p = 10;

	std::cout << *p << std::endl;
	delete p;
	delete &a;
	return 0;
}