#include <iostream>

int &function(int &b) {
	b += 5;
	std::cout << &b << std::endl;
	return b;
}

int main() {
	int a = 3;
	std::cout << &a << std::endl;
	const int &c = function(a);
	std::cout << &c << std::endl;
	int k = 1;
	int &q = k;
	std::cout << &q << &k << std::endl;
	std::cout << "c : " << c << std::endl;
	return 0;
}