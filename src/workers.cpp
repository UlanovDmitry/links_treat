#include "workers.h"
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

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

// worker_ini_parser
void worker_ini_parser::work(tree_node& n){

    using boost::property_tree::ptree;
    ptree pt;
    read_ini(n.path(), pt);
    for (auto& section : pt){
//        std::cout << '[' << section.first << "]\n";
        for (auto& key : section.second){
            std::cout << key.first << "=" << key.second.get_value<std::string>() << "\n";
            break;
        }
        break;
    }
    worker_wrap::work(n);
}


} // namespace file_treat
