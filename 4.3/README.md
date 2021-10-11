# 복사 생성자 & 소멸자

이전에 생성자를 통해 변수 초기화를 하지 않아 생길수 있는 수많은 문제를 효과적으로 없앨 수 있었습니다.

그리고 함수 오버로딩 덕분에 함수 이름을 일일히 따로 지정하지 않더라도 성공적으로 인자들의 타입에 따라 원하는 함수들만 호출할 수 있게 되었습니다.

## 스타크래프트 만들기

스타크래프트라는 거대한 프로젝트를 진행하기에 앞서 일단, 유닛 하나 부터 만들어 보도록 할 것입니다.

스타크래프트의 마린이라는 유닛을 코드상에서 한번 구현해 보겠습니다.

``` cpp
#include <iostream>

class Marine {
	private:
		int hp;						// 체력
		int coord_x, coord_y;		// 마린 위치
		int damage;					// 공격력
		bool is_dead;
	public:
		Marine();					// 기본 생성자
		Marine(int x, int y);		// x, y 좌표에 마린 생성
		int attack();				// 데미지를 리턴합니다.
		void be_attacked(int damage_earn);	//입는 데미지
		void move(int x, int y);			// 새로운 위치

		void show_status();					// 상태를 보여줍니다.
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
}

Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
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

성공적으로 컴파일 하였다면 잘 실행될 것입니다.

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
 HP : 45
```

코드를 한번 살펴봅시다.

``` cpp
class Marine {
	private:
		int hp;						// 체력
		int coord_x, coord_y;		// 마린 위치
		int damage;					// 공격력
		bool is_dead;
	public:
		Marine();					// 기본 생성자
		Marine(int x, int y);		// x, y 좌표에 마린 생성
		int attack();				// 데미지를 리턴합니다.
		void be_attacked(int damage_earn);	//입는 데미지
		void move(int x, int y);			// 새로운 위치

		void show_status();					// 상태를 보여줍니다.
};
```

위는 마린을 구현한 클래스입니다.

즉, 위 클래스의 객체들이 바로 개개의 마린이 되는 것입니다.

이전 강좌에서도 이야기 하였지만, 보통 어떠한 객체의 내부적 성질, 상태등에 관련된 변수들은 모두 `private` 범주에 두고, 그 객체가 외부에 하는 행동들은 함수로써 구현하여 `public`에 두면 된다고 하였습니다.

그렇다면 마린의 경우, 마린의 상태에 관련된 현재 hp, 위치, 공격력, 생존여부 등은 `private` 범주에 두어서 관리하고, 마린이 하는 행동과 관련된 이동, 공격, 외부로 받는 공격 등은 메서드로 만들어서 `public` 범주에 두어 관리하면 좋습니다.

따라서 위와 같이 코드를 구성하였습니다.

이제 main 함수의 코드들을 살펴보도록 합시다.

``` cpp
Marine marine1(2, 3);
Marine marine2(3, 5);
```

먼저, 위 두개의 marine1과 marine2 라는 이름의 Marine 개게들을 생성하였습니다.

물론 생성자 오버로딩에 의해 각각 (2, 3), (3, 5)에 위치한 마린들이 생성되었습니다.

```cpp
marine1.show_status();
marine2.show_status();
```

이제 위 함수들을 통해서 각각의 마린의 상태를 출력한 뒤에, 마린 2가 마린 1로부터 공격을 받는 상황을 그렸습니다.

```cpp
std::cout << std::endl << "마린 1이 마린 2를 공격!" << std::endl;
marine2.be_attacked(marine1.attack());
```

그런데 사실 위 코드는 약간의 문제가 있습니다.

만약에 실제 게임에서 처럼 수십마리의 마린들이 서로 뒤엉켜서 싸우면 어떻게 될까요?

그럴때는 marine1, marine2와 같이 일일히 이름 붙이기도 벅찰 뿐더러, 사용자가 몇 개의 마린을 만들겠다라고 컴파일 시점에 정해버리는 것도 아니기 때문에 수십개의 marine1, marine2를 미리 만들 수 도 없는 격입니다.

그럼 어떻게 해야 할까요?

답은 단순합니다. marine 들을 배열로 정해버리면 됩니다.

```cpp
int main() {
	Marine *marines[100];
	
	marines[0] = new Marine(2, 3);
	marines[1] = new Marine(3, 5);

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격!" << std::endl;

	marines[0]->be_attacked(marines[1]->attack());
	
	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];
}
```

예전에 new와 delete에 대해서 배울 때 `malloc` 과의 차이점에 대해서 잠깐 언급 했던 것이 기억나나요?

그 때는 아직 내용을 다 배우지 못해서, new와 malloc 모두 동적으로 할당하지만 '무언가' 다르다고 했었는데 위 코드에서 여러분들은 아마 눈치 채셨을 것이라 생각됩니다.

바로 new의 경우 객체를 동적으로 생성하면서와 동시에 자동으로 생성자도 호출해준다는 점입니다.

``` cpp
	marines[0] = new Marine(2, 3);
	marines[1] = new Marine(3, 5);
```

위와 같이 Marine(2, 3)와 Marine(3, 5)라는 생성자를 자동으로 호출해줍니다.

이것이 바로 C++에 맞는 새로운 동적할당이라고 볼 수 있습니다.

```cpp
	marines[0]->show_status();
	marines[1]->show_status();
```

물론 Marine 들의 포인터를 가리키는 배열이기 때문에 메소드를 호출할 때 .이 아리날 ->를 사용해 주어야 합니다.

마지막으로, 동적으로 할당한 메모리는 언제나 해제해 주어야 된다는 원칙에 따라 delete로 해제해주어야 합니다.

``` cpp
delete marines[0];
delete marines[1];
```

## 소멸자(Destructor)

알고보니 각각의 마린에도 이름을 지정할 수 있었습니다.

그래서 우리는 만들어놓은 Marine 클래스에 name 이라는 이름을 저장할 수 있는 또 다른 인스턴스 변수를 추가하도록 합시다.

``` cpp
#include <iostream>
#include <string.h>

class Marine {
	private:
		int hp;						// 체력
		int coord_x, coord_y;		// 마린 위치
		int damage;					// 공격력
		bool is_dead;
		char *name;					// 마린 이름
	public:
		Marine();					// 기본 생성자
		Marine(int x, int y);		// x, y 좌표에 마린 생성
		Marine(int x, int y, const char *marine_name);		// 이름까지 지정
		int attack();				// 데미지를 리턴합니다.
		void be_attacked(int damage_earn);	//입는 데미지
		void move(int x, int y);			// 새로운 위치

		void show_status();					// 상태를 보여줍니다.
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y, const char *marine_name) {
	name = new char[strlen(marine_name) + 1];
	strcpy(name, marine_name);
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() {
	Marine *marines[100];
	
	marines[0] = new Marine(2, 3);
	marines[1] = new Marine(3, 5);

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격!" << std::endl;

	marines[0]->be_attacked(marines[1]->attack());
	
	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];
}
```

실행해보면 결과가 잘 나오는 것을 볼 수 있습니다.

그런데 사실 위 코드에는 또다른 문제점이 있습니다.

``` cpp
Marine::Marine(int x, int y, const char *marine_name) {
	name = new char[strlen(marine_name) + 1];
	strcpy(name, marine_name);
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}
```

우리는 분명히 위 코드에서 name에 생성하는 마린의 이름을 넣어줄 때, name을 동적으로 생성해서 문자열을 복사했는데요

그럼 이렇게 동적으로 할당된 char 배열에 대한 delete는 언제 이루어지는 것인가요?

안타깝게도, 우리가 명확히 delete를 지정하지 않는 한 자동으로 delete가 되는 경우는 없습니다.

다시 말해서 우리가 동적으로 할당했던 저 name은 영원히 메모리 공간 속에서 둥둥 떠다닌다는 말이지요

사실 하나는 몇 바이트 밖에 되지 않지만, 쌓이다 보면 메모리 누수라는 문제점이 발생하게 됩니다.

그렇다면 main 함수 끝에서 Marine이 delete 될 때, 즉 우리가 생성했던 객체가 소멸 될 때 자동으로 호출되는 함수, 마치 객체가 생성될 때 자동으로 호출되었던 생성자 처럼 소멸 될 때 자동으로 호출되는 함수가 있다면 얼마나 좋을까요?

놀랍게도 C++에서는 이 기능을 지원하고 있는데 바로 소멸자입니다.

``` cpp
#include <iostream>
#include <string.h>

class Marine {
	private:
		int hp;						// 체력
		int coord_x, coord_y;		// 마린 위치
		int damage;					// 공격력
		bool is_dead;
		char *name;					// 마린 이름
	public:
		Marine();					// 기본 생성자
		Marine(int x, int y);		// x, y 좌표에 마린 생성
		Marine(int x, int y, const char *marine_name);		// 이름까지 지정
		~Marine();

		int attack();				// 데미지를 리턴합니다.
		void be_attacked(int damage_earn);	//입는 데미지
		void move(int x, int y);			// 새로운 위치

		void show_status();					// 상태를 보여줍니다.
};

Marine::Marine() {
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y, const char *marine_name) {
	name = new char[strlen(marine_name) + 1];
	strcpy(name, marine_name);
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

Marine::~Marine() {
	std::cout << name << " 의 소멸자 호출 !" << std::endl;
	if (name != NULL) {
		delete []name;
	}
}

int main() {
	Marine *marines[100];
	
	marines[0] = new Marine(2, 3, "Marine 2");
	marines[1] = new Marine(3, 5, "Marine 1");

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "마린 1이 마린 2를 공격!" << std::endl;

	marines[0]->be_attacked(marines[1]->attack());
	
	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];
}
```

성공적으로 컴파일 하였다면 다음과 같이 잘 출력됩니다.

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
 HP : 45
 *** Marine *** 
 Location : ( 3 , 5 ) 
 HP : 50
Marine 2 의 소멸자 호출 !
Marine 1 의 소멸자 호출 !
```

생성자가 클래스 이름과 똑같이 생겼다면 소멸자는 그 앞에 ~ 만 붙여주면 됩니다.

```
~(class name)
```

예를들어, Marine 클래스의 소멸자의 경우 다음과 같이 생겼습니다.

```cpp
~Marine();
```

생성자와 한 가지 다른 점은 소멸자는 인자를 아무것도 가지지 않는 다는 것입니다.

생각해보세요. 소멸하는 객체에 인자를 넘겨서 무엇을 하겠습니까?

다시 말해 소멸자는 오버로딩도 되지 않습니다.

우리의 소멸자 내용을 살펴보자면

```cpp
Marine::~Marine() {
	std::cout << name << " 의 소멸자 호출 !" << std::endl;
	if (name != NULL) {
		delete []name;
	}
}
```

위와 같이 name이 NULL이 아닐 경우에 (즉 동적으로 할당이 되었을 경우에)만 delete로 name을 삭제하는 것을 알 수 있습니다.

참고로 name 자체가 char의 배열로 동적할당 하였기 때문에 delete 역시 delete []name, 즉 []를 꼭 써주어야만 합니다.

```cpp
	delete marines[0];
	delete marines[1];
```

객체가 소멸될 때 소멸자가 호출된다고 출력된다고 출력하도록 했는데, 실제로 위 코드가 실행 시 소멸자 호출 메시지가 뜬다는 것을 확인할 수 있습니다.

```cpp
#include <string.h>
#include <iostream>

class Test {
	private:
		char c;
	public:
		Test(char _c) {
			c = _c;
			std::cout << "생성자 호출" << c << std::endl;
		}
		~Test() {std::cout << "소멸자 호출" << c << std::endl; }
};

void simple_function() { Test b('b'); }

int main() {
	Test a('a');
	simple_function();
}
```

성공적으로 컴파일 하였다면 다음과 같이 출력합니다.

```
생성자 호출a
생성자 호출b
소멸자 호출b
소멸자 호출a
```

위 코드를 보면서 "객체가 파괴될 때 호출되는 소멸자'를 확실하게 확인할 수 있었을 것입니다.

``` cpp
class Test {
	private:
		char c;
	public:
		Test(char _c) {
			c = _c;
			std::cout << "생성자 호출" << c << std::endl;
		}
		~Test() {std::cout << "소멸자 호출" << c << std::endl; }
};
```

Test 클래스는 매우 간단한데, 생성자와 소멸자 호출 때 어떤 객체의 것이 호출되는지 확인하기 위해 char c를 도입 하였습니다.

``` cpp
int main() {
	Test a('a');
	simple_function();
}
```

일단 가장 먼저 main 함수에서 a 객체를 생성하였으므로 a의 생성자가 호출됩니다.

그리고 simple_function을 실행하게 되면

``` cpp
void simple_function() { Test b('b'); }
```

simple_function 안에서 또 b 객체를 생성하므로 b의 생성자가 호출되지요 하지만 b는 simple_function의 지역 객체이기 때문에 simple_function이 종료됨과 동시에 b 역시 소멸되게 됩니다.

따라서 끝에서 b의 소멸자가 호출됩니다.

``` cpp
int main() {
	Test a('a');
	simple_function();
}
```

simple_function 호출 후, 이제 main 함수가 종료될 때 마찬가지로 main 함수의 지역 객체였던 a가 소멸되면서 a의 소멸자가 호출됩니다.

이제 출력결과를 이해할 수 있게 되었습니다.

소멸자가 뭐 별거 있어 라고 생각하는 분들도 있겠지만, 사실은 소멸자의 역할은 상당히 중요합니다.

이세상에 태어나는일이 중요한 일이지만 그 보다 더 중요한 일은 이 세상을 떠날 때 얼마나 깔끔하게 떠나는지가 더욱 중요한 일이 듯이, 객체가 다른 부분에 영향을 끼치지 않도록 깔끔하게 소멸되는 일은 매우 중요한 일입니다.

소멸자가 하는 가장 흔한 역할은 위에서도 나타나 있지만, 객체가 동적으로 할당받은 메모리를 해제하는 일이라고 볼 수 있습니다.

그외에도 스레드 사이에서 lock 된 것을 푸는 역할이라던지 등의 역할을 수행하게 됩니다.

참고로 우리가 따로 생성자를 정의하지 않더라도 디폴트 생성자가 있었던 것 처럼, 소멸자도 디폴트 소멸자가 있습니다.

물론 디폴트 소멸자 내부에선 아무런 작업도 수행하지 않습니다.

만일 소멸자가 필요없는 클래스라면 굳이 소멸자를 따로 써줄 필요는 없습니다.

## 복사 생성자

만약 수십개의 객체를 생성하고 싶을 때는 어떻게 할까요?

하나하나 생성할 수도 있지만 1개만 생성해 놓고 그 한개를 가지고 복사생성을 하는 방법도 있습니다.

``` cpp
#include <string.h>
#include <iostream>

class Photo_cannon {
	private:
		int hp, shield;
		int coord_x, coord_y;
		int damage;
	public:
		Photo_cannon(int x, int y);
		Photo_cannon(const Photo_cannon &pc);

	void show_status();
};

Photo_cannon::Photo_cannon(const Photo_cannon &pc) {
	std::cout << "복사 생성자 호출 !" << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
}

Photo_cannon::Photo_cannon(int x, int y) {
	std::cout << "생성자 호출 !" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}

void Photo_cannon::show_status() {
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() { 
	Photo_cannon pc1(3, 3);
	Photo_cannon pc2(pc1);
	Photo_cannon pc3 = pc2;

	pc1.show_status();
	pc2.show_status();
}
```

잘 실행되는 것을 볼 수 있습니다.

먼저 우리가 제작한 복사 생성자(copy constructor)부터 살펴봅시다.

```cpp
		Photo_cannon(const Photo_cannon &pc);
```

사실 위는 복사 생성자의 표준적인 정의라고 볼 수 있습니다.

즉 복사 생성자는 어떤 클래스 T가 있다면 다음과 같은 형태를 지닙니다.

``` cpp
T(const T& a);
```

즉 다른 T의 객체 a를 상수 레퍼런스로 받는 다는 이야기입니다.

여기서 a가 const이기 때문에 우리는 복사 생성자 내부에서 a의 데이터를 변경할 수 없고, 오직 새롭게 초기화되는 인스턴스 변수들에게 '복사'만 할 수 있게 됩니다.

예를들어 

``` cpp
Photo_cannon::Photo_cannon(const Photo_cannon &pc) {
	std::cout << "복사 생성자 호출 !" << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
}
```

위와 같이 복사 생성자 내부에서 pc의 인스턴스 변수들에 접근해서 객체의 shield, coord_x, coord_y 등을 초기화할 수 있지만 값을 직접적으로 변경할 수는 없습니다.

```cpp
pc.coord_x = 3 // 불가능함
```

왜냐하면 const 레퍼런스로 인자를 받았기 때문입니다.

한가지 중요한 점은 함수 내부에서 받은 인자의 값을 변화시키는 일이 없다면 꼭 const를 붙여주시기 바랍니다.

const를 붙인다면 후에 발생할 수 있는 실수를 효과적으로 막을 수 있습니다.

이제 복사 생성자를 실제로 어떻게 이용하는지 살펴보도록 합시다.

``` cpp
	Photo_cannon pc1(3, 3);
	Photo_cannon pc2(pc1);
```

일단 pc1은 int x, int y 인자로 가지는 생성자가 오버로딩 되었고, pc2의 경우 인자로 pc1을 넘겼으므로 복사 생성자가 호출되었음을 알 수 있습니다.

``` cpp
	Photo_cannon pc3 = pc2;
```

그렇다면 위 코드는 어떨까요?

놀랍게도 위 코드 역시 복사 생성자가 호출됩니다.

C++ 컴파일러는 위 문장을 아래와 동일하게 해석합니다.

``` cpp
Photo_cannon pc3(pc2);
```

따라서 복사생성자가 호출되는 것입니다.

물론, 위는 아주아주 특별한 경우입니다.

만일 그냥 `pc 3 = pc2;`를 했다면 이는 평범한 대입 연산이겠지만 생성 시에 대입하는 연산 즉, 위에 같이 `Photo_cannon pc3 = pc2;`를 한다면 복사 생성자가 호출되게 되는 것입니다.

`Photo_cannon pc3 = pc2;`를 컴파일러가 `Photo_cannon pc3(pc2);`로 해석해서 사용자가 상당히 직관적이고 깔끔한 프로그래밍을 할 수 있습니다.

참고로 한가지 더 말하자면

```cpp
Photo_cannon pc3 = pc2;
```

```cpp
Photo_cannon pc3;
pc3 = pc2
```

이 둘은 엄연히 다른 문장입니다.

왜냐하면 위의 것은 말 그대로 복사 생성자가 1번 호출되는 것이고

아래 것은 생성자가 1번 호출되고 pc3 = pc2 라는 명령이 실행되는 것이지요 다시 한번 강조하지만 복사 생성자는 오직 생성시에 호출된다는 것을 명심하면 됩니다.

그런데, 사실 디폴트 생성자와 디폴트 소멸자 처럼 C++ 컴파일러는 이미 디폴트 복사 생성자(Default copy constructor)를 지원해주고 있습니다.

위 코드에서 복사 생성자를 한 번 지워보고 실행해보면 이전과 정확히 동일한 결과가 나타남을 알 수 있습니다.

디폴트 복사 생성자의 경우 기존의 디폴트 생성자와 소멸자가 하는 일이 아무 것도 없었던 것과는 달리 실제로 "복사"를 해줍니다.

만일 우리가 위 Photon_Cannon의 디폴트 생성자의 내용을 추정해 본다면 다음과 같이 생겼을 것입니다.

```cpp
Photo_cannon::Photo_cannon(const Photo_cannon &pc) {
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
}
```

대응되는 원소들을 말 그대로 1대1 복사해주게 됩니다.

따라서 위와 같이 간단한 클래스의 경우 귀찮게 복사 생성자를 써주지 않고도 디폴트 복사 생성자만 이용해서 복사 생성을 쉽게 처리할 수 있습니다.

## 디폴트 복사 생성자의 한계

이번에도 위의 마린 처럼 포토 캐논의 이름을 지어줄 수 있다는 사실을 알고 클래스 Photo_cannon에 char *name을 추가해주었습니다.

그리고 복사 생성자는 그냥 위에서 처럼 디폴트 복사 생성자를 사용하기로 합시다.

```cpp
#include <string.h>
#include <iostream>

class Photo_cannon {
	private:
		int hp, shield;
		int coord_x, coord_y;
		int damage;
		char *name;
	public:
		Photo_cannon(int x, int y);
		Photo_cannon(int x, int y, const char *cannon_name);
		~Photo_cannon();

		void show_status();
};

Photo_cannon::Photo_cannon(int x, int y, const char *cannon_name) {
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = new char[strlen(cannon_name) + 1];
	strcpy(name, cannon_name);
}

Photo_cannon::Photo_cannon(int x, int y) {
	std::cout << "생성자 호출 !" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}

Photo_cannon::~Photo_cannon() {
	if (name)
		delete []name;
}

void Photo_cannon::show_status() {
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() { 
	Photo_cannon pc1(3, 3);
	Photo_cannon pc2(pc1);
	Photo_cannon pc3 = pc2;

	pc1.show_status();
	pc2.show_status();
}
```

컴파일 후 실행해보면 아래와 같은 오류가 발생합니다.

```
free(): double free detected in tcache 2
[1]    8258 abort      ./a.out
```

왜 이런 오류가 발생했을까요?

일단 그럼 디폴트 복사 생성자가 어떻게 생겼는지 살펴보도록 합시다.

아마도 다음과 같이 1대1 복사를 해주고 있을 것입니다.

```cpp
Photo_cannon::Photo_Cannon(const Photo_cannon &pc) {
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
	name = pc.name;
}
```

그렇다면 위 복사 생성자를 호출한 뒤에 pc1과 pc2가 어떻게 되었는지 살펴보도록 합시다.

당연히 모든 멤버 변수가 1대1로 복사가 될 것이고 물론 name도 같은 값을 가지게 될 것입니다.

하지만 name 같은 경우 포인터이기 때문에 값의 메모리 주소를 가리키고 있고 복사되는 값도 실제 값이 아닌 메모리 주소를 가리키게 될 것입니다.

여기서 소멸자가 동적할당 됐던 name을 해제하면 복사한 name은 이미 해제된 포인터를 가르키게 되고 해당 값에 똑같이 소멸자로 접근하려고 할시 double free가 되며 문제가 생깁니다.

이런 증상을 해결하기 위해서는 복사 생성자에서 name을 그대로 복사하지 말고 따로 다른 메모리에 동적 할당을 해서 그 내용만 복사하면 됩니다.

이렇게 메모리를 새로할당해서 내용을 복사하는 것을 깊은 복사(deep copy)라고 부르며 아까 처럼 단순히 대입만 해주는 것을 얕은 복사(shallow copy)라고 부릅니다.

컴파일러가 생성하는 디폴트 복사 생성자의 경우 얕은 복사를 할 수 없으므로 위와 같이 깊은 복사가 필요한 경우에는 직접 복사 생성자를 만들어야 합니다.

다음은 복사 생성자를 직접만들어 깊은 복사를 하도록 하는 코드입니다.

```cpp
#include <string.h>
#include <iostream>

class Photo_cannon {
	private:
		int hp, shield;
		int coord_x, coord_y;
		int damage;
		char *name;
	public:
		Photo_cannon(int x, int y);
		Photo_cannon(int x, int y, const char *cannon_name);
		Photo_cannon(const Photo_cannon &pc);
		~Photo_cannon();

		void show_status();
};

Photo_cannon::Photo_cannon(int x, int y, const char *cannon_name) {
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;

	name = new char[strlen(cannon_name) + 1];
	strcpy(name, cannon_name);
}

Photo_cannon::Photo_cannon(int x, int y) {
	std::cout << "생성자 호출 !" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}

Photo_cannon::Photo_cannon(const Photo_cannon &pc) {
	std::cout << "복사 생성자 호출! " << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
	name = new char[strlen(pc.name) + 1];
	strcpy(name, pc.name);
}

Photo_cannon::~Photo_cannon() {
	if (name)
		delete []name;
}

void Photo_cannon::show_status() {
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

int main() { 
	Photo_cannon pc1(3, 3, "cannon");
	Photo_cannon pc2(pc1);
	Photo_cannon pc3 = pc2;

	pc1.show_status();
	pc2.show_status();
}
```