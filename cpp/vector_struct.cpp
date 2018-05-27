#include <iostream>
#include <vector>

struct types {
	int a;
	double e;
};

int main()
{
	std::vector<struct types> s;

	// types() is a constructor
	s.push_back(types());

	s[0].a = 10;
	s[0].e = 10.4;

	s.push_back(types());

	s[1].a = 4;
	s[1].e = 4.4;

	std::vector<struct types>::const_iterator i;

	for (i = s.begin(); i != s.end(); i ++) {
		std::cout << "a:" << (*i).a << std::endl;
		std::cout << "e:" << (*i).e << std::endl;
	}

	return 0;
}

