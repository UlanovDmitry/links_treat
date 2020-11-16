#include "workers.h"
#include <string>
#include <iostream>

namespace file_treat {

using std::string;


// worker_wrap
void worker_wrap::work(tree_node& n){_w->work(n);}
worker_wrap::~worker_wrap(){ delete _w; }


// worker_logger
void worker_logger::work(tree_node& n){
    string pref = n.is_dir()? "[] ": "- ";
    std::cout<<n.indent()<<pref<<n.filename()<<std::endl;
    worker_wrap::work(n);
}


} // namespace file_treat
