#pragma once
#include <string>

enum Level {anonymous, registered, regular, representative, senior, root};
	
class Sql_data
{
public:
	static std::string table_name = "Users";
	static unordered_map<std::string, std::string> structure {
		{"email", "char(30) NOT NULL"},
		{"password", "char(45) DEFAULT NULL"},
		{"level", "tinyint(4) DEFAULT NULL"},
		{"name", "varchar(45) DEFAULT NULL"},
		{"tel", "varchar(20) DEFAULT NULL"},
		{"date", "datetime NOT NULL"}
	}
	static std::string extra = "primary key('email', 'date')";
	static std::string engine = "ENGINE=MyISAM DEFAULT CHARSET=utf8";


class Member 
{
 private:
	
 protected:
	std::string email;
	std::string password;
	Level level;
	std::string name;
	std::string tel;
	std::string follow;
    void show();
    
 public:
	std::string contents[];
	Member() {}
	bool auth(std::string _password); //MysqlMember에서 같은 이름의 함수가 있다.
	static bool checkValidEmail(std::string _email);
	std::string setInfo(std::string email, std::string password, Level level, std::string name, std::string tel, std::string follow = "");
    std::string getEmail() {return email;}
    std::string getName() {return name;}
    Level getLevel() {return level;}
    std::string getFollow() {return follow;}
    std::string getTel() {return tel;}
};
