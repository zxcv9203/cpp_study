# 생성자의 초기화 리스트

```cpp
#include <iostream>

class Marine {
	private:
		int hp;
		int coord_x, coord_y;
		int damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);

		int attack();
		void be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
};

Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return damage; }

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();
}
```

성공적으로 컴파일 하였다면 잘 실행되는 것을 볼 수 있습니다.

예전에 만들었던 Marine 클래스와 달라진 것은 딱 하나인데 바로 생성자에서 무언가 특이한 것을 도입했다는 것입니다.

```cpp
Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
```

놀랍게도 함수 본체에는 아무것도 없습니다.

오직 위에 추가된 이상한 것들이 기존의 생성자가 했던 일과 동일한 작업을 하고 있을 뿐입니다.

기존의 생성자는 다음과 같이 생성했었습니다.

```cpp
Marine::Marine() {
  hp = 50;
  coord_x = coord_y = 0;
  damage = 5;
  is_dead = false;
}
```

```cpp
: hp(50), coord_x(0), coord_y(0),
damage(5), is_dead(false) {}
```

이런식으로 초기화하는 것을 초기화 리스트라고 부르며 생성자 호출과 동시에 멤버 변수들을 초기화 해주게 됩니다.

``` cpp
Marine::Marine(int x, int y)
    : coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}
```

위에서 coord_x는 x로 초기화되고 is_dead는 false로 초기화하게 됩니다.

멤버 초기화 리스트의 일반적인 형태는 다음과 같습니다.

```
(생성자 이름) : var1(ar1), var2(arg2) {}
```

여기서 var들은 클래스의 멤버 변수들을 지칭하고 arg는 그 멤버 변수들을 무엇으로 초기화할 지 지칭하는 역할을합니다.

한 가지 흥미로운 점은 var1과 arg1의 이름이 같아도 되는데, 실제로 아래의 예제는 정상적으로 작동합니다.

```cpp
Marine::Marine(int coord_x, int coord_y)
	: coord_x(coord_x), coord_y(coord_y), hp(50), damage(5), is_dead(false) {}
```

왜냐하면 coord_x ( coord_x )에서 바깥쪽의 coord_x는 무조건 멤버 변수를 지칭하게 되는데, 이 경우 coord_x를 지징하는 것이고 괄호 안의 coord_x는 원칙상 Marine이 인자로 받은 coord_x를 우선적으로 지칭하는 것이기 때문입니다.

따라서 실제로 받은 coord_x가 클래스의 멤버 변수 coord_x를 초기화하게 됩니다.

아래같은 경우는 컴파일러가 두 coord_x 모두 인자로 받은 coord_x로 구분해서 오류가 발생합니다.

```cpp
Marine::Marine(int coord_x, int coord_y) {
	coord_x = coord_x;
	coord_y = coord_y;
	hp = 50;
	damage = 5;
	is_dead = false;
}
```

그러면 왜 초기화 리스트를 사용해야 하는 걸까요?

여태까지 하던 방법하고 초기화 리스트를 사용하는 법 둘다 하는 일이 같아 보이는데 말이죠

하지만 실제로는 약간의 차이가 있습니다.

왜냐하면 초기화 리스트를 사용한 버전의 경우 생성과 초기화를 동시에 하게 됩니다.

반면에 초기화 리스트를 사용하지 않는다면 생성을 먼저 하고 그 다음에 대입을 수행하게 됩니다.

쉽게 말하면 초기화 리스트를 사용하는 것은 다음과 같습니다.

``` cpp
int a = 10
```

그냥 이전에 하던대로 하는 것은 다음과 같습니다.

```cpp
int a;
a = 10;
```

만약 에 int 대신에 클래스 였다면 전자의 경우 복사 생성자가 호출되는데, 후자의 경우 디폴트 생성자가 호출된 뒤 대입이 수행된다는 이야기 입니다.

딱보아도 후자가 조금 더 하는 작업이 많게 됩니다.

따라서 초기화 리스트를 사용하는 것이 조금 더 효율적인 작업이라는 사실을 알 수 있습니다.

우리는 반드시 생성과 동시에 초기화 되어야하는 것들이 몇가지 있었습니다.

대표적으로 참조자와 상수가 있습니다.

상수와 참조자는 모두 생성과 동시에 초기화가 되어야 합니다.

따라서 만약에 클래스 내부에 참조자나 상수를 넣고 싶다면 이들을 생성자에서 무조건 초기화 리스트를 사용해서 초기화 시켜주어야만 합니다.

```cpp
#include <iostream>

class Marine {
	private:
		int hp;
		int coord_x, coord_y;
		const int default_damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);

		int attack();
		void be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
};

Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}
```

위 마린 클래스는 프로그래머들이 실수로 마린의 공격력이 이상하게 변하는 것을 막기 위해서 기본 공격력이라는 상수 멤버를 도입해서 딱 고정 시켜 버리고 마음 편하게 프로그래밍할 수 있도록 하였습니다.

따라서 이를 위해 생성자에서 초기화 리스트를 도입해서 default_damage를 생성과 동시에 초기화할 수 있도록 하였습니다.

```cpp
Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false)
```

따라서 우리는 상수인 deafult_damage를 5로 초기화할 수 있고, 이 값은 영원히 바뀌지 않게됩니다.

```cpp
Marine marine1(2, 3);
Marine marine2(3, 5);

marine1.show_status();
marine2.show_status();
```

위와 같이 Marine의 객체들 (marine1, marine2)를 생성하면서 생성자 오버로딩에 따라 Marine(int x, int y)가 호출되는데, 이를 통해 각각(2, 3)과 (3, 5)에 위치해 있는 마린 객체들을 만들 수 있게 되었습니다.

그리고 show_status를 호출해보면 이들이 제대로 정의 되어 있다는 사실을 알 수 있습니다.

```cpp
	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());
```

마찬가지로 Marine 객체들이 서로 공격하는 과정도 잘 실행되고 있음을 알 수 있습니다.

위와 같이 중요한 값들을 상수로 처리하는 것은 매우 유용한 일입니다.

다른 프로그래머가 이 클래스를 사용하면서 실수로 marine의 default_damage를 변경하는 명령을 집어 넣더라도 컴파일 오류가 발생하기 때문에 프로그램을 실행해서 지루한 디버깅 과정을 거쳐서 알아내는 것보다 훨씬 효율적으로 오류를 발견할 수 있습니다.

``` cpp
#include <iostream>

class Marine {
	private:
		int hp;
		int coord_x, coord_y;
		const int default_damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);

		int attack();
		void be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
};

Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {}

Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Marine marine1(2, 3, 10);
	Marine marine2(3, 5, 10);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}
```

성공정으로 컴파일하면 다음과 같은 결과가 나옵니다.

```
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 50

마린 1이 마린 2를 공격! 
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 40
```

이 예제에서는 생성자 하나를 새로 더 추가하였는데 살펴봅시다.

``` cpp
Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {}
```

이전에는 default_damage에 초기화 리스트로 5를 전달하였는데, 이 생성자의 경우 어떤 값을 전달할지 인자로 받은 다음에 그 내용을 상수에 넣어주었습니다.

마찬가지로 이는 

```
const int default_damage = (인자로 받은 default_damage);
```

를 실행한 것과 마찬가지 이기 때문에 잘 동작됨을 알 수 있습니다.

그리고 실행결과로 5가 아닌 10이 깎였음을 확인할 수 있습니다.

# Static 변수

여태까지 만들어진 총 Marine 수를 알아내기 위한 코드를 짜봅시다.

이를 위해서는 많은 방법이 있겠지만 가장 단순한 두 방식을 생각해 본다면 다음과 같을 것입니다.

1. 어떠한 배열에 Marine을 보관해 놓고 생성된 마린의 개수를 모두 센다.

2. 어떤 변수를 만들어서 Marine의 생성시에 1을 추가하고, 소멸시에 1을 뺀다

첫 번째 방법의 경우 크기가 자유자재로 변할 수 있는 배열을 따로 만들어야하는 문제점이 있고, 두번째의 경우 만일 어떠한 함수 내에서 이런 변수를 정의하였다면 다른 함수에서도 그 값을 이용하기 위해 인자로 계속 전달해야 하는 귀찮음이 있습니다.

물론, 전역 변수로 만들면 되지 않겠냐고 물을 수 도 있겠지만, 전력 변수의 경우 프로젝트의 크기가 커질수록 프로그래머의 실수로 인해 서로 겹쳐서 오류가 날 가능성이 다분하기에 반드시 필요한 경우가 아니라면 사용을 하지 않습니다. (실제로 꼭 필요한 경우가 아니면 전역변수는 사용하지 맙시다.)

하지만 C++에서는 위와 같은 문제를 간단하게 해결할 수 있는 기능을 제공하고 있습니다.

마치 전역 변수 같지만 클래스 하나에만 종속되는 변수인 static 멤버 변수가 있습니다.

예전에 C언어에서 어떠한 함수의 static 변수가 지역 변수들 처럼 함수가 종료될때 소멸되는 것이 아니라 프로그램이 종료될 때 소멸되는 것 처럼, 어떤 클래스의 static 멤버 변수의 경우 멤버 변수들 처럼, 객체가 소멸될 때 소멸되는 것이 아닌 프로그램이 종료될때 소멸되는 것입니다.

또한 이 statiac 멤버 변수의 경우 클래스의 모든 객체들이 '공유'하는 변수로써 각 객체 별로 따로 존재하는 멤버 변수들과는 달리 모든 객체들이 '하나의' static 멤버 변수를 사용하게 됩니다.

``` cpp
#include <iostream>

class Marine {
	private:
		static int total_marine_num;
		
		int hp;
		int coord_x, coord_y;
		const int default_damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);
		~Marine() { total_marine_num--; }

		int attack();
		void be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
};

int Marine::total_marine_num = 0;

Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
		total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {
			total_marine_num++;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	marine3.show_status();
}
int main() {
	Marine marine1(2, 3, 10);

	marine1.show_status();

	Marine marine2(3, 5, 10);

	marine2.show_status();

	create_marine();

	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}
```

```
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 현재 총 마린 수 : 1
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 50
 현재 총 마린 수 : 2
 *** Marine *** 
 Location : ( 10 , 10 ) 
 HP : 50
 현재 총 마린 수 : 3

마린 1이 마린 2를 공격! 
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 현재 총 마린 수 : 2
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 40
 현재 총 마린 수 : 2
```

```cpp
static int total_marine_num;
```

먼저 위와 같이 클래스 static 변수를 정의하였습니다.

모든 전역 및 static 변수들은 정의와 동시에 값이 자동으로 0으로 초기화 되 때문에 이 경우 우리가 굳이 따로 초기화 하지 않앋 ㅗ되지만 클래스 static 변수들의 경우 아래와 같은 방법으로 초기화 합니다.

```cpp
int Marine::total_marine_num = 0;
```

간혹 어떤 사람들의 경우 클래스 내부에서

``` cpp
class Marine {
	static int total_marine_num = 0;
}
```

와 같이 초기화 해도 되지 않냐고 묻는 경우가 있는데, 멤버 변수들을 위와 같이 초기화 시키지 못하는 것처럼 static 변수 역시 클래스 내부에서 위와 같이 초기화하는 것은 불가능합니다.

위와 같은 꼴이 되는 유일한 경우는 const static 변수일 때만 가능한데, 실제로

class Marine {
	const static int x = 0;
}

으로 쓸 수 있습니다.

그럼 실제로 total_marine_sum이 잘 작동하고 있는지 살펴보도록 합시다.

클래스의 편한점이 생성자와 소멸자를 제공한다는 점인데 덕분에 Marine이 생성될 때, 그리고 소멸될 때 굳이 따로 처리하지 않고도, 생성자와 소멸자안에 total_marine_num을 조작하는 문장을 넣어주면 편하게 처리할 수 있습니다.

```cpp
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
		total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {
			total_marine_num++;
}
```

위와 같이 각 생성자 호출 시에 total_marine_sum을 1 증가시키는 문자을 넣고

``` cpp
~Marine() { total_marine_num--; }
```

소멸될 때는 1 감소시키는 문장을 넣었습니다.

```cpp
Marine marine1(2, 3, 5);
marine1.show_status();

Marine marine2(3, 5, 10);
marine2.show_status();
```

위의 코드를 실행하면 Marine의 수가 하나씩 늘어나는 것을 확인할 수 있습니다.

그 다음 create_marine 을 실행했을 때 marine3을 생성함으로써 총 marine의 수가 3이 됨을 확인할 수 있습니다.

marine3은 create_marine의 지역 객체이기 때문에 create_marine이 종료될 때 소멸되게 됩니다.

따라서 다시 main 함수로 돌아와서

```cpp
	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
```

에서 총 마린수를 표현할 때 2명으로 나오게 됩니다.

그런데 클래스 안에 static 변수 만 만들 수 있는 것이 아닙니다.

놀랍게도 클래스 안에는 static 함수도 정의할 수 있는데, static 변수가 어떠한 객체에 종속되는 것이 아니라 클래스 전체에 딱 1개 존재하는 것인 것 처럼, static 함수 역시 어떤 특정 객체에 종속되는 것이 아니라 클래스 전체에 딱 1개 존재하는 함수입니다.

즉, static이 아닌 멤버 함수들의 경우 객체를 만들어야지만 각 멤버 함수들을 호출할 수 있지만 static 함수의 경우 객체가 없어도 그냥 클래스 자체에서 호출할 수 있게 됩니다.

```cpp
#include <iostream>

class Marine {
	private:
		static int total_marine_num;
		const static int i = 0;

		int hp;
		int coord_x, coord_y;
		const int default_damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);
		~Marine() { total_marine_num--; }

		int attack();
		void be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
		static void show_total_marine();
};

int Marine::total_marine_num = 0;

Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
		total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {
			total_marine_num++;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	Marine::show_total_marine();
}
int main() {
	Marine marine1(2, 3, 10);
	Marine::show_total_marine();

	Marine marine2(3, 5, 10);
	Marine::show_total_marine();
	create_marine();

	std::cout << std::endl << "마린 1이 마린 2를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}
```

성공적으로 컴파일하면 잘 실행됩니다.

```
전체 마린 수 : 1
전체 마린 수 : 2
전체 마린 수 : 3

마린 1이 마린 2를 공격! 
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 현재 총 마린 수 : 2
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 40
 현재 총 마린 수 : 2
```

static 함수는 앞에서 이야기 한 것과 같이 어떤 객체에 종속되는 것이 아니라 클래스에 종속되는 것으로 따라서 이를 호출하는 방법도 (객체).(멤버함수)가 아니라 다음과 같이 (클래스)::(static) 함수 형식으로 호출하게 됩니다.

```cpp
Marine::show_total_marine();
```

왜냐하면 어떤 객체도 이 함수를 소유하지 않기 때문이죠. 그러하기에 static 함수 내에서는 클래스의 static 변수 만을 이용할 수 밖에 없습니다.

만일 static 함수 내에서 아래처럼 그냥 클래스의 멤버 변수들을 이용한다면 default_damage가 누구의 default_damege 인지 아무도 모르는 상황이 발생합니다.

```cpp
void Marine::show_total_marine() {
  std::cout << default_damage << std::endl;  // default_damage 는 멤버 변수
  std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}
```

즉, 어떤 객체의 default_damage 인지 static 함수인 show_total_marine()은 알 수 없습니다.

왜냐하면 어떤 객체에도 속하지 않기 때문입니다.

# this

``` cpp
#include <iostream>

class Marine {
	private:
		static int total_marine_num;
		const static int i = 0;

		int hp;
		int coord_x, coord_y;
		const int default_damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);
		~Marine() { total_marine_num--; }

		int attack();
		Marine &be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
		static void show_total_marine();
};

int Marine::total_marine_num = 0;

Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
		total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {
			total_marine_num++;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

Marine &Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
	return *this;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	Marine::show_total_marine();
}
int main() {
	Marine marine1(2, 3, 10);
	Marine::show_total_marine();

	Marine marine2(3, 5, 10);
	Marine::show_total_marine();
	create_marine();

	std::cout << std::endl << "마린 1이 마린 2를 두번 공격! " << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}
```

```
전체 마린 수 : 1
전체 마린 수 : 2
전체 마린 수 : 3

마린 1이 마린 2를 두번 공격! 
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 현재 총 마린 수 : 2
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 30
 현재 총 마린 수 : 2
```

성공적으로 컴파일 하였다면 위와 같은 결과가 나옵니다.

일단 위의 코드에서 가장 먼저 눈에 띄는 것은 바로 레퍼런스를 리턴하는 함수와 this 라는 것인데 차근 차근
살펴보도록 하겠습니다.

```cpp
Marine &Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
	return *this;
}
```

일단 this라는 것이 C++ 언어 차원에서 정의되어 있는 키워드 인데, 이는 객체 자신을 가리키는 포인터의 역할을 합니다.

즉, 이 멤버 함수를 호출하는 객체 자신을 가리킨다는 것이지요

따라서 실제로 위 내용은 다음과 같습니다.

```cpp
Marine &Marine::be_attacked(int damage_earn) {
	this->hp -= damage_earn;
	if (hp <= 0)
		this->is_dead = true;
	return *this;
}
```

실제로 모든 멤버 함수 내에서는 this 키워드가 정의되어 있으며 클래스 안에서 정의된 함수 중에서 this 키워드가 없는 함수는 static 함수 뿐입니다.

그러면 이제 Marine& 을 리턴한다는 말이 무엇인지 생각해봅시다.

이전 강좌에서 배운 바에 따르면 레퍼런스라는 것이 어떤 변수의 다른 별명이라고 했습니다.

그런데 그 별명을 리턴한다니 무슨말일까요?

레퍼런스를 리턴하는 함수를 알아보기위해 간단한 예제를 한번 살펴보도록 합시다.

# 레퍼런스를 리턴하는 함수

```cpp
#include <iostream>

class A {
	private:
		int x;
	public:
		A(int c) : x(c) {}
	int &access_x() { return x; }
	int get_x() { return x;}
	void show_x() { std::cout << x << std::endl; } 
};

int main() {
	A a(5);
	a.show_x();

	int &c = a.access_x();
	c = 4;
	a.show_x();

	int d = a.access_x();
	d = 3;
	a.show_x();

	// 아래는 오류
	// int &e = a.get_x();
	// e = 2;
	// a.show_x();
	int f = a.get_x();
	f = 1;
	a.show_x();
}
```

위의 코드를 실행시키면 다음과 같은 결과가 나옵니다.

```
5
4
4
4
```

일단 위 클래스 A는 아래와 같이 int와 int의 레퍼런스를 리턴하는 두개의 함수를 가지고 있습니다.

```cpp
int &access_x() {return x;}
int get_x() {return x;}
```

access_x는 x의 레퍼런스를 리턴하게 되고 get_x는 x의 값을 리턴하게 됩니다.

실제로 이들이 어떻게 작동하는지 살펴보도록 하겠습니다.

``` cpp
	int &c = a.access_x();
	c = 4;
	a.show_x();
```

여기서 레퍼런스 c는 x의 레퍼런스 즉, x의 별명을 받았습니다.

따라서 c는 x의 별명으로 탄생하게 되는 것이지요

레퍼런스를 리턴하는 함수는 그 함수의 원래의 변수로 치환했다고 생각해도 상관이 없습니다.

다시 말해서 다음과 같습니다. 

``` cpp
int &c = x;
```

따라서 c의 값을 바꾸는 것은 a의 x의 값을 바꾸는 것과 동일한 의미이므로 (c는 단순히 x에 다른 이름을 붙여준 것일 뿐) show_x를 실행 시에 x의 값이 5에서 4로 바뀌었음을 알 수 있습니다.

그렇다면 아래의 예도 살펴봅시다.

```cpp
int d = a.access_x();
d = 3;
a.show_x();
```

이번에는 int &가 아닌 그냥 int 변수에 x의 별명을 전달하였습니다.

만일 d가 int &였다면 x의 별명을 받아서 d 역시 또 다른 x의 별명이 되었겠지만 d가 그냥 int 변수이므로 값의 복사가 일어나 d에는 x의 값이 들어가게 됩니다.

그리고 당연히 d는 x의 별명이 아닌 또 다른 독립적인 변수 이기에 d = 3;을 해도 x의 값은 바뀌지 않은 채 그냥 4가 출력되게 되죠.

그럼 주석처리된 예시를 살펴봅시다.

```cpp
	 int &e = a.get_x();
	 e = 2;
	 a.show_x();
```

주석을 풀고 실행시키면 다음과 같은 에러가 발생합니다.

```
ret_reference.cpp:26:8: error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
```

그 이유는 레퍼런스가 아닌 타입을 리턴하는 경우 값의 복사가 이루어지기 때문에 임시 객체가 생성되는데 임시 객체의 레퍼런스를 가질 수 없기 때문입니다. (임시 객체는 함수가 종료되면 소멸됩니다.)

get_x의 리턴으로 인해 임시로 '복사 생성' 된 int는 a.get_x()부분을 대체하며 다음과 같이 되는데

```cpp
int &e = x;
```

x는 문장이 끝날 때 자동으로 소멸되는 임시 객체이기 대문에 레퍼런스를 만들 수 없습니다.

설사 레퍼런스를 만들었다고 해도 이미 존재하지 않는 것에 대한 별명이 되므로 이 레퍼런스에 접근하는 것은 정상적이지 않을 것입니다.

아무튼 이러한 이유로 int를 리턴하는 a.get_x에 대해서는 레퍼런스를 만들 수 없습니다.

정확한 설명을 하자면 int &은 좌측 값에 대한 레퍼런스이고 a.get_x()는 우측 값이기 때문에 레퍼런스를 만들 수 없습니다.

```cpp
int f = a.get_x();

f = 1;
a.show_x();
```

마지막으로 위 코드는 익히 보았던 것 처럼 임시로 생성된 int 변수 (위 그림에서는 x)가 f에 복사되는데 역시 f = 1 한 것이 실제 객체 a의 x에게는 아무런 영향을 끼칠수 없습니다.

한가지 재미있는 점은 `a.access_x() = 3` 이 잘 동작한다는 점인데, 앞에서도 말했지만 레퍼런스를 리턴하는 함수는 그 함수 부분을 리턴하는 원래 변수로 치한해도 된다라는 말이 정확히 들어맞는 다는 점입니다.

즉, `a.access_x() = 3`는 결국 다음과 같습니다.

```
a.x = 3;
```

그에 반면, 잘 알고있듯이 다음 문장은 에러가 발생합니다.

```
a.get_x() = 3;
```

왜냐하면 a.get_x()는 get_x()가 리턴하면서 생성되는 임시 객체 x로 치환되며 임시 객체에 대입하게 되는 모순적인 상황이 발생하게 됩니다.

그럼 이제 다시 예전의 Marine 예제로 돌아가 보도록 합시다

```cpp
Marine &Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
	return *this;
}
```

위 경우 be_attacked 함수는 Marine & 타입을 리턴하게 되는데, 위 경우 *this를 리턴하게 됩니다.

앞에서도 말했지만 this가 지금 이 함수를 호출한 객체를 가리키게 됩니다.

즉, *this는 그 객체 자신을 의미하게 됩니다.

```cpp
marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
```

위 문장의 경우 먼저 marine2.be_attacked(marine1.attack())이 먼저 실행되고 리턴되는 것이 다시 marine2 이므로 그 다음에 또 한번 marine2.be_attacked(marine1.attack())가 실행된다고 할 수 있습니다.

만일 be_attacked 함수의 리턴 타입이 Marine &이 아니라 그냥 Marine 이라고 해봅시다.

즉, 만일 be_attacked 함수가 아래와 같이 바뀌었다고 가정한다면

```cpp
Marine Marine::be_attacked(int damage_earn) {
	this->hp -= damage_earn;
	if (this->hp <= 0)
		this->is_dead = true;

	return *this;
}
```

위로 바뀐 함수를 가지고 다음을 실행해보면 Marine2는 실제로 두번공격이 아닌 1번 공격으로 감소한 HP만을 보입니다.

```cpp
marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
```

이는 앞에서도 설명했듯이 리턴타입이 Marine이므로, 임시 객체 Marine을 생성해서 *this의 내용으로 복사가 되고 (즉, Marine의 복사 생성자 호출)이 임시 객체에 대한 be_attacked 함수가 호출하게 되는 것입니다.

따라서 결국 두 번째 be_attacked는 marine2가 아닌 엉뚱한 임시 객체에 대해 호출되는 것이므로 결국 marine2는 marine1의 공격을 한번만 받게됩니다.

# const 함수

C++에서는 변수들의 값을 바꾸지 않고 읽기만 하는, 마치 상수 같은 멤버 함수를 상수 함수로써 선언할 수 있습니다.

```cpp
#include <iostream>

class Marine {
	private:
		static int total_marine_num;
		const static int i = 0;

		int hp;
		int coord_x, coord_y;
		const int default_damage;
		bool is_dead;
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);
		~Marine() { total_marine_num--; }

		int attack() const;
		Marine &be_attacked(int damage_earn);
		void move(int x, int y);

		void show_status();
		static void show_total_marine();
};

int Marine::total_marine_num = 0;

Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
		total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
	:	coord_x(x),
		coord_y(y),
		hp(50),
		default_damage(default_damage),
		is_dead(false) {
			total_marine_num++;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() const { return default_damage; }

Marine &Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0)
		is_dead = true;
	return *this;
}

void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	Marine::show_total_marine();
}
int main() {
	Marine marine1(2, 3, 5);
	Marine::show_total_marine();

	Marine marine2(3, 5, 10);
	Marine::show_total_marine();
	create_marine();

	std::cout << std::endl << "마린 1이 마린 2를 두번 공격! " << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
}
```

성공적으로 컬파일 하였다면 다음과 같이 나옵니다.

```
전체 마린 수 : 1
전체 마린 수 : 2
전체 마린 수 : 3

마린 1이 마린 2를 두번 공격! 
 *** Marine *** 
 Location : ( 2 , 3 ) 
 HP : 50
 현재 총 마린 수 : 2
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 40
 현재 총 마린 수 : 2
```

위 코드는 거의 바뀐 것은 없고 단순히 예시를 위해 아래와 같이 attack 함수를 살짝 바꾸었습니다.

```cpp
int attack() const;
```

일단 상수 함수는 위와 같은 형태로 선언하게 됩니다.

```cpp
(기존의 함수 정의) const;
```

그리고 함수의 정의 역시 const 키워드를 꼭 넣어주어야 합니다.

```cpp
int Marine::attack() const { return default_damage; }
```

위와 같이 하게되면 attack 함수는 '상수 멤버 함수'로 정의된 것입니다.

우리는 상수 함수로 이 함수를 정의함으로써 이 함수는 다른 변수의 값을 바꾸지 않는 함수라고 다른 프로그래머에게 명시 시킬 수 있습니다.

당연하게도 상수 함수 내에서는 객체들의 '읽기' 만이 수행되며 상수 함수 내에서 호출할 수 있는 함수로는 다른 상수 함수 밖에 없습니다.

사실 많은 경우 클래스를 설계할 때, 멤버 변수들은 모두 private에 넣고, 이 변수들은 값을 접근하는 방법으로 get_X 함수 처럼 함수를 public에 넣어 이 함수를 이용해 값을 리턴받는 형식을 많이 사용합니다.

이렇게 하면 멤버 변수들을 private에 넣음으로써 함부로 변수에 접근하는 것을 막고 또 그 값은 자유롭게 구할 수 있게 됩니다.
