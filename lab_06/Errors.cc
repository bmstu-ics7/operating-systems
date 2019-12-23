#include "Errors.h"
#include <iostream>

void mutexError()
{
	std::cerr << "Can't create mutex" << std::endl;
	exit(-1);
}

void eventError()
{
	std::cerr << "Can't create event" << std::endl;
	exit(-2);
}

void threadError()
{
	std::cerr << "Can't create thread" << std::endl;
	exit(-3);
}