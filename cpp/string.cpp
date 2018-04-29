#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s = "Hello";
	int len;
	char first, last;

	first = s.at(0);
	len = s.length();

	last = s.at(len - 1);

	cout << "length " << len << " size " << s.size() << " max size " << s.max_size() <<endl;
	cout << "first character " << first <<endl;
	cout << "last character " << last <<endl;
	cout << "front " << s.front() << " back " << s.back() <<endl;

	s.append(" C++");

	cout << "final string " << s <<endl;

	s = s + " from MacOS";
	cout << s <<endl;
}

