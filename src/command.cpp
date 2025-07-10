#include "command.hpp"
#include "repository.hpp"
#include "index.hpp"
#include "object.hpp"
#include "utils.hpp"
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string> 

void handle_command(int argc, char* argv[]) {
   if(argc < 2) {
      std::cout << "Usage: minigit <command> [args]\n"; 
      return; 
   }

   std::string cmd = argv[1]; 

   if(cmd == "init") {
      if(init_repository())
         std::cout << "Initialized empty miniGit repository in .miniGit/\n"; 
      else std::cout << "Repo already initialized.\n"; 
   } else if(cmd == "add" && argc == 3) {
      add_to_index(argv[2]); 
   } else if(cmd == "commit" && argc ==3) {
      std::string message; 
      for(int i = 2; i < argc; i++) message += argv[i]; 
      write_commit(message); 
   } else {
      std::cerr << "Unknown or incomplete command.\n"; 
   }
}