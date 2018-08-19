#include <iostream>
#include <map>

int main()
{
	std::map <char, int> map;

	map['a'] = 1;
	map['b'] = 2;

	for (std::map<char, int>::iterator it = map.begin(); it != map.end(); it ++) {
		std::cout <<"first : " << it->first << " second : " << it->second << std::endl;
	}

	std::cout << "map[a] :" << map['a'] << std::endl;

	for (std::map<char, int>::const_iterator cit = map.cbegin(); cit != map.cend(); cit ++) {
		std::cout <<"cfirst : " << cit->first << " csecond : " << cit->second << std::endl;
	}

	for (std::map<char, int>::reverse_iterator rit = map.rbegin(); rit != map.rend(); rit ++) {
		std::cout <<"rfirst : " << rit->first << " rsecond : " << rit->second << std::endl;
	}

	std::cout << "map empty ? " << map.empty() << std::endl;

	for (std::map<char, int>::iterator it = map.begin(); it != map.end(); it ++) {
		map.erase(it);
		std::cout << "size of map : " << map.size() << std::endl;
	}

	std::cout << "map empty ? " << map.empty() << std::endl;

	map.insert(std::pair<char, int>('a', 100));
	map.insert(std::pair<char, int>('b', 200));

	for (std::map<char, int>::iterator it = map.begin(); it != map.end(); it ++) {
		std::cout << "first : " << it->first << " second : " << it->second << std::endl;
	}

	return 0;
}

