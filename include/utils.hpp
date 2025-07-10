#ifndef UTILS_HPP
#define UTILS_HPP

#include <string> 

bool create_dir(const std::string& path); 
bool write_file(const std::string& path, const std::string& content); 
std::string read_file(const std::string& path); 
bool file_exists(const std::string& path); 

#endif