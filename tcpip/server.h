#include <string>
#include <vector>
#include "tcpip.h"

class GameServer
{
public:
	std::string operator()(std::string s);
	static std::vector<std::string> logged_ids;

protected:
};


