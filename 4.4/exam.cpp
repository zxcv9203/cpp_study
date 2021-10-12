#include <iostream>

class A {
	private:
		int x;
	public:
		A(int c) : x(c) {}
	A(const A &a) {
		x = a.x;
		std::cout << "복사 생성" << std::endl;
	}
};

class B {
	private:
		A a;
	public:
		B(int c) : a(c) {}
		B(const B& b) : a(b.a) {}
		A get_A() {
			A temp(a);
			return temp;
		}
};

int main() {
	B b(10);

	std::cout << "--------" << std::endl;
	A a1 = b.get_A();
}