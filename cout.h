//class that deals with custom output
#include <iostream>
class Cout : public std::ostream 
{
public :
//	template <typename T>
//	std::ostream operator<<(T s) {std::cout << s; return std::cout;}
};
