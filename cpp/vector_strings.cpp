#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> str;

	// add at the tail
	str.push_back("Hello -> 1");
	str.push_back("Hello -> 2");
	str.push_back("Hello -> 3");

	int i;
	// iteration from 0 to size
	for (i = 0; i < str.size(); i ++) {
		std::cout << str[i] << std::endl;
	}

	// using constant iterator
	std::vector<std::string>::const_iterator it;
	for (it = str.begin(); it != str.end(); it ++) {
		std::cout << *it << std::endl;
	}

	// reverse read
	std::vector<std::string>::reverse_iterator ri;
	for (ri = str.rbegin(); ri != str.rend(); ri ++) {
		std::cout << *ri << std::endl;
	}

	return 0;
}

