/*
 * This program will compute the duration in days between two dates excluding the end date
 * The date format should be: mm/dd/yyyy
 * This program assumes the given strings match the format
 */

#include <iostream>
#include <sstream>
#include <string>

class DateDuration {
	private:
		struct Date {
			int day, month, year;
			bool operator<(Date &b) {
				if (this->year != b.year)
					return this->year < b.year;
				if (this->month != b.month)
					return this->month < b.month;
				return this->day < b.day;
			}
		};

		static int days[12];

		static bool isLeap(int year) {
			if (year % 400 == 0)
				return true;
			if (year % 100 == 0)
				return false;
			return year % 4 == 0;
		}

		static Date parseDate(std::string s) {
			Date d;
			d.month = stoi(s.substr(0, 2));
			d.day   = stoi(s.substr(3, 2));
			d.year  = stoi(s.substr(6, 4));
			return d;
		}

		static int daysBetweenMonth(int m1, int m2, int y) {
			int ans = 0;
			for (int i=m1; i<=m2; i++)
				ans += i==2 ? (isLeap(y) ? 29 : 28) : days[i-1];
			return ans;
		}

		static int computeDuration(Date &a, Date &b) {
			int ans = 0;
			/* compute the days of the years in between a and b */
			for (int i=a.year+1; i<b.year; i++)
				ans += isLeap(i) ? 366 : 365;
			/* compute the days in the duration of the year a and b */
			if (a.year == b.year)
				ans += daysBetweenMonth(a.month, b.month-1, a.year);
			else
				ans += daysBetweenMonth(a.month, 12, a.year) + daysBetweenMonth(1, b.month-1, b.year);
			ans = ans - a.day + b.day;
			return ans;
		}

	public:
		static int computeDuration(std::string s1, std::string s2) {
			Date d1 = parseDate(s1);
			Date d2 = parseDate(s2);
			if (d1 < d2)
				return computeDuration(d1, d2);
			else
				return computeDuration(d2, d1);
		}
};

int DateDuration::days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "ERROR usage: ./a.out date1 date2" << std::endl;
		return -1;
	}
	std::cout << "There are " << DateDuration::computeDuration(argv[1], argv[2]) << " days between " << argv[1] << " and " << argv[2] << ", excluding the end date." << std::endl;
	return 0;
}
