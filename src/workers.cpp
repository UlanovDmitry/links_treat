#include "workers.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace file_treat {

namespace fs = std::filesystem;

using std::string;
using fs::path;

// worker_wrap
void worker_wrap::work(tree_node& n){_w->work(n);}
worker_wrap::~worker_wrap(){ delete _w; }


// worker_logger
void worker_logger::work(tree_node& n){
    worker_wrap::work(n);
    string pref = n.is_dir()? "[] ": "- ";
    std::cout<<n.indent()<<pref<<n.filename()<<std::endl;
}


// worker_ini_parser
void worker_ini_parser::work(tree_node& n){
    worker_wrap::work(n);
    if (n.is_url()){
        using boost::property_tree::ptree;
        ptree pt;
        read_ini(n.path(), pt);
        for (auto& section : pt){
            for (auto& key : section.second){
                n.set_url(key.second.get_value<std::string>());
                break;
            }
            break;
        }
    }
}


// worker_md_maker
worker_md_maker::worker_md_maker(worker* w, string pth): worker_wrap(w){
    path p(pth);
    p+=".md";
    _f.open(p);
}
worker_md_maker::~worker_md_maker(){
    _f.close();
}
void worker_md_maker::work(tree_node& n){
    worker_wrap::work(n);
    if (n.is_dir()){
        string idt = "";
        for(int i=0; i<n.get_l(); i++){
            idt += "#";
        }
        _f<<idt<<" "<<n.filename()<<std::endl;
    } else if (n.url().length()>0) {
        _f<<"["<<n.filename()<<"]"
                <<"("<<n.url()<<")"
               <<std::endl;
    }
}


// worker_res_accum
worker_res_accum::worker_res_accum(worker* w, string path): worker_wrap(w){
    _path = path+"_files";          // определяемся с путём к папке
    fs::create_directories(_path);  // создаём папку, если не было
    _f.open(path+"_files.log");     // открываем на запись файл логов
}
worker_res_accum::~worker_res_accum(){
    _f.close();
}
void worker_res_accum::work(tree_node& n){
    worker_wrap::work(n);
    if (!n.is_dir() && !n.is_url()){
        _f<<n.path()<<std::endl;
        path p = path(_path) / n.filename();  // копируем файл в специальную папку
        fs::copy_file(path(n.path()),p);
    }
}


} // namespace file_treat
