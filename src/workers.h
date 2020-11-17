#ifndef FILE_TREAT_WORKERS_H
#define FILE_TREAT_WORKERS_H

#include "tree.h"

namespace file_treat {


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


} // namespace file_treat

#endif // FILE_TREAT_WORKERS_H
