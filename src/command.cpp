#include "command.hpp"
#include "repository.hpp"
#include "index.hpp"
#include "object.hpp"
#include "utils.hpp"
#include "restore.hpp"
#include "checkout.hpp"
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string> 

void print_log() {
   std::string hash = get_head_commit();
   while (!hash.empty()) {
      std::string content = read_file(".miniGit/objects/" + hash);
      std::istringstream ss(content);
      std::string line, parent;

      // Read optional parent line
      std::getline(ss, line);
      if (starts_with(line, "parent ")) {
         parent = line.substr(7);
         std::getline(ss, line); // move to next line (date)
      } else {
         parent = "";
      }

      std::string date = line;
      std::getline(ss, line); // message
      std::string message = line;

      std::cout << "commit " << hash << "\n    " << message << "\n    " << date << "\n\n";
      hash = parent;
   }
}

void show_status() {
   std::map<std::string, std::string> idx = read_index();
   std::cout << "Staged files:\n";
   for (auto& [file, hash] : idx) std::cout << "    " << file << "\n";
}

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
   } else if (cmd == "log") {
      print_log();
   } else if (cmd == "status") {
      show_status();
   } else if (cmd == "restore" && argc == 3) {
      std::string arg = argv[2];
   if (arg == "--staged") {
         restore_staged_files();
      } else {
         restore_file(arg);
      }
   } else if (cmd == "restore" && argc == 4 && std::string(argv[2]) == "--commit") {
      restore_from_commit(argv[3], "Restore from commit " + std::string(argv[3]));
   } else if (cmd == "checkout" && argc == 3) {
      checkout_commit(argv[2]);
   } else {
      std::cerr << "Unknown or incomplete command.\n"; 
   }
}