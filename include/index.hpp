#ifndef INDEX_HPP
#define INDEX_HPP

#include <string> 
#include <map> 

bool add_to_index(const std::string& filepath); 
void write_index(); 
std::map<std::string, std::string> read_index(); 

#endif