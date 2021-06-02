#include "../info.h"
#include <iostream>

int main() {
	using namespace SOJ_JUDGER_NAMESPACE;
	{
	PointInfo t(1, 2, 3, 4, "5", "6", "7", "8");
	std::cout << t.getStatus() << '\n';
	t.setStatus("123");
	std::cout << t.getStatus() << '\n';
	}
	{
	CustomTestInfo t(1, 2, "3", "4", "5");
	std::cout << t.getStatus() << '\n';
	t.setStatus("123");
	std::cout << t.getStatus() << '\n';
	}
}
