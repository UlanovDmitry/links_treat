#include <iostream>
#include "files_tree/file_treat.h"
#include "files_tree/visitor.h"

using std::string;
using file_treat::IFileWalker;
using file_treat::WalkerBuilder;

int main(int argc, char* argv[]){
    if (argc > 1){
        string path{argv[1]};
        IFileWalker* root = WalkerBuilder::get_instance().build_walker(nullptr,path);
        root->treat();

        file_treat::File_visitor::visit(*root);

        delete root;
    }
    return 0;
}
