#include "checkout.hpp"
#include "utils.hpp"
#include "object.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

bool checkout_commit(const std::string& commit_hash) {
   std::string path = ".miniGit/objects/" + commit_hash;
   if (!file_exists(path)) {
      std::cerr << "Commit not found: " << commit_hash << "\n";
      return false;
   }

   std::string content = read_file(path);
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

   // Skip commit message
   while (line.find(' ') == std::string::npos && std::getline(ss, line));

   // Remaining lines = file hash pairs
   std::map<std::string, std::string> index_entries;
   do {
      std::istringstream iss(line);
      std::string file, hash;
      if (iss >> file >> hash) {
         std::string file_content = read_file(".miniGit/objects/" + hash);
         write_file(file, file_content);
         index_entries[file] = hash;
         std::cout << "Checked out: " << file << "\n";
      }
   } while (std::getline(ss, line));

   // Update HEAD to point directly to this commit
   write_file(".miniGit/HEAD", commit_hash);

   // Rewrite index
   std::ofstream idx(".miniGit/index");
   for (auto& [file, hash] : index_entries)
      idx << file << " " << hash << "\n";

   return true;
}
