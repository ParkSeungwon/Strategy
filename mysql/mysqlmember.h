#pragma once
#include <string>
#include "member.h"
#include "mysqlquery.h"

class MysqlMember : public Member, public Mysqlquery
{
 public:
	bool read(std::string _id);//email주소를 아이디로 사용함.
	void write();
	bool exist(std::string _email);
    bool login(std::string user, std::string pass);
    bool writeFollow(std::string email, std::string follower, bool secret);
};


