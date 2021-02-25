// SkipList.cpp: 定义应用程序的入口点。
//

#include "SkipList.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	SkipList skipList;
	skipList.add(10);
	skipList.add(5);

	skipList.del(5);
	skipList.del(5);

	if (skipList.search(20)) {
		std::cout << "finded " << 20 << std::endl;
	}

	if (skipList.search(5)) {
		std::cout << "finded " << 5 << std::endl;
	}

	return 0;
}
