#include "object.hpp"
#include "index.hpp"
#include "utils.hpp"
#include "repository.hpp"
#include <string> 
#include <filesystem>
#include <fstream> 
#include <ctime> 
#include <sstream> 
#include <vector> 

std::string hash_blob(const std::string& content) {
   std::string hash = compute_sha1(content); 
   std::string path = ".miniGit/objects/" + hash; 
   write_file(path, content); 
   return hash; 
}

std::string get_head_commit() {
   if(!file_exists(".miniGit/HEAD")) return ""; 
   std::string ref = read_file(".miniGit/HEAD").substr(5); // 'ref: '
   std::string path = ".miniGit/" + ref; 
   if(!file_exists(path)) return ""; 
   return read_file(path);
}

std::string write_commit(const std::string& message) {
   std::map<std::string, std::string> final_tree; 

   // start with parent tree 
   std::string parent = get_head_commit(); 
   if(!parent.empty()) {
      std::string parent_content = read_file(".miniGit/objects/" + parent); 
      std::istringstream ss(parent_content); 
      std::string line; 
      while(std::getline(ss, line)) {
         if(line.rfind("parent", 0) == 0 || line.rfind("date", 0) == 0) continue; 
         std::istringstream ls(line); 
         std::string file, hash; 
         ls >> file >> hash; 
         final_tree[file] = hash; 
      }
   }

   // if any file in parent is staged, update it 
   // if new files are present, add them 
   auto index = read_index(); 
   for(auto& [file, hash] : index) {
      final_tree[file] = hash; //add or overwrite 
   }

   // if any file in the repo is deleted, remove them from the map 
   std::vector<std::string> to_remove; 
   for(const auto& [file, hash]: final_tree) {
      if(!file_exists(file) && index.find(file)==index.end()) {
         // file doesn't exist in repo and in index 
         to_remove.push_back(file); 
      }
   }
   for(const std::string& file: to_remove) {
      final_tree.erase(file); 
   }

   // build the new commit tree; 
   std::ostringstream tree; 
   for(auto& [file, hash]: final_tree) {
      tree << file << " " << hash << "\n"; 
   }

   // create the commit object 
   std::ostringstream commit; 
   if(!parent.empty()) commit << "parent " << parent << "\n"; 
   time_t now = time(0); 
   commit << "date " << ctime(&now); 
   commit << message << "\n"; 
   commit << tree.str();

   std::string data = commit.str(); 
   std::string hash = compute_sha1(data); 
   write_file(".miniGit/objects/" + hash, data); 

   std::string ref = read_file(".miniGit/HEAD").substr(5); 
   write_file(".miniGit/" + ref, hash); // update latest commit 
   write_file(".miniGit/index", ""); // clear staging area 

   return hash; 
}