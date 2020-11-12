#ifndef VISITOR_H
#define VISITOR_H

#include "file_treat.h"
#include <iostream>

namespace file_treat {

//using std::string;

class File_visitor {
public:
    static void visit(IFileWalker& f){
        if(f.is_dir()){
            std::cout<<f.indent()<<"[+] "<<f.filename()<<std::endl;
            for(auto f: f.files()){
                visit(*f);
            }
        } else {
            std::cout<<f.indent()<<"+ "<<f.filename()<<std::endl;
        }
    }
};



};  // namespace file_treat

#endif // VISITOR_H
