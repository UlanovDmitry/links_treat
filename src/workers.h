#ifndef FILE_TREAT_WORKERS_H
#define FILE_TREAT_WORKERS_H

#include <string>
#include <fstream>
#include "tree.h"

namespace file_treat {

using std::string;
using std::ofstream;

// Исполнитель действий над узлом
// (паттерн Декоратор)
class worker {
public:
    virtual void work(tree_node& n){}
    virtual ~worker(){}
};


// Обертка исполнителя
class worker_wrap: public worker {
private:
    worker* _w;
public:
    worker_wrap(worker* w): _w(w){}
    virtual void work(tree_node& n);
    virtual ~worker_wrap();
};


// Логгер
class worker_logger: public worker_wrap{
public:
    worker_logger(worker* w): worker_wrap(w){}
    virtual void work(tree_node& n);
};


// Разбор ini-файла
class worker_ini_parser: public worker_wrap{
public:
    worker_ini_parser(worker* w): worker_wrap(w){}
    virtual void work(tree_node& n);
};


// Формирование .md файла
class worker_md_maker: public worker_wrap{
    ofstream _f;
public:
    worker_md_maker(worker* w, string path);
    virtual ~worker_md_maker();
    virtual void work(tree_node& n);
};


// Сбор не-url файлов
class worker_res_accum: public worker_wrap{
    ofstream _f;
    string _path;
public:
    worker_res_accum(worker* w, string path);
    virtual ~worker_res_accum();
    virtual void work(tree_node& n);
};



} // namespace file_treat

#endif // FILE_TREAT_WORKERS_H
