#include <iostream>

#include "BitMap.h"

int main(void)
{
	BitMap bitMap{ 100, {1, 2, 3} };
	std::cout << bitMap.test(1) << bitMap.test(2) << bitMap.test(3) << std::endl;
	bitMap.reset(1);
	std::cout << bitMap.test(1) << bitMap.test(2) << bitMap.test(3) << std::endl;
	bitMap.reset(2);
	std::cout << bitMap.test(1) << bitMap.test(2) << bitMap.test(3) << std::endl;
	bitMap.reset(3);
	std::cout << bitMap.test(1) << bitMap.test(2) << bitMap.test(3) << std::endl;
	bitMap.set(15);
	std::cout << bitMap.test(1) << bitMap.test(2) << bitMap.test(3)  << bitMap.test(15) << std::endl;

	std::cin.get();
	return 0;
}