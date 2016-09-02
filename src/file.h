#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class File
{
public:
	std::vector<std::string> file_names;
	static std::unordered_multimap<int, std::string> getdir(std::string dir);
	void find_all_ext(std::string dir, std::string ext); 
	
protected:

private:
	void find_sub_dirs(std::string dir);
	std::vector<std::string> sub_directory;
	void find_files(std::string dir, std::string ext);
};
