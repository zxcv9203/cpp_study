#include <iostream>

class Date {
	private:
		int year_;
		int month_;
		int day_;

	public:
		void AddDay(int inc);
		void AddMonth(int inc);
		void AddYear(int inc);

		// 해당 월의 총 일 수를 구합니다.
		int GetCurrentMonthTotalDays(int year, int month);

		void ShowDate();
		Date();
		Date(int year, int month, int day);
};

Date::Date() {
	year_ = 2021;
	month_ = 10;
	day_ = 17;	
}

Date::Date(int year, int month, int day) {
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month) {
	static int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month != 2) {
		return month_day[month - 1];
	} else if (year % 4 == 0 && year % 100 != 0) {
		return 29;
	} else {
		return 28;
	}
}

void Date::AddDay(int inc) {
	while (true) {
		int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);
		if (day_ + inc <= current_month_total_days) {
			day_ += inc;
			return ;
		} else {
			inc -= (current_month_total_days - day_ + 1);
			day_ = 1;
			AddMonth(1);
		}
	}
}

void Date::AddMonth(int inc) {
	AddYear((inc + month_ - 1) / 12);
	month_ = month_ + inc % 12;
	month_ = (month_ == 12 ? 12 : month_ % 12);
}

void Date::AddYear(int inc) { year_ += inc; }

void Date::ShowDate() {
	std::cout << "오늘은" << year_ << " 년 " << month_ << " 월 " << day_ << " 일 입니다 " << std::endl;
}

int main() {
	Date date1;
	Date date2(1,1,1);
	date1.ShowDate();
	date2.ShowDate();

	return 0;
}