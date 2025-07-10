#include "repository.hpp"
#include "utils.hpp"
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