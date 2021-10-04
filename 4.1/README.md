# 객체란?

이전에 만든 프로그램에서 Animal 이라는 구조체를 가져와서 살펴봅시다.

``` c++
typedef struct Animal {
	char name[30];
	int age;

	int health;
	int food;
	int clean;
}				Animal;
```

위와 같이 Animal 구조체를 정의한 후 animal 변수를 만들어서 이를 필요로 하는 함수들에게

``` c++
play(list[play_with]);
```

이와 같이 전달해 주었습니다.

그런데 곰곰히 생각해보면 play 함수에 인자로 전달하는 것이 이상합니다.

이 상황을 생각해보면 play가 animal을 하는 것처럼 느껴집니다.

다시 생각해보면 animal이 play를 하는 것이 더 맞는 표현이라고 생각이 듭니다.

만약 다음과 같이 작성할 수 있다면 play 함수에 animal을 인자로 주지 않아도 됩니다.

``` cpp
Animal animal;

animal.play();
animal.sleep();
```

이렇게 작성하면 animal이 play하는 것이기 때문에 이미 play 함수가 알고 있기 때문입니다.

play 함수는 나의 상태, 예를 들어서 체력이나 배고픔 정도나 피곤한 정도 등을 모두 알 수 있기 때문에 animal에 대한 적절한 처리를 할 수 있게 되는 것입니다.

즉, animal은 자신의 상태를 알려주는 변수와, 자신이 하는 행동들 (play, sleep 등등)을 수행하는 함수(method)로 이루어졌다고 볼 수 있습니다.

결과적으로 객체는 다음과 같이 정의됩니다.

객체란, 변수들과 참고 자료들로 이루어진 소프트웨어 덩어리 이다.

이때, 객체가 현실 세계에서 존재하는 것들을 나타내기 위해서는 추상화(abstraction)이라는 과정이 필요로 합니다.

컴퓨터 상에서 현실 세계를 100% 나타낼 수 없는 것이기 때문에, 적절하게 컴퓨터에서 처리할 수 있도록 바꾸는 것인데, 예를 들어서 핸드폰의 경우 전화를 한다, 문자를 보낸다 와 같은 것들은 핸드폰이 하는 것이므로 함수로 추상화시킬 수 있고, 핸드폰의 상태를 나타내는 것들, 예를 들어서 자기 자신의 전화번호나 배터리 잔량 같은 것은 변수로 추상화 시킬 수 있습니다.

객체는 자기 만의 정보를 나타내는 변수들과 이를 가지고 어떠한 작업을 하는 함수들로 둘러싸고 있다고 보시면 됩니다.

참고로, 이러한 객체의 변수나 함수들을 보통 인스턴스 변수(instance variable)와 인스턴스 메소드(instance method)라고 부르게 되는데, 그냥 알고 계시는 변수와 함수와 동일한 것으로 생각하시면 됩니다.

누군가 인스턴스 메소드라고 하면 "아 그냥 객체에 정의되어 있는 함수구나"라고 생각 하시면 됩니다.

객체를 그림으로 그리면 다음과 같이 그릴 수 있습니다.

![object](./image/aaa.PNG)

위의 그림에서 메서드가 변수들을 감싸고 있는 것 처럼 그리는 이유는 진짜로 변수들이 외부로 부터 '보호'되고 있기 때문입니다.

다시 말해 외부에서 어떠한 객체의 인스턴스 변수의 값을 바꾸지 못하고 오직 개체의 인스턴스 함수를 통해서만 가능하다는 것이죠 (물론 절대적으로 불가능한 것은 아니고 개발자가 조절할 수 있습니다.)

이를 단순히 코드로 표현한다면 Animal의 food라는 변수 값을 바꾼다고 합시다.

``` cpp
animal.food += 100;        // fail
animal.increase_food(100); // ok
```

`animal.food += 100` 과 같이 외부에서 animal이라는 객체의 인스턴스 변수의 직접 접근하는 것은 불가능하고 `animal.increase_food(100)` 의 경우 animal 객체의 인스턴수 함수를 통해 수정하는 것이기 때문에 가능해집니다.

이와 같이 외부에서 직접 인스턴스 변수의 값을 바꿀 수 없고 항상 메서드를 통해서 간접적으로 조절하는 것을 캡슐화(Encapsulation)이라고 부릅니다.

이 개념을 처음 들으면 이게 왜 필요한지 이해를 못할 수 있습니다.

캡슐화의 장점은 나중에 설명하고 간단하게 말하면 "객체가 내부적으로 어떻게 작동하는지 몰라도 사용할 줄 알게 된다"라고 볼 수 있습니다.

예를 들면, `animal.increase_food(100);`의 경우 food 변수 값이 100 증가하는 것 뿐만 아니라 몸무게도 바뀔 수 있고 행복도도 올라갈 수 있고 등등 여러가지 작업들이 일어날 수 있습니다.

만약 increatse_food 함수를 사용하지 않았다면 해당 값들을 프로그래머가 일일이 더하거나 빼주어야 합니다.

``` cpp
animal.food += 100;
animal.weight += 10;
animal.happy += 10;
...
```
하지만 이것은 프로그래머가 food를 100 늘리는 과정에서 정확히 어떠한 일들이 일어나는지 알아야지만 가능하다는 것입니다.

이런 것을 하나하나 알아보는 것은 굉장히 피곤한 작업일 것이고 프로젝트의 규모가 커지면 객체들을 한 사람이 설계하는 것이 아니기 때문에 다른 사람이 작성한 것을 읽고 완벽히 이해해야만 합니다.

이런 작업은 굉장히 힘든 작업이겠죠

하지만 인스턴스 메소드를 이용하면 "food 값을 늘리려면 increase_food를 이용하세요" 라는 것만 알아도 객체 내부적으로 알아서 처리가 되기 때문에 이를 사용하는 프로그래머가 굳이 이해하지 않아도 됩니다.

"내부적으로 어떻게 처리되는지 알 필요가 없다!"라는 말이 조금 못마땅하다고 생각하시는 분들이 있을 것입니다.

사람이 그렇게 무책임 해서도 되나 말이죠. 하지만 곰곰히 생각해보면 우리가 접하는 모든 전자 기기들은 캡슐화 되어 있다고 볼 수 있습니다.

노트북의 경우도 화면에 글자 'a'를 띄우기 위해서 우리는 컴퓨터 내부에서 어떠한 연산이 처리되는지 알 필요가 없습니다.

단순히 우리가 하는 일은 '키보드의 a를 누른다'라는 마치 `my_computer.keyboard_hit('a');` 라는 메서드를 호출하는 것과 동일한 작업이지요 만일 노트북이 캡슐화되어 있지 않다면요?

노트북을 제대로 사용하기란 굉장히 힘들것입니다.

> 클래스

자 그러면 객체는 C++ 상에서 어떻게 만들어낼까요?

이를 위해 C++에서 객체를 만들 수 있는 장치를 준비하였습니다.

쉽게 말하면 객체의 설계도라고 볼 수 있지요

바로 클래스입니다.

클래스를 이용해서 만들어진 객체를 인스턴스라고 합니다.

앞서 객체의 변수와 메서드를 인스턴스 변수와 인스턴스 메서드라고 한 이유입니다.

다음과 같이 C++ 코드를 작성해봅시다.

``` c++
#include <iostream>

class Animal {
	private:
		int food;
		int weight;
	public:
		void set_animal(int _food, int _weight) {
			food = _food;
			weight = _weight;
		}
		void increase_food(int inc) {
			food += inc;
			weight += (inc / 3);
		}
		void view_stat() {
			std::cout << "이 동물의 food : " << food << std::endl;
			std::cout << "이 동물의 weight : " << weight << std::endl;
		}
}; // 세미콜론을 꼭 써주어야 합니다.

int main() {
	Animal animal;
	animal.set_animal(100, 50);
	animal.increase_food(30);
	animal.view_stat();
	return 0;
}
```

코드를 한 번 살펴봅시다.

``` cpp
Animal animal;
```

먼저 main 함수에서 Animal 클래스의 인스턴스를 어떻게 생성하였는지 살펴 봅시다.

기존의 구조체에서 구조체 변수를 생성할 때와 동일한데, 구조체의 경우 앞에 struct를 명시 했어야 했지만 여기서는 그러지 않아도 됩니다.

그냥 int나 char 처럼 Animal이라고 써주면 됩니다.

위와 같이 `Animal animal;`을 하면 Animal 클래스의 animal 인스턴스를 만든 것입니다.

이제 클래스 내부를 살펴봅시다.

``` cpp
class Animal {
	private:
		int food;
		int weight;
	public:
		void set_animal(int _food, int _weight) {
			food = _food;
			weight = _weight;
		}
		void increase_food(int inc) {
			food += inc;
			weight += (inc / 3);
		}
		void view_stat() {
			std::cout << "이 동물의 food : " << food << std::endl;
			std::cout << "이 동물의 weight : " << weight << std::endl;
		}
}; 
```

위는 Animal이라는 클래스를 나타낸 것으로 Animal 클래스를 통해서 생성될 임의의 객체에 대한 설계도라고 볼 수 있습니다.

즉, Animal 클래스를 통해서 생성될 객체는 food, weight라는 변수가 있고, set_animal, increase_food, view_stat 이라는 함수들이 있는데, Animal 클래스상에서 이들을 지칭할 때는 각각 멤버변수와 멤버함수라고 부릅니다.

즉, 인스턴스로 생성된 객체에서는 인스턴스 변수, 인스턴스 함수, 그리고 그냥 클래스 상에서는 멤버 변수, 멤버 함수라고 부르는 것입니다.

멤버 변수와 멤버 함수는 실제하는 것이 아닙니다.

인스턴스가 만들어져야 비로소 사용할 수 있게 됩니다.

예를들어, 아파트 설계도가 있다고 해서 아파트가 실제로 존재하는 것이 아닌 것 처럼 말이죠

클래스의 내부를 좀더 살펴봅시다.

```cpp
	private:
		int food;
		int weight;
```

먼저 멤버 변수들을 정의한 부분을 봅시다.

처음보는 private 라는 키워드가 있는데 이러한 키워드를 접근 지시자라고 부릅니다.

접근 지시자의 역할은 외부에서 멤버들에 접근을 할 수 있는지 없는지를 알려줍니다.

private 키워드의 경우 아래에 쓰여진 것들은 모두 객체 내에서 보호되고 있다는 의미입니다.

앞서 객체 그림을 떠올려보면 멤버 변수들은 객체 안에서 보호 받고 있었습니다.

private 되고 있는 모든 것들은 자기 객체 안에서만 접근할 수 있을 뿐 객체 내부에서는 접근할 수 없게 됩니다.

다시 말해 다음과 같이 같은 객체안에서 food와 weight에 접근하는 것은 가능한 일이지만

``` cpp
		void set_animal(int _food, int _weight) {
			food = _food;
			weight = _weight;
		}
```

다음과 같이 객체밖에서 직접적으로 접근하는 것은 불가능합니다.

``` cpp
int main() {
	Animal animal;
	animal.food = 3030;
}
```

다음과 같이 접근지시자를 public으로 설정한 것은 외부에서 마음껏 사용할 수 있습니다.

```c++
public:
		void set_animal(int _food, int _weight) {
			food = _food;
			weight = _weight;
		}
		void increase_food(int inc) {
			food += inc;
			weight += (inc / 3);
		}
		void view_stat() {
			std::cout << "이 동물의 food : " << food << std::endl;
			std::cout << "이 동물의 weight : " << weight << std::endl;
		}
```

만약 키워드를 설정하지 않았다면 기본적으로 private로 설정됩니다.

예를들어, 다음과 같이 선언하면 해당 멤버들은 private로 설정됩니다.

```cpp
class Animal {
	/* 자동으로 private */
	int food;
	int weight;
}
```

만일 멤버 변수들도 public으로 공개해버리면 메서드를 외부에서 접근한 것처럼 직접 수정이 가능해집니다.

``` cpp
animal.food = 100;
```

마지막으로 멤버 변수에 대해 조금 더 자세히 알아보겠습니다.

``` cpp
void set_animal(int _food, int _weight) {
	food = _food;
	weight = _weight;
}
```

위는 각 멤버 변수들의 값을 설정하는 부분인데요, 여기서 food와 weight는 누구의 것일까요?

당연하게도 객체(class) 자신의 것입니다.

그렇기 때문에 food와 weight가 누구 것인지 명시할 필요 없이 그냥 food weight라고 사용하면 됩니다.