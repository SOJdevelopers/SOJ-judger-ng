#include "../config.h"
#include <iostream>

int main() {
	using namespace SOJ_JUDGER_NAMESPACE;
	Config conf;
	conf.loadFromFile("problem.conf");
	std::cout << "DEBUG: " << conf["subtask"]["dependence"]["2"]["1"].getDouble() << std::endl;
	conf["subtask"]["dependence"]["2"]["2"].set(998244353.123);
	std::cout << conf << std::endl;
	return 0;
}
