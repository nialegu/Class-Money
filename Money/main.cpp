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
	money(long double m) : value(m) {}

	long double mstold(char []); //money string to long double
	void ldtoms(long double); //long double to money string

	void get_money() {
		char str[19];
		cout << "Enter a count of money: "; cin >> str;
		mstold(str);
	}
	void put_money() {
		ldtoms(value);
	}

	/*money operator+(money);
	money operator-(money);
	money operator*(money);
	money operator/(long double);
	long double operator/(money);*/
};

int main() {
	money a, b;
	a.get_money();
	a.put_money();

	return 0;
}

void money::ldtoms(long double m) {
	if (m > 9999999999999990.00) exit(1);

	ostringstream mstr;
	mstr << fixed << setprecision(2) << m;
	
	char ms[27] = "$";
	int count, j=0, c=0;

	for (int i = 0; i < 19; i++) {
		if (mstr.str().c_str()[i] != '.') c++;
		else break;
	}
	count = 3 - c % 3;
	if (count == 3) count = 0;

	ms[26] = '\0'; // don't forget add \0 element to the character's array end - this is very important!
	for (int i = 0; i < 18; i++) {
		if (count != 3) {
			ms[i + 1 + j] = mstr.str().c_str()[i];
			count++;
		}
		else if (count == 3 && mstr.str().c_str()[i] != '.') {
			ms[i + 1 + j] = ',';
			j++;
			ms[i + 1 + j] = mstr.str().c_str()[i];
			count = 1;
		}
		else if (count == 3 && mstr.str().c_str()[i] == '.') {
			count = 0;
			ms[i + 1 + j] = mstr.str().c_str()[i];
		}
	}
	cout << ms << endl;
}

long double money::mstold(char m[]) {
	char mvd[19];
	int j=0;
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