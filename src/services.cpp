#include "services.h"
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
file_walker::file_walker(){
    _wrk = new worker();
}
file_walker::~file_walker(){
    delete _wrk;
}
file_walker& file_walker::configure(string path){
    _wrk = new worker_md_maker(_wrk);
    _wrk = new worker_ini_parser(_wrk);
    _wrk = new worker_res_accum(_wrk,path);
    return get_instance();
}
void file_walker::visit(tree_node& n){
    _wrk->work(n);
    if(n.is_dir()){
        for(auto f: n.files()){
            visit(*f);
        }
    }
}


} // namespace file_treat
