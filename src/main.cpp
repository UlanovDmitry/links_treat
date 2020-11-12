#include <iostream>
#include "files_tree/file_treat.h"

using file_treat::IFileWalker;
using file_treat::WalkerBuilder;

int main(void){

    IFileWalker* root = WalkerBuilder::get_instance().build_walker(nullptr,std::string("/opt/links/lang"));
    root->treat(); 
    delete root;

    return 0;
}
