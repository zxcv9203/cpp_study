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