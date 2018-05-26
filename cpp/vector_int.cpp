#include <iostream>
#include <vector>

std::vector<int>::const_iterator searchVector(std::vector<int> a, int element)
{
	std::vector<int>::const_iterator it;

	for (it = a.begin(); it != a.end(); it ++) {
		if (*it == element) {
			return it;
		}
	}
}

int main()
{
	std::vector<int> a;

	if (a.empty()) {
		std::cout << "Vector a is empty" << std::endl;
	}

	std::cout << "elements in vector a:" << a.size() << std::endl;
	std::cout << "capacity:" << a.capacity() << std::endl;
	std::cout << "maxsize:" << a.max_size() << std::endl;

	a.reserve(4);

	std::cout << "new size:" << a.size() << std::endl;

	int i;
	for (i = 0; i < 44; i ++) {
		a.push_back(i);
	}

	std::cout << "new size:" << a.size() << std::endl;

	a.insert(a.begin(), 4);
	for (i = 0; i < a.size(); i ++) {
		std::cout << "a:" << a[i] << std::endl;
	}

	a.insert(a.begin(), 4);

	std::vector<int>::iterator r = a.begin();

	a.erase(r);

	std::cout << "size::->" << a.size() << std::endl;

	// version oerloaded erase
	a.erase(a.begin(), a.end());

	std::cout << "size::->" << a.size() << std::endl;

	return 0;
}

