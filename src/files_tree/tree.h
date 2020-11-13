#ifndef FILE_TREAT_TREE_H
#define FILE_TREAT_TREE_H

#include <string>
#include <vector>

namespace file_treat {

using std::string;
using std::vector;

// Интерфейс узла дерева (паттерн Компоновщик)
class tree_node {
protected:
    string _path;       // полный путь к файлу
    string _filename;   // имя файла
    int _l;             // уровень отступа
    string _indent;		// отступ
    tree_node* _prnt;   // родитель
public:
    tree_node(tree_node* prnt = nullptr, string path = "");
    virtual ~tree_node(){}
    string filename() const { return _filename; };
    string indent() const { return _indent; };
    int get_l() const { return _l; };
    virtual bool is_dir() const = 0;
    virtual vector<tree_node*>& files() = 0;
};

// Узел-файл
class file_node: public tree_node {
public:
    file_node(tree_node* prnt = nullptr, string path = ""):tree_node(prnt,path){}
    virtual ~file_node(){}
    virtual bool is_dir() const {return false; };
    virtual vector<tree_node*>& files();
};

// Узел-каталог
class dir_node: public tree_node {
protected:
    vector<tree_node*> _files;
public:
    dir_node(tree_node* prnt = nullptr, string path = "");
    virtual ~dir_node(){}
    virtual bool is_dir() const {return true; };
    virtual vector<tree_node*>& files() {return _files; };
};


} // namespace file_treat

#endif // TREE_H
