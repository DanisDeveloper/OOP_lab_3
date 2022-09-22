#include <iostream>
#include<string>

class Calendar {
private:
	class Month {
	public:
		int number;
		int number_of_days;
		Month(int number, int number_of_days = 30) {
			this->number = number;
			this->number_of_days = number_of_days;
		}
	};
	Month month_array[12] = { Month(0,31),
					  Month(1,28),
					  Month(2,31),
					  Month(3,30),
					  Month(4,31),
					  Month(5,30),
					  Month(6,31),
					  Month(7,31),
					  Month(8,30),
					  Month(9,31),
					  Month(10,30),
					  Month(11,31) };
	int day;
	int month;
	int year;
public:
	Calendar() {
		this->set_date(1, 1, 1970);
	}
	Calendar(int day, int month, int year) {
		this->set_date(day, month, year);
	}
	Calendar(const Calendar& calendar) {
		this->set_date(calendar.day, calendar.month, calendar.year);
	}
	void set_day(int day) {
		if (day < 1 && day > 31) {
			this->day = 1;
			std::cerr << "incorrect value" << std::endl;
		}
		else {
			this->day = day;
		}
	}
	void set_month(int month) {
		if (month < 1 && month > 12) {
			this->month = 1;
			std::cerr << "incorrect value" << std::endl;
		}
		else {
			this->month = month;
		}
	}
	void set_year(int year) {
		this->year = year;
	}
	void set_date(int day, int month, int year) {
		this->set_day(day);
		this->set_month(month);
		this->set_year(year);
	}
	int get_day() {
		return this->day;
	}
	int get_month() {
		return (this->month);
	}
	int get_year() {
		return this->year;
	}

	//не включая конечную дату
	Calendar operator-(int days) {
		Calendar temp = (*this);
		while (days > 0) {
			if (temp.year % 4 == 0) {
				temp.month_array[1].number_of_days = 29;
				if (temp.year % 100 == 0 && temp.year % 400 != 0) {
					temp.month_array[1].number_of_days = 28;
				}
			}
			else {
				temp.month_array[1].number_of_days = 28;
			}
			int temp_days = days;
			days -= temp.day;
			temp.day -= temp_days;
			if (temp.day <= 0) {
				if (temp.month == 1) {
					temp.month = 12;
					temp.year--;
				}
				else {
					temp.month--;
				}
				temp.day = temp.month_array[temp.month - 1].number_of_days;
			}

		}
		return temp;
	}
	Calendar operator+(int days) {
		Calendar temp = (*this);
		while (days > 0) {
			if (temp.year % 4 == 0) {
				temp.month_array[1].number_of_days = 29;
				if (temp.year % 100 == 0 && temp.year % 400 != 0) {
					temp.month_array[1].number_of_days = 28;
				}
			}
			else {
				temp.month_array[1].number_of_days = 28;
			}
			int temp_days = days;
			days -= temp.month_array[temp.month - 1].number_of_days - temp.day;
			temp.day += temp_days;
			if (temp.day > temp.month_array[temp.month - 1].number_of_days) {
				if (temp.month == 12) {
					temp.month = 1;
					temp.year++;
				}
				else {
					temp.month++;
				}
				temp.day = 0;
			}
		}
		return temp;
	}
	int operator-(Calendar calendar1) {
		Calendar temp = (*this);
		if (temp < calendar1)
			std::swap(temp, calendar1);

		int days = 0;
		if (temp.month != calendar1.month) days += calendar1.month_array[calendar1.month - 1].number_of_days - calendar1.day;
		else days += abs(temp.day - calendar1.day);
		while (temp.month != calendar1.month) {
			days += temp.day;
			if (temp.month == 1) {
				temp.month = 12;
			}
			else {
				temp.month--;
			}

			temp.day = temp.month_array[temp.month - 1].number_of_days;
		}
		for (int i = temp.year; i != calendar1.year; i--)
		{
			if (i % 4 == 0) {
				days += 366;
				if (i % 100 == 0 && i % 400 != 0) {
					days--;
				}
			}
			else {
				days += 365;
			}
		}
		return days;
	}
	friend int operator-(const Calendar& calendar2, Calendar calendar1);

	// операции сравнения
	friend bool operator> (const Calendar& c1, const Calendar& c2);
	friend bool operator< (const Calendar& c1, const Calendar& c2);
	friend bool operator>= (const Calendar& c1, const Calendar& c2);
	friend bool operator<= (const Calendar& c1, const Calendar& c2);
	friend bool operator==(const Calendar& c1, const Calendar& c2);
	friend bool operator!=(const Calendar& c1, const Calendar& c2);

	bool operator> (Calendar& c2) {
		if (this->year > c2.year) return true;
		else if (this->year < c2.year) return false;
		else if (this->month > c2.month) return true;
		else if (this->month < c2.month) return false;
		else if (this->day > c2.day) return true;
		else if (this->day < c2.day) return false;
		else return false;
	}
	bool operator< (Calendar& c2) {
		if (this->year < c2.year) return true;
		else if (this->year > c2.year) return false;
		else if (this->month < c2.month) return true;
		else if (this->month > c2.month) return false;
		else if (this->day < c2.day) return true;
		else if (this->day > c2.day) return false;
		else return false;
	}
	bool operator>= (Calendar& c2) {
		if ((*this) == c2) return true;
		if ((*this) > c2) return true;
		return false;
	}
	bool operator<= (Calendar& c2) {
		if ((*this) == c2) return true;
		if ((*this) < c2) return true;
		return false;
	}
	bool operator==(Calendar& c2) {
		if (this->year == c2.year && this->month == c2.month && this->day == c2.day) return true;
		return false;
	}
	bool operator!=(Calendar& c2) {
		if (this->year != c2.year || this->month != c2.month || this->day != c2.day) return true;
		return false;
	}
};

int operator-(const Calendar& calendar2, Calendar calendar1) {
	Calendar temp = calendar2;
	if (temp < calendar1)
		std::swap(temp, calendar1);
	int days = 0;
	if (temp.month != calendar1.month) days += calendar1.month_array[calendar1.month - 1].number_of_days - calendar1.day;
	else days += abs(temp.day - calendar1.day);
	while (temp.month != calendar1.month) {
		days += temp.day;
		if (temp.month == 1) {
			temp.month = 12;
		}
		else {
			temp.month--;
		}
		temp.day = temp.month_array[temp.month - 1].number_of_days;
	}
	for (int i = temp.year; i != calendar1.year; i--)
	{
		if (i % 4 == 0) {
			days += 366;
			if (i % 100 == 0 && i % 400 != 0) {
				days--;
			}
		}
		else {
			days += 365;
		}
	}
	return days;
}

bool operator> (const Calendar& c1, const Calendar& c2) {
	if (c1.year > c2.year) return true;
	else if (c1.year < c2.year) return false;
	else if (c1.month > c2.month) return true;
	else if (c1.month < c2.month) return false;
	else if (c1.day > c2.day) return true;
	else if (c1.day < c2.day) return false;
	else return false;
}
bool operator< (const Calendar& c1, const Calendar& c2) {
	if (c1.year < c2.year) return true;
	else if (c1.year > c2.year) return false;
	else if (c1.month < c2.month) return true;
	else if (c1.month > c2.month) return false;
	else if (c1.day < c2.day) return true;
	else if (c1.day > c2.day) return false;
	else return false;
}
bool operator>= (const Calendar& c1, const Calendar& c2) {
	if (c1 == c2) return true;
	if (c1 > c2) return true;
	return false;
}
bool operator<= (const Calendar& c1, const Calendar& c2) {
	if (c1 == c2) return true;
	if (c1 < c2) return true;
	return false;
}
bool operator==(const Calendar& c1, const Calendar& c2) {
	if (c1.year == c2.year && c1.month == c2.month && c1.day == c2.day) return true;
	return false;
}
bool operator!=(const Calendar& c1, const Calendar& c2) {
	if (c1.year != c2.year || c1.month != c2.month || c1.day != c2.day) return true;
	return false;
}
std::ostream& operator<<(std::ostream& os, Calendar& calendar) {
	return os << calendar.get_day() << "." << calendar.get_month() << "." << calendar.get_year();
}

void check(const Calendar& c1, const Calendar& c2) {
	std::cout << "Difference1-2: " << (c1 - c2) << std::endl;
	std::cout << "Difference2-1: " << (c2 - c1) << std::endl;
	std::cout << "c1 == c1: " << std::boolalpha << (c1 == c2) << std::endl;
	std::cout << "c1 != c1: " << std::boolalpha << (c1 != c2) << std::endl;
	std::cout << "c1 >= c1: " << std::boolalpha << (c1 >= c2) << std::endl;
	std::cout << "c1 <= c1: " << std::boolalpha << (c1 <= c2) << std::endl;
	std::cout << "c1 > c1: " << std::boolalpha << (c1 > c2) << std::endl;
	std::cout << "c1 < c1: " << std::boolalpha << (c1 < c2) << std::endl;
}

int main()
{
	Calendar calendar1(10, 3, 2019);
	Calendar calendar2 = calendar1 + 5;
	Calendar calendar3 = calendar1 + 30;
	Calendar calendar4 = calendar1 + 380;
	Calendar calendar5 = calendar1 + 1000;
	Calendar calendar6 = calendar1 - 10;
	Calendar calendar7 = calendar1 - 50;
	Calendar calendar8 = calendar1 - 380;
	Calendar calendar9 = calendar1 - 1000;
	std::cout << "Calendar 1: " << calendar1 << std::endl;
	std::cout << "Difference1-1: " << (calendar1 - calendar1) << std::endl;
	std::cout << "c1 == c1: " << std::boolalpha << (calendar1 == calendar1) << std::endl;
	std::cout << "c1 != c1: " << std::boolalpha << (calendar1 != calendar1) << std::endl;
	std::cout << "c1 >= c1: " << std::boolalpha << (calendar1 >= calendar1) << std::endl;
	std::cout << "c1 <= c1: " << std::boolalpha << (calendar1 <= calendar1) << std::endl;
	std::cout << "c1 > c1: " << std::boolalpha << (calendar1 > calendar1) << std::endl;
	std::cout << "c1 < c1: " << std::boolalpha << (calendar1 < calendar1) << std::endl;
	std::cout << "Calendar 2: " << calendar2 << std::endl;
	std::cout << "Difference1-2: " << (calendar1 - calendar2) << std::endl;
	std::cout << "Difference2-1: " << (calendar2 - calendar1) << std::endl;
	std::cout << "c1 == c2: " << std::boolalpha << (calendar1 == calendar2) << std::endl;
	std::cout << "c1 != c2: " << std::boolalpha << (calendar1 != calendar2) << std::endl;
	std::cout << "c1 >= c2: " << std::boolalpha << (calendar1 >= calendar2) << std::endl;
	std::cout << "c1 <= c2: " << std::boolalpha << (calendar1 <= calendar2) << std::endl;
	std::cout << "c1 > c2: " << std::boolalpha << (calendar1 > calendar2) << std::endl;
	std::cout << "c1 < c2: " << std::boolalpha << (calendar1 < calendar2) << std::endl;
	std::cout << "Calendar 3: " << calendar3 << std::endl;
	std::cout << "Calendar 4: " << calendar4 << std::endl;
	std::cout << "Calendar 5: " << calendar5 << std::endl;
	std::cout << "Calendar 6: " << calendar6 << std::endl;
	std::cout << "Calendar 7: " << calendar7 << std::endl;
	std::cout << "Calendar 8: " << calendar8 << std::endl;
	std::cout << "Calendar 9: " << calendar9 << std::endl;

	std::cout << "Difference5-9: " << (calendar5 - calendar9) << std::endl;
}	

