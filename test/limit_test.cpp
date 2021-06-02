#include "../limit.h"
#include <iostream>

int main() {
	using namespace SOJ_JUDGER_NAMESPACE;
	RunLimit rl(1, 2, 3, 4);
	std::cout << rl.getTime() << ' ' << rl.getRealtime() << ' ' << rl.getMemory() << ' ' << rl.getOutput() << std::endl;
	rl.setTime(233).setRealtime(234).setMemory(235).setOutput(114514);
	std::cout << rl.getTime() << ' ' << rl.getRealtime() << ' ' << rl.getMemory() << ' ' << rl.getOutput() << std::endl;
	rl = RunLimit::JUDGER;
	std::cout << rl.getTime() << ' ' << rl.getRealtime() << ' ' << rl.getMemory() << ' ' << rl.getOutput() << std::endl;
}
