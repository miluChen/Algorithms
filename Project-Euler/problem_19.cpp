/*
 * Counting Sundays: how many Sundays fell on the first of the month during
 * the twentieth century (1 Jan 1901 to 31 Dec 2000)
 * given 1 Jan 1900 was a Monday
 */

#include <iostream>

using namespace std;

class Date {
public:
	int year;
	int month;

	Date(int y, int m): year(y), month(m) {}
	void nextMonth() {
		if (month < 12)
			month += 1;
		else {
			month = 1;
			year += 1;
		}
	}
	int days() {
		// 1, 3, 5, 7, 8, 10, 12 => 31
		// 4, 6, 9, 11 => 30
		// 2 => 28 / 29
		if (month == 1 || month == 3 || month == 5 || month == 7 ||
			month == 8 || month == 10 || month == 12)
			return 31;
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;
		else {
			if (isLeap())
				return 29;
			return 28;
		}
	}
	bool isLeap(void) {
		if (year % 4 != 0)
			return false;
		if ((year % 100 == 0) && (year % 400 != 0))
			return false;
		return true;
	}
};

bool isSunday(int num) {
	return num % 7 == 0;
}

int main() {
	int num = 366;
	Date date(1901, 1);

	int ans = isSunday(num) ? 1 : 0;
	while (date.year <= 2000) {
		num += date.days();
		date.nextMonth();
		ans += isSunday(num) ? 1 : 0;
	}

	cout << ans << endl;
	return 0;
}
