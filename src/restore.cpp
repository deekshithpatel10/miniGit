#include "restore.hpp"
#include "utils.hpp"
#include "object.hpp"
#include "index.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

bool restore_file(const std::string& filepath) {
   auto index = read_index();
   if (index.find(filepath) == index.end()) {
   std::cerr << "File not found in index: " << filepath << "\n";
   return false;
   }
   std::string hash = index[filepath];
   std::string content = read_file(".miniGit/objects/" + hash);
   return write_file(filepath, content);
}

bool restore_staged_files() {
   auto index = read_index();
   for (auto& [file, hash] : index) {
      std::string content = read_file(".miniGit/objects/" + hash);
      write_file(file, content);
      std::cout << "Restored: " << file << "\n";
   }
   return true;
}

bool restore_from_commit(const std::string& commit_hash, const std::string& message) {
   std::string commit_path = ".miniGit/objects/" + commit_hash;
   if (!file_exists(commit_path)) {
      std::cerr << "Commit not found: " << commit_hash << "\n";
      return false;
   }

   std::string content = read_file(commit_path);
   std::istringstream ss(content);
   std::string line;

   // Skip parent and date lines (max 2)
   int skipped = 0;
   while (std::getline(ss, line)) {
      if ((line.rfind("parent ", 0) == 0 || line.rfind("date ", 0) == 0) && skipped < 2) {
         skipped++;
         continue;
      }
      break;
   }

   // Current line is message — skip it
   // (It's okay if it's blank or multiple lines of msg)
   while (line.find(' ') == std::string::npos && std::getline(ss, line));

   std::map<std::string, std::string> temp_index;

   // Remaining lines are file-hash pairs
   do {
      std::istringstream pair(line);
      std::string file, hash;
      if (pair >> file >> hash) {
         std::string file_content = read_file(".miniGit/objects/" + hash);
         write_file(file, file_content);
         temp_index[file] = hash;
         std::cout << "Restored: " << file << "\n";
      }
   } while (std::getline(ss, line));

   // Rewrite index with these file entries
   std::ofstream idx(".miniGit/index");
   for (auto& [file, hash] : temp_index)
      idx << file << " " << hash << "\n";

   // Commit this state
   write_commit(message);

   return true;
}
