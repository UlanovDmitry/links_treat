#ifndef FILE_TREAT_WORKERS_H
#define FILE_TREAT_WORKERS_H

#include "tree.h"

namespace file_treat {

// Построитель дерева (паттерны Строитель, Одиночка)
class tree_builder {
private:
    tree_builder(){}
    tree_builder(tree_builder& oter) = delete;
    ~tree_builder(){}
    void operator=(const tree_builder& ) = delete;
public:
    static tree_builder& get_instance(){
        static tree_builder _instance;
        return _instance;
    }
    tree_node* build_node(tree_node* prnt, string path);
};

// Обходчик дерева (паттерны Посетитель, Одиночка)
class file_walker {
private:
    file_walker(){}
    file_walker(file_walker& oter) = delete;
    ~file_walker(){}
    void operator=(const file_walker& ) = delete;
public:
    static file_walker& get_instance(){
        static file_walker _instance;
        return _instance;
    }
    void visit(tree_node& f);
};


} // namespace file_treat

#endif // WORKERS_H
