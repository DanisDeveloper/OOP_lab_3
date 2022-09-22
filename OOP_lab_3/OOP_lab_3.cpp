#include <iostream>
#include<string>
#include"Calendar.h"

int operator-(const Calendar& calendar2, Calendar calendar1);

bool operator> (const Calendar& c1, const Calendar& c2);
bool operator< (const Calendar& c1, const Calendar& c2);
bool operator>= (const Calendar& c1, const Calendar& c2);
bool operator<= (const Calendar& c1, const Calendar& c2);
bool operator==(const Calendar& c1, const Calendar& c2);
bool operator!=(const Calendar& c1, const Calendar& c2);

std::ostream& operator<<(std::ostream& os, Calendar& calendar);

void check(const Calendar& c1, const Calendar& c2, int index_c1, int index_c2);

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
	check(calendar1, calendar1, 1, 1);
	std::cout << "Calendar 2: " << calendar2 << std::endl;
	check(calendar1, calendar2, 1, 2);
	std::cout << "Calendar 3: " << calendar3 << std::endl;
	check(calendar1, calendar3, 1, 3);
	std::cout << "Calendar 4: " << calendar4 << std::endl;
	check(calendar1, calendar4, 1, 4);
	std::cout << "Calendar 5: " << calendar5 << std::endl;
	check(calendar1, calendar5, 1, 5);
	std::cout << "Calendar 6: " << calendar6 << std::endl;
	check(calendar1, calendar6, 1, 6);
	std::cout << "Calendar 7: " << calendar7 << std::endl;
	check(calendar1, calendar7, 1, 7);
	std::cout << "Calendar 8: " << calendar8 << std::endl;
	check(calendar1, calendar8, 1, 8);
	std::cout << "Calendar 9: " << calendar9 << std::endl;
	check(calendar1, calendar9, 1, 9);
}

int operator-(const Calendar& calendar2, Calendar calendar1) {
	Calendar temp = calendar2;
	if (temp < calendar1)
		std::swap(temp, calendar1);
	int days = 0;
	if (temp.month != calendar1.month) days += calendar1.month_array[calendar1.month - 1] - calendar1.day;
	else days += abs(temp.day - calendar1.day);
	while (temp.month != calendar1.month) {
		days += temp.day;
		if (temp.month == 1) {
			temp.month = 12;
			temp.year--;
		}
		else {
			temp.month--;
		}
		temp.day = temp.month_array[temp.month - 1];
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
	char delimiter = '.';
	return os << calendar.get_day() << delimiter << calendar.get_month() << delimiter << calendar.get_year();
}

void check(const Calendar& c1, const Calendar& c2, int index_c1, int index_c2) {
	std::cout << "Difference " << index_c1 << "-" << index_c2 << ": " << (c1 - c2) << " days" << std::endl;
	std::cout << "Difference " << index_c2 << "-" << index_c1 << ": " << (c2 - c1) << " days" << std::endl;
	std::cout << "c" << index_c1 << " == c" << index_c2 << ": " << std::boolalpha << (c1 == c2) << std::endl;
	std::cout << "c" << index_c1 << " != c" << index_c2 << ": " << std::boolalpha << (c1 != c2) << std::endl;
	std::cout << "c" << index_c1 << " >= c" << index_c2 << ": " << std::boolalpha << (c1 >= c2) << std::endl;
	std::cout << "c" << index_c1 << " <= c" << index_c2 << ": " << std::boolalpha << (c1 <= c2) << std::endl;
	std::cout << "c" << index_c1 << " > c" << index_c2 << ": " << std::boolalpha << (c1 > c2) << std::endl;
	std::cout << "c" << index_c1 << " < c" << index_c2 << ": " << std::boolalpha << (c1 < c2) << std::endl;
	std::cout << std::endl;
}
