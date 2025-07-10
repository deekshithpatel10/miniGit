#include "index.hpp" 
#include "object.hpp"
#include "utils.hpp" 
#include <fstream> 

bool add_to_index(const std::string& filepath) {
   std::string content = read_file(filepath); 
   std::string hash = hash_blob(content); 
   std::ofstream indexFile(".miniGit/index", std::ios::app); 
   indexFile << filepath << " " << hash << "\n"; 
   return true; 
}

void write_index() {
   // don't forget this
}