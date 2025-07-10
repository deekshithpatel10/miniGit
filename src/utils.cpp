#include "utils.hpp"
#include <filesystem>
#include <fstream> 
#include <sstream> 
#include <openssl/sha.h>
#include <iomanip> 

bool create_dir(const std::string& path) {
   return std::filesystem::create_directories(path); 
}

bool write_file(const std::string& path, const std::string& content) {
   std::ofstream file(path); 
   if(!file) return false; 
   file << content; 
   return true; 
}

std::string read_file(const std::string& path) {
   std::ifstream file(path); 
   std::ostringstream ss; 
   ss << file.rdbuf(); 
   return ss.str(); 
}

bool file_exists(const std::string& path) {
   return std::filesystem::exists(path); 
}

std::string compute_sha1(const std::string& data) {
   unsigned char hash[SHA_DIGEST_LENGTH]; 
   SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash); 
   std::ostringstream result; 
   for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
      result << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i]; 
   }
   return result.str(); 
}

