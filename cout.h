//class that deals with custom output
#pragma once
#include <iostream>
class Cout : public std::ostream 
{
public :
	Cout() : std::ostream(std::cout.rdbuf()){}
//	template <typename T>
//	std::ostream operator<<(T s) {std::cout << s; return std::cout;}
} co;
