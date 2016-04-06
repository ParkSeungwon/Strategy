#include <string>
#include <vector>
#include "../tcpip.h"

class GameServer
{
public:
	std::string operator()(std::string s);

protected:
	std::vector<std::string> logged_ids;
};


