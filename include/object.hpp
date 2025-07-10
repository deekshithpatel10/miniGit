#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string> 

std::string hash_blob(const std::string& content);
std::string write_commit(const std::string& message); 
std::string get_head_commit(); 

#endif 