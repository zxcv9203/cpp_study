#include <iostream>

class Point {
	private:
		int x, y;
	public:
		Point(int pos_x, int pos_y);
		int GetX() const;
		int GetY() const;
};

int Point::GetX() const { return x; }
int Point::GetY() const { return y; }

class Geometry {
	private:
		Point *point_array[100];
		int num_points;
	public:
		Geometry();
		void AddPoint(const Point &point);
		void PrintDistance();
		void PrintNumMeets();
};

Geometry::Geometry() {
	num_points = 0;
}

void Geometry::AddPoint(const Point &point) {
	point_array[num_points++] = new Point(point.GetX(), point.GetY());
}