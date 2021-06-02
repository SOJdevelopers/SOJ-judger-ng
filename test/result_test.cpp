#include "../result.h"
#include <iostream>

int main() {
	using namespace SOJ_JUDGER_NAMESPACE;
	RunResult _rs;
	Result * rs = (Result*) &_rs;
	std::cout << rs->loadFromFile("result.txt") << '\n';
	std::cout << rs->getType() << ' ' << rs->getUsedTime() << ' ' << rs->getUsedMemory() << '\n';
	rs->failedResult();
	std::cout << rs->getType() << ' ' << rs->getUsedTime() << ' ' << rs->getUsedMemory() << '\n';
	return 0;
}
