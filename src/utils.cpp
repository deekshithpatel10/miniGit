#include "utils.hpp"
#include <filesystem>
#include <fstream> 
#include <sstream> 

bool create_dir(const std::string& path) {
   return std::filesystem::create_directories(path); 
}

bool write_file(const std::string& path, const std::string& content) {
   std::ofstream file(path); 
   if(!file) return false; 
   file << content; 
   return true; 
}

std::string read_file(const std::string& path) {
   std::ifstream file(path); 
   std::ostringstream ss; 
   ss << file.rdbuf(); 
   return ss.str(); 
}