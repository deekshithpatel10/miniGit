#ifndef RESTORE_HPP
#define RESTORE_HPP

#include <string> 

bool restore_file(const std::string& filepath); 
bool restore_staged_files(); 
bool restore_from_commit(const std::string& commit_hash, const std::string& message); 

#endif