#include "object.hpp"
#include "utils.hpp"
#include <string> 

std::string hash_blob(const std::string& content) {
   std::string hash = compute_sha1(content); 
   std::string path = ".miniGit/objects/" + hash; 
   write_file(path, content); 
   return hash; 
}