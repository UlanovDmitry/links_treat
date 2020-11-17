#include "tree.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <filesystem>

#include "services.h"

namespace file_treat{

using std::string;
namespace fs = std::filesystem;


// tree_node
tree_node::tree_node(tree_node* prnt, string path):_path(path),_prnt(prnt) {
    fs::path p(path);
    if(fs::exists(p)){
        this->_filename = p.filename().string();
        this->_ext = p.extension().string();
    }
    if(prnt != nullptr){
        _l = prnt->get_l()+1;
    } else {
        _l = 0;
    }
    _indent = "";
    for(int i=0; i<_l; i++) _indent+="\t";
}


// file_node
// TODO: надо как-то по другому вернуть пустой массив
vector<tree_node*>& file_node::files(){
    vector<tree_node*> *f = new vector<tree_node*>{};
    return *f;
}


// dir_node
dir_node::dir_node(tree_node* prnt, string path)
    :tree_node(prnt,path){
    for (const auto& e: fs::directory_iterator(path) ){
        tree_builder& tb = tree_builder::get_instance();
        tree_node* f = tb.build_node(this,e.path().string());
        if (f != nullptr){
            this->_files.push_back(f);
        }
    }
}

} // namespace file_treat
