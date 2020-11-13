#include <iostream>
#include "files_tree/tree.h"
#include "files_tree/workers.h"


int main(int argc, char* argv[]){
    using std::string;
    using file_treat::tree_node;
    using file_treat::tree_builder;
    using file_treat::file_walker;

    if (argc > 1){
        string path{argv[1]};

        tree_node *r = tree_builder::get_instance()
                .build_node(nullptr,path);
        file_walker::get_instance().visit(*r);
        delete r;

    }
    return 0;
}
