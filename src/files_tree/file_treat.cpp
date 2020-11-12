#include "file_treat.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <filesystem>


// TODO: 
// нужна обертка (декоратор) для расширения ф-циональности 
// - определение типа файла по расширению
// - разбор файлов .url
// - сохранение дерева в формате .md
// можно сделать абстрактную фабрику для построения разных walker-ов
// сортрировка - сначала каталоги, потом файлы, и по алфавиту
// параметр командной строки (путь к папке для обработки)

namespace file_treat{

using std::string;
namespace fs = std::filesystem; 

//
// IFileWalker
//
IFileWalker::IFileWalker(IFileWalker* prnt, string path):_path(path),_prnt(prnt) {
    fs::path p(path);
    if(fs::exists(p)){
        this->_filename = p.filename().string();
    }
    if(prnt != nullptr){
        _l = prnt->get_l()+1; 
    } else {
        _l = 0;
    }
}
string IFileWalker::filename(){
    return _filename;
} 
string IFileWalker::indent(){
    string ind = "";
    for(int i=0; i<_l; i++) ind+="\t"; 
    return ind;
} 
int IFileWalker::get_l(){
    return _l;
} 

//
// FileWalker
//

void FileWalker::treat(){
    std::cout<<indent()<<"- "<<_filename<<std::endl;
}

//
// DirWalker
//

DirWalker::DirWalker(IFileWalker* prnt, string path)
    :IFileWalker(prnt,path){
    for (const auto& e: fs::directory_iterator(path) ){
        WalkerBuilder& wb = WalkerBuilder::get_instance();
        IFileWalker* f = wb.build_walker(this,e.path().string()); 
        if (f != nullptr){
            this->files.push_back(f);
        }
    } 
}
void DirWalker::treat(){
    if (this->_path != ""){
        std::cout<<indent()<<"[] "<<_filename<<std::endl;
        for (const auto& e: this->files){
            e->treat();
        }
    }
} 

//
// WalkerBuilder
//

IFileWalker* WalkerBuilder::build_walker(IFileWalker* prnt, string path){ 
    if (fs::exists(path)) {
        if (fs::is_directory(path)) {
            return new DirWalker(prnt,path);
        } else {
            return new FileWalker(prnt,path);
        }
    } else {
        return nullptr; 
    } 
} 

}; // namespace file_treat
