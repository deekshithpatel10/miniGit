#include "command.hpp"
#include "repository.hpp"
#include "utils.hpp"
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string> 

void handle_command(int argc, char* argv[]) {
   if(argc < 2) {
      std::cout << "Usage: miniGit <command> [args]\n"; 
      return; 
   }

   std::string cmd = argv[1]; 

   if(cmd == "init") {
      if(init_repository())
         std::cout << "Initialized empty miniGit repository in .miniGit/\n"; 
      else std::cout << "Repo already initialized.\n"; 
   } else {
      std::cerr << "Unknown or incomplete command.\n"; 
   }
}