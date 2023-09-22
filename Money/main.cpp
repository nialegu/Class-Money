#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <cstring>
#include <string.h>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;

class money {
private:
	long double value;
public:
	money() : value(0) {}
	explicit money(long double m) : value(m) {} 

	long double mstold(char[]); //money string to long double
	void ldtoms(long double); //long double to money string

	void get_money() {
		char str[19];
		cout << "Enter a count of money: "; cin >> str;
		mstold(str);
	}
	void put_money() {
		ldtoms(value);
	}

	money operator+(money) const;
	money operator-(money) const;
	money operator*(long double) const;
	money operator/(long double) const;
	long double operator/(money) const;
};

int main() {
	money a, b, c;
	long double time_oneitem, item_counter;
	cout << "1: "; a.get_money();
	cout << "2: "; b.get_money();

	c = a + b; cout << "1st$ + 2nd$ = "; c.put_money();
	c = a - b; cout << "1st$ - 2nd$ = "; c.put_money();
	cout << "Time for one item: "; cin >> time_oneitem;
	c = a * time_oneitem; cout << "Total price for one item per entered time: "; c.put_money();
	cout << "Count of products: "; cin >> item_counter;
	c = a / item_counter; cout << "Price for one item: "; c.put_money();
	item_counter = a / c; cout << "Count of products: " << item_counter;
	
	return 0;
}

money money::operator+(money m2) const {
	long double m = value + m2.value;
	return money(m);
}

money money::operator-(money m2) const {
	long double m = value - m2.value;
	return money(m);
}

money money::operator*(long double t) const {
	long double m = value * t;
	return money(m);
}

money money::operator/(long double c) const {
	long double m = value / c;
	return money(m);
}

long double money::operator/(money m2) const {
	long double c = value / m2.value;
	return c;
}

void money::ldtoms(long double m) {
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

long double money::mstold(char m[]) {
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