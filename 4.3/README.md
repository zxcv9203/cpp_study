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
