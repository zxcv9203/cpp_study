# 변수

C++에서 변수는 다음과 같이 선언됩니다.
``` c++
#include <iostream>

int main() {
	int i;
	char c;
	double d;
	float f;

	return 0;
}
```

C언어에서 변수를 선언했던 것과 큰 차이가 없습니다.

변수 명 이름 작성 규칙도 C언어에서 바뀐 것이 없습니다.

알파벳, `_`, 숫자들을 사용할 수 있고 그외의 것들은 사용할 수 없습니다.

또한 변수 이름의 맨 앞부분은 숫자가 오면 안됩니다.

> 변수 이름을 지을 때 고려해야하는 점

먼저, 변수의 이름은 변수의 이름만을 딱 보았을 때 무엇을 하는지 확실히 알 수 있어야 합니다.

``` c++
int number_of_people; // good
double interest_rate; // good
int a; // bad
double b; // bad
```

맨 위의 두 변수 이름들은 딱 보았을 때 '아, 첫번째에는 사람의 인원수이고 두번째는 이자율 이구나'라는 느낌을 받을 수 있습니다.

세번째와 네번째 변수는 이름을 보았을때 무슨 역할을 하는지 알아보기 힘듭니다.

따라서, 변수 이름이 조금 길어지더라도 확실히 이해할 수 있는 변수 이름을 짓는 것이 매우 중요합니다.

둘째로, 변수 이름의 띄어쓰기에 관한 규칙인데 보통 변수 이름을 지을 때 두가지 방법을 사용합니다.

하나는 띄어쓰기 부분에 `_`를 넣는 것이고(스네이크 케이스) 다른 하나는 문자를 대문자로 바꿔서 구분하는 것입니다.(카멜 케이스)

``` c++
int number_of_people; // good
int NumberOfPeople; // good
```

두 방법 중 아무거나 선택해도 괜찮지만 두 방법을 혼용하여 쓰는 것은 좋지 않습니다.

``` C++
int NumberOf_People
```

> C++에서의 배열이나 포인터 선언

배열이나 포인터를 정의하는 방법도 C나 C++이나 동일합니다.

C에서 포인터나 배열을 사용하던것 과 같이 다음과 같이 사용하면 됩니다.

``` c++
int arr[10];
int *parr = arr;

int i;
int *pi = &i;
```

> C++에서의 반복문

``` c++
#include <iostream>

int main() {
	int i;
	
	for (i = 0; i < 10; i++) {
		std::cout << i << std::endl;
	}
	return 0;
}
```

C의 `for`문과 차이가 없습니다.

`while` 문도 마찬가지로 C랑 차이가 없습니다.

``` c++
#include <iostream>

int main() {
	int i;

	i = 0;
	while (i < 10)
	{
		std::cout << i << std::endl;
		i++;
	}
	return 0;
}
```

> C++에서의 if - else

C++에서 `if - else` 문 역시 C와 동일한 문법 구조로 되어 있습니다.

아래의 예를 봅시다.

``` c++
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
```

역시 C에서 사용했던 대로 `if - else` 구문을 사용할 수 있습니다.

하지만 위의 코드에서 처음보는 부분이 보입니다.
``` c++
std::cin >> user;
```

`cin`은 사용자로부터 값을 입력받아서 `>>` 를 통해 `user`에 값을 넣습니다.

`cin`도 마찬가지로 `std`에 정의되어 있기에 `std::cin` 과 같이 사용해야 합니다.

C에서 `scanf`를 사용할때는 `&`을 붙였어야 했는데 C++에서는 편리하게도 앞에 `&`을 붙일 필요가 없습니다.

심지어, `scanf` 에서는 `int` 형태로 데이터를 입력 받을지, `char` 형태로 데이터를 받을지에 따라서 `%d` `%c` 같이 구분해야 했는데 C++에서는 `cin`이 변수를 보고 알아서 처리 해줍니다.

아직 여러분은 cin이 뭔지, cout이 뭔지 이게 도대체 함수인건지 변수인건지 구조체 인건지 기본의 쉬프트 연산자로 사용되었던 `<<` `>>` 는 뭔지 도저히 감이 잡히지 않을 것입니다.

그래도 상관없습니다. 일단 사용하세요!

일단 사용하고 편리하게 느껴질때 쯤 강좌에서 뭔지 배울 것입니다.

> C++에서의 switch

이번에는 C++에서의 switch문 예제를 보겠습니다.

``` c++
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
	int user;

	cout << "저의 정보를 표시해줍니다." << endl;
	cout << "1. 이름" << endl;
	cout << "2. 나이" << endl;
	cout << "3. 성별" << endl;
	cin >> user;

	switch (user) {
		case 1:
			cout << "PSI !" << endl;
			break;
		case 2:
			cout << "99살" << endl;
			break;
		case 3:
			cout << "남자" << endl;
			break;
		default:
			cout << "궁금한게 없군요~" << endl;
			break;
	}
	return 0;
}
```

스위치문 역시 예제를 살펴보면 C언어에서 사용하던것과 같습니다.