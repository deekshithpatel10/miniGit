#include "repository.hpp"
#include "utils.hpp"
#include "object.hpp"
#include "index.hpp"
#include <fstream> 
#include <sstream> 
#include <map> 

bool init_repository() {
   if(file_exists(".miniGit")) {
      return false;  //Repo already exists 
   }

   // create .miniGit directories 
   create_dir(".miniGit"); 
   create_dir(".miniGit/objects"); 
   create_dir(".miniGit/refs");
   create_dir(".miniGit/refs/heads"); 
   write_file(".miniGit/HEAD", "ref: refs/heads/master"); 
   write_file(".miniGit/refs/heads/master", ""); 
   write_file(".miniGit/index", ""); 

   return true; 
}

std::map<std::string, std::string> read_index() {
   std::ifstream file(".miniGit/index"); 
   std::map<std::string, std::string> result; 
   std::string line; 
   while(std::getline(file, line)) {
      std::istringstream iss(line); 
      std::string file, hash; 
      iss >> file >> hash; 
      result[file] = hash; 
   }
   return result;
}