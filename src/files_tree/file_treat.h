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
    virtual ~IFileWalker(){}
    string filename() const;
    string indent() const;
    int get_l() const;
    virtual bool is_dir() const = 0;
    virtual void treat() = 0; 
    virtual vector<IFileWalker*>& files() = 0;
};

// Анализатор файлов
class FileWalker : public IFileWalker {
public:
    FileWalker(IFileWalker* prnt = nullptr, string path = ""):IFileWalker(prnt,path){}
    virtual ~FileWalker(){}
    virtual bool is_dir() const;
    virtual void treat();
    virtual vector<IFileWalker*>& files();
};

// Анализатор каталогов
class DirWalker : public IFileWalker { 
protected:
    vector<IFileWalker*> _files;
public:
    DirWalker(IFileWalker* prnt = nullptr, string path = "");
    virtual ~DirWalker(){}
    virtual bool is_dir() const;
    virtual void treat();
    virtual vector<IFileWalker*>& files();
};

// Построитель объектов-анализаторов
// (одиночка, строитель)
class WalkerBuilder { 
private:
    WalkerBuilder(){}
    WalkerBuilder(WalkerBuilder& oter) = delete;
    ~WalkerBuilder(){}
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
