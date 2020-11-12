#ifndef TREAT_DIR_H
#define TREAT_DIR_H

#include <string>
#include <vector>

namespace file_treat {

using std::string;
using std::vector;

// Интерфейс анализатора файлов
class IFileWalker { 
protected: 
    string _path;       // полный путь к файлу
    string _filename;   // имя файла
    int _l;             // уровень отступа
    IFileWalker* _prnt; // родитель
public:
    IFileWalker(IFileWalker* prnt = nullptr, string path = "");
    string filename();
    string indent();
    int get_l(); 
    virtual ~IFileWalker(){}
    virtual void treat() = 0; 
};

// Анализатор файлов
class FileWalker : public IFileWalker {

public:
    virtual void treat(); 
    FileWalker(IFileWalker* prnt = nullptr, string path = ""):IFileWalker(prnt,path){}
    virtual ~FileWalker(){}
}; 

// Анализатор каталогов
class DirWalker : public IFileWalker { 
protected:
    vector<IFileWalker*> files;
public:
    virtual void treat(); 
    DirWalker(IFileWalker* prnt = nullptr, string path = "");
    virtual ~DirWalker(){} 
};

// Построитель объектов-анализаторов
// (одиночка, строитель)
class WalkerBuilder { 
private:
    WalkerBuilder(){}
    ~WalkerBuilder(){}
    WalkerBuilder(WalkerBuilder& oter) = delete;
    void operator=(const WalkerBuilder& ) = delete; 
public: 
    static WalkerBuilder& get_instance(){
        static WalkerBuilder _instance;
        return _instance; 
    } 
    IFileWalker* build_walker(IFileWalker* prnt, string path); 
};

}; // namespace file_treat

#endif
