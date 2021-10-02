# new, delete

메모리를 관리하는 문제는 언제나 중요한 문제입니다.

프로그램이 정확하게 실행되기 위해서는 컴파일 시에 모든 변수의 주소 값이 확정되어야만 했습니다.

하지만, 이를 위해서는 프로그램의 많은 제약이 따르기 때문에 프로그램 실행 시에 자유롭게 할당하고 해제할 수 있는 heap(힙)이라는 공간이 따로 생겼습니다.

하지만 이전에 컴파일러에 의해 어느정도 안정성이 보장되는 stack(스택)과는 다르게 힙은 사용자가 스스로 제어해야 하는 부분인 만큼 책임이 따릅니다.

C언어에서는 malloc과 free 함수를 지원하여 힙 상에서의 메모리 할당을 지원하였습니다.

C++에서도 마찬가지로 malloc과 free 함수를 사용할 수 있습니다.

하지만 언어 차원에서 지원하는 것으로 바로 new와 delete 라고 할 수 있습니다.

new는 말 그대로 malloc과 대응되는 것으로 메모리를 할당하고 delete는 free에 대응되는 것으로 메모리를 해제합니다.

그럼 한 번 어떻게 이를 사용하는지 살펴보겠습니다.

``` c++
#include <iostream>

int main() {
	int *p = new int;
	*p = 10;

	std::cout << *p << std::endl;
	delete p;
	return 0;
}
```

성공적으로 컴파일 하였다면 int 영역이 잘 할당되어 10이 출력 되었음을 알 수  있습니다.

먼저 위와 같이 int 크기의 공간을 할당하여 그 주소 값을 p에 집어 넣었음을 알 수 있습니다.

new를 사용하는 방법은 `T *pointer = new T;`와 같습니다.

그리고 이제 p 위치에 할당도니 공간에 `*p = 10;`을 통해서 값을 집어 넣었고 이를 출력하였습니다.

마지막으로 할당된 공간을 해제하기 위해서 delete를 사용하였는데 `delete p;`를 하게 되면 p에 할당된 공간이 해제 됩니다.

물론 delete로 해제 할 수있는 메모리 공간은 사용자가 new를 통해서 할당된 공간만 가능합니다.

만일 위 처럼 지역 변수를 무리하게 `delete`로 해제해버리려 한다면 다음과 같은 에러메시지가 출력됩니다.

```
free(): invalid pointer
[1]    6709 abort      ./a.out
```

> new로 배열 할당하기

다음과 같이 new로 배열을 할당해봅시다.

``` cpp
#include <iostream>

int main() {
	int arr_size;

	std::cout << "array size : ";
	std::cin >> arr_size;
	int *list = new int[arr_size];
	for (int i = 0; i < arr_size; i++) {
		std::cin >> list[i];
	}
	for (int i = 0; i < arr_size; i++) {
		std::cout << i << "th element of list : " << list[i] << std::endl;
	}
	delete[] list;
	return 0;
}
```
다음과 같이 잘 실행되는 것을 볼 수 있습니다.
```
array size : 3
1
2
3
0th element of list : 1
1th element of list : 2
2th element of list : 3
```

```cpp
	int arr_size;

	std::cout << "array size : ";
	std::cin >> arr_size;
	int *list = new int[arr_size];
```
먼저 위와 같이 배열의 크기를 잡을 arr_size라는 변수를 정의하였고 그 값을 입력 받았습니다.

그리고 list에 new를 이용하여 크기가 arr_size인 int 배열을 생성하였습니다.

배열을 생성할때에는 []를 이용해 크기를 넣어주면 되는데,

``` cpp
T* pointer = new T[size];
```
T를 임의의 타입이라 하면 위와 같이 하면됩니다.

따라서 list는 이제 크기가 arr_size인 int 배열을 가지게 됩니다.

new로 할당한 배열을 메모리 영역을 해제하기 위해서는 다음과 같이 작성해야 합니다.

``` cpp
delete[] list;
```

new[]로 할당을 했기 때문에 delete도 마찬가지로 delete[]로 해제 하면 됩니다.

> 간단한 프로그램 만들어보기

지금까지 배웠던 내용을 기반으로 간단한 프로그램을 만들어봅시다.

요구조건은 다음과 같습니다.

- 동물(struct Animal) 이라는 구조체를 정의해서 이름(char name[30]), 나이(int age), 체력(int health), 배부른 정도(int food), 깨끗한 정도의(int clean) 값을 가집니다.

- 처음에 동물 구조체의 포인터 배열(struct Animal* list[30])을 만들어서 사용자가 동물을 추가할 때마다 하나씩 생성합니다.

- play라는 함수를 만들어서 동물의 상태를 변경하고 show_stat 함수를 만들어서 지정하는 동물의 상태를 출력합니다.

- 1 턴이 지날 때 마다 동물의 상태를 변경합니다.

다음과 같이 작성해봅시다.

```cpp 
#include <iostream>

typedef struct Animal {
	char name[30];
	int age;

	int health;
	int food;
	int clean;
}				Animal;

void create_animal(Animal *animal) {
	std::cout << "동물의 이름이 무엇인가요? ";
	std::cin >> animal->name;

	std::cout << "동물의 나이는 몇살인가요? ";
	std::cin >> animal->age;

	animal->health = 100;
	animal->food = 100;
	animal->clean = 100;
}

void play(Animal *animal) {
	animal->health += 10;
	animal->food -= 20;
	animal->clean -= 30;
}

void one_day_pass(Animal *animal) {
	animal->health -= 10;
	animal->food -= 30;
	animal->clean -= 20;
}

void show_stat(Animal *animal) {
	std::cout << animal->name << "의 상태" << std::endl;
	std::cout << "체력 : " << animal->health << std::endl;
	std::cout << "배부름 : " << animal->food << std::endl;
	std::cout << "청결 : " << animal->clean << std::endl;
}

int main() {
	Animal *list[10];
	int animal_num = 0;

	for (;;) {
		std::cout << "1. 동물 추가하기" << std::endl;
		std::cout << "2. 놀기" << std::endl;
		std::cout << "3. 상태 보기" << std::endl;
		
		int input;
		std::cin >> input;

		switch (input) {
			int play_with;
			case 1:
				list[animal_num] = new Animal;
				create_animal(list[animal_num]);
				animal_num++;
				break ;
			case 2:
				std::cout << "누구랑 노실건가요? ";
				std::cin >> play_with;
				if (play_with < animal_num)
					play(list[play_with]);
				else
					std::cout << "등록되지 않았어요" << std::endl;
			case 3:
				std::cout << "누구를 보실건가요? ";
				std::cin >> play_with;
				if (play_with < animal_num)
					show_stat(list[play_with]);
				else
					std::cout << "등록되지 않았어요" << std::endl;
		}
		
		for (int i = 0; i != animal_num; i++) {
			one_day_pass(list[i]);
		}
	}
	for (int i = 0; i != animal_num; i++) {
		delete list[i];
	}
}
```

실행시켜보면 프로그램이 잘 작동합니다.
