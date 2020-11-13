#include "workers.h"
#include "tree.h"

#include <string>
#include <filesystem>
#include <iostream>

namespace file_treat {

using std::string;
namespace fs = std::filesystem;

// tree_builder
tree_node* tree_builder::build_node(tree_node* prnt, string path){
    if (fs::exists(path)) {
        if (fs::is_directory(path)) {
            return new dir_node(prnt,path);
        } else {
            return new file_node(prnt,path);
        }
    } else {
        return nullptr;
    }
}

// file_walker
void file_walker::visit(tree_node& f){
    if(f.is_dir()){
        std::cout<<f.indent()<<"[+] "<<f.filename()<<std::endl;
        for(auto f: f.files()){
            visit(*f);
        }
    } else {
        std::cout<<f.indent()<<"+ "<<f.filename()<<std::endl;
    }
}



} // namespace file_treat
