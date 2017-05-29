#include "dataref_files.h"

#include "XPLMUtilities.h"

#include <boost/algorithm/string.hpp>

std::vector<std::string> loadBlacklistFile(const boost::filesystem::path & filename) {
    std::vector<std::string> entries;
    std::ifstream f(filename.string());
    if(f.fail()) {
        std::string no_file_message = std::string("DRT: Failed to open blacklist file at ") + filename.string();
        XPLMDebugString(no_file_message.c_str());
        return {};
    }
    
    std::string line;
    while(std::getline(f, line)) {
        size_t first_hash = line.find("#");
        line = line.substr(0, first_hash);
        boost::algorithm::trim(line);
        
        entries.emplace_back(std::move(line));
    }
    {
        std::string loaded_message = std::string("DRT: Loaded blacklist with ") + std::to_string(entries.size()) + " entries\n";
        XPLMDebugString(loaded_message.c_str());
    }
    
    return entries;
}

std::vector<std::string> loadDatarefsFile(const boost::filesystem::path & filename) {
    std::string dr_path_message = "DRT: Loading datarefs from path " + filename.string() + "\n";
    XPLMDebugString(dr_path_message.c_str());
    
    std::ifstream dr_file(filename.string());
    
    if(dr_file.bad()) {
        XPLMDebugString("DRT: DataRefs.txt file could not be loaded\n");
        return {};
    }
    
    std::string line;
    std::getline(dr_file, line);	//discard header
    std::vector<std::string> datarefs;
    while(std::getline(dr_file, line)) {
        size_t tab_offset = line.find('\t');
        if(tab_offset == std::string::npos) {
            continue;
        }
        
        line.erase(line.begin() + tab_offset, line.end());
        datarefs.emplace_back(std::move(line));
    }
    
    {
        std::string dr_count_message = "DRT: Finished loading " + std::to_string(datarefs.size()) + " datarefs" + "\n";
        XPLMDebugString(dr_count_message.c_str());
    }
    
    return datarefs;
}