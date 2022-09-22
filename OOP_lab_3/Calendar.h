#ifndef _CALENDAR_
#define _CALENDAR_

class Calendar {
private:
	int month_array[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int day;
	int month;
	int year;
public:
	Calendar();
	Calendar(int day, int month, int year);
	Calendar(const Calendar& calendar);
	void set_day(int day);
	void set_month(int month);
	void set_year(int year);
	void set_date(int day, int month, int year);
	int get_day();
	int get_month();
	int get_year();

	//не включая конечную дату
	Calendar operator-(int days);
	Calendar operator+(int days);
	int operator-(Calendar calendar1);
	bool operator> (Calendar& c2);
	bool operator< (Calendar& c2);
	bool operator>= (Calendar& c2);
	bool operator<= (Calendar& c2);
	bool operator==(Calendar& c2);
	bool operator!=(Calendar& c2);

	friend int operator-(const Calendar& calendar2, Calendar calendar1);

	// операции сравнения
	friend bool operator> (const Calendar& c1, const Calendar& c2);
	friend bool operator< (const Calendar& c1, const Calendar& c2);
	friend bool operator>= (const Calendar& c1, const Calendar& c2);
	friend bool operator<= (const Calendar& c1, const Calendar& c2);
	friend bool operator==(const Calendar& c1, const Calendar& c2);
	friend bool operator!=(const Calendar& c1, const Calendar& c2);

	
};

Calendar::Calendar() {
	this->set_date(1, 1, 1970);
}
Calendar::Calendar(int day, int month, int year) {
	this->set_date(day, month, year);
}
Calendar::Calendar(const Calendar& calendar) {
	this->set_date(calendar.day, calendar.month, calendar.year);
}
void Calendar::set_day(int day) {
	if (day < 1 && day > 31) {
		this->day = 1;
		std::cerr << "incorrect value" << std::endl;
	}
	else {
		this->day = day;
	}
}
void Calendar::set_month(int month) {
	if (month < 1 && month > 12) {
		this->month = 1;
		std::cerr << "incorrect value" << std::endl;
	}
	else {
		this->month = month;
	}
}
void Calendar::set_year(int year) {
	this->year = year;
}
void Calendar::set_date(int day, int month, int year) {
	this->set_day(day);
	this->set_month(month);
	this->set_year(year);
}
int Calendar::get_day() {
	return this->day;
}
int Calendar::get_month() {
	return (this->month);
}
int Calendar::get_year() {
	return this->year;
}

//не включая конечную дату
Calendar Calendar::operator-(int days) {
	Calendar temp = (*this);
	while (days > 0) {
		if (temp.year % 4 == 0) {
			temp.month_array[1] = 29;
			if (temp.year % 100 == 0 && temp.year % 400 != 0) {
				temp.month_array[1] = 28;
			}
		}
		else {
			temp.month_array[1] = 28;
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
			temp.day = temp.month_array[temp.month - 1];
		}

	}
	return temp;
}
Calendar Calendar::operator+(int days) {
	Calendar temp = (*this);
	while (days > 0) {
		if (temp.year % 4 == 0) {
			temp.month_array[1] = 29;
			if (temp.year % 100 == 0 && temp.year % 400 != 0) {
				temp.month_array[1] = 28;
			}
		}
		else {
			temp.month_array[1] = 28;
		}
		int temp_days = days;
		days -= temp.month_array[temp.month - 1] - temp.day;
		temp.day += temp_days;
		if (temp.day > temp.month_array[temp.month - 1]) {
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
int Calendar::operator-(Calendar calendar1) {
	Calendar temp = (*this);
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
bool Calendar::operator> (Calendar& c2) {
	if (this->year > c2.year) return true;
	else if (this->year < c2.year) return false;
	else if (this->month > c2.month) return true;
	else if (this->month < c2.month) return false;
	else if (this->day > c2.day) return true;
	else if (this->day < c2.day) return false;
	else return false;
}
bool Calendar::operator< (Calendar& c2) {
	if (this->year < c2.year) return true;
	else if (this->year > c2.year) return false;
	else if (this->month < c2.month) return true;
	else if (this->month > c2.month) return false;
	else if (this->day < c2.day) return true;
	else if (this->day > c2.day) return false;
	else return false;
}
bool Calendar::operator>= (Calendar& c2) {
	if ((*this) == c2) return true;
	if ((*this) > c2) return true;
	return false;
}
bool Calendar::operator<= (Calendar& c2) {
	if ((*this) == c2) return true;
	if ((*this) < c2) return true;
	return false;
}
bool Calendar::operator==(Calendar& c2) {
	if (this->year == c2.year && this->month == c2.month && this->day == c2.day) return true;
	return false;
}
bool Calendar::operator!=(Calendar& c2) {
	if (this->year != c2.year || this->month != c2.month || this->day != c2.day) return true;
	return false;
}


#endif // !_CALENDAR_
