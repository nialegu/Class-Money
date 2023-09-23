#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <string.h>
#include <string>
#include <windows.h>
#include <sstream>
#include <math.h>

using namespace std;

class dollars {
private:
	long double value;
public:
	dollars() : value(0) {}
	explicit dollars(long double m) : value(m) {} 

	long double mstold(char[]); //money string to long double
	void ldtoms(long double); //long double to money string

	void get_dollars() {
		char str[19];
		cout << "Enter a count of money: "; cin >> str;
		mstold(str);
	}
	void put_dollars() {
		ldtoms(value);
	}

	dollars operator+(dollars) const;
	dollars operator-(dollars) const;
	dollars operator*(long double) const;
	dollars operator/(long double) const;
	long double operator/(dollars) const;
};

class sterling {
private:
	long pounds;
	int shillings;
	int pence;
public:
	sterling() : pounds(0), shillings(0), pence(0) {}
	sterling(double p) {
		double temp = abs(p - static_cast<int>(p));
		pounds = static_cast<long>(p - temp);
		shillings = static_cast<int>(temp * 20);
		pence = static_cast<int>(temp * 240 - shillings*12);
	}
	sterling(long p, int s, int pn) : pounds(p), shillings(s), pence(pn) {}

	void get_sterling() {
		char dummy_point;
		cout << "Enter a count of sterling (format J*.*.*): J";
		cin >> pounds >> dummy_point >> shillings >> dummy_point >> pence;
		
		if (pounds < 0 || shillings < 0 || pence < 0) {
			cout << "\nIncorrect! Values must to be positive. \nTry again.\n\n";
			get_sterling();
		}
		if (shillings >= 20 || pence >= 12) {
			cout << "\nIncorrect! Shillings can't to be more or equal to 20; pences can't to be more or equal to 12.\n"
				<< "Try again.\n\n";
			get_sterling();
		}
	}

	void put_sterling() const {
		cout << "J" << pounds << "." << shillings << "." << pence << endl;
	}

	sterling operator+(sterling) const;
	sterling operator-(sterling) const;
	sterling operator*(double) const;
	sterling operator/(double) const;
	double operator/(sterling) const;
	operator double();
	operator dollars();
};

int main() {
	sterling s1;
	s1.get_sterling();
	s1.put_sterling();
	dollars d1 = s1;
	d1.put_dollars();

	/*dollars a, b, c;
	long double time_oneitem, item_counter;
	cout << "1: "; a.get_dollars();
	cout << "2: "; b.get_dollars();

	c = a + b; cout << "1st$ + 2nd$ = "; c.put_dollars();
	c = a - b; cout << "1st$ - 2nd$ = "; c.put_dollars();
	cout << "Time for one item: "; cin >> time_oneitem;
	c = a * time_oneitem; cout << "Total price for one item per entered time: "; c.put_dollars();
	cout << "Count of products: "; cin >> item_counter;
	c = a / item_counter; cout << "Price for one item: "; c.put_dollars();
	item_counter = a / c; cout << "Count of products: " << item_counter;*/
	
	return 0;
}

sterling sterling::operator+(sterling s2) const {
	return sterling(double(sterling(pounds, shillings, pence)) + double(s2));
}

sterling sterling::operator-(sterling s2) const {
	return sterling(double(sterling(pounds, shillings, pence)) - double(s2));
}

sterling sterling::operator*(double a) const {
	return sterling(double(sterling(pounds, shillings, pence)) * a);
}

sterling sterling::operator/(double a) const {
	return sterling(double(sterling(pounds, shillings, pence)) / a);
}

double sterling::operator/(sterling s2) const {
	double a = double(sterling(pounds, shillings, pence)) / double(s2);
	return a;
}

sterling::operator double() {
	double s = pounds + static_cast<double>(shillings) / 20 + static_cast<double>(pence) / 240;
	double s_fixed = round(s * 100) / 100;
	return s_fixed;
}

sterling::operator dollars() {
	long double dlrs = 50 * double(sterling(pounds, shillings, pence));
	return dollars(dlrs);
}

dollars dollars::operator+(dollars m2) const {
	long double m = value + m2.value;
	return dollars(m);
}

dollars dollars::operator-(dollars m2) const {
	long double m = value - m2.value;
	return dollars(m);
}

dollars dollars::operator*(long double t) const {
	long double m = value * t;
	return dollars(m);
}

dollars dollars::operator/(long double c) const {
	long double m = value / c;
	return dollars(m);
}

long double dollars::operator/(dollars m2) const {
	long double c = value / m2.value;
	return c;
}

void dollars::ldtoms(long double m) {
	if (m > 9999999999999990.00) exit(1);

	ostringstream mstr;
	mstr << fixed << setprecision(2) << m;

	char ms[27] = "$";
	int cnt, j = 0, c = 0;

	for (int i = 0; i < 19; i++) {
		if (mstr.str().c_str()[i] != '.') c++;
		else break;
	}
	cnt = 3 - c % 3;
	if (cnt == 3) cnt = 0;
	//cout << count << endl;
	ms[26] = '\0'; // don't forget add \0 element to the character's array end - this is very important!
	for (int i = 0; i < 18; i++) {
		if (mstr.str().c_str()[i] == '-') {
			ms[i + 1] = mstr.str().c_str()[i];
			cnt++;
			if (cnt == 3) cnt = 0;
		}
		else if (cnt != 3) {
			ms[i + 1 + j] = mstr.str().c_str()[i];
			cnt++;
		}
		else if (cnt == 3 && mstr.str().c_str()[i] != '.') {
			ms[i + 1 + j] = ',';
			j++;
			ms[i + 1 + j] = mstr.str().c_str()[i];
			cnt = 1;
		}
		else if (cnt == 3 && mstr.str().c_str()[i] == '.') {
			cnt = 0;
			ms[i + 1 + j] = mstr.str().c_str()[i];
		}
	}
	if (ms[1] == '-') {
		char temp;
		temp = ms[0]; ms[0] = ms[1]; ms[1] = temp;
	} // fixing negative number's format for writing 

	cout << ms << endl;
}

long double dollars::mstold(char m[]) {
	char mvd[19];
	int j = 0;
	for (int i = 0; i < 18; i++) {
		if (m[i] == '0' || m[i] == '1' || m[i] == '2' || m[i] == '3' || m[i] == '4' || m[i] == '5' ||
			m[i] == '6' || m[i] == '7' || m[i] == '8' || m[i] == '9' || m[i] == '.') {

			mvd[j++] = m[i];
		}
	}
	mvd[18] = '\0'; //add \0 element to the character's array end is a really important!!!

	value = static_cast<long double>(atof(mvd));
	return value;
}