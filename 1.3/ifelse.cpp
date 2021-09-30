#include <iostream>

int main() {
	int lucky = 7;
	std::cout << "행운의 숫자를 맞춰보세요" << std::endl;

	int user;

	while (1) {
		std::cout << "입력 : ";
		std::cin >> user;
		if (lucky == user) {
			std::cout << "맞추셨습니다." << std::endl;
			break;
		} else {
			std::cout << "다시 생각해보세요~" << std::endl;
		}
	}
	return 0;
}