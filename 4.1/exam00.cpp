#include <iostream>

class Date{
	private :
		int year_;
		int month_;
		int day_;
	public :
		void SetDate(int year, int month, int date) {
			year_ = year;
			month_ = month;
			day_ = date;
		}
		void AddDay(int inc) {
			day_ += inc;
		}
		void AddMonth(int inc) {
			month_ += inc;
		}
		void AddYear(int inc) {
			year_ += inc;
		}
		void ShowDate() {
			std::cout << year_ << month_ << day_ << std::endl;
		}
};

int main() {
	Date date;

	date.SetDate(1,1,1);
	date.ShowDate();
	date.AddDay(5);
	date.ShowDate();
	date.AddMonth(3);
	date.ShowDate();
	date.AddYear(450);
	date.ShowDate();

}
