
#ifndef MOTO_DIRMEMORY_H
#define MOTO_DIRMEMORY_H

#include "../../../src/include.h"
#include "../../FileDependencies/MappingFileDependencies.h"
#include <cstddef>
#include <memory>
#include <stack>
#include <utility>


template <typename T>
class DirMemory {
public:
    explicit DirMemory(int F);
    ~DirMemory() = default;

    void addFileVertex(T path);
    void addFileEdge(T src, T dest);
    std::vector<T> topologicalSort();

    std::shared_ptr<std::list<FILE>> getDependency(T path) { return _files->find(path)->second->getDependency(); }

private:

    class FILE {
    public:
        explicit FILE(T path) : path(std::move(path)) { dependency = std::make_shared<std::list<FILE>>(); }
        ~FILE() = default;

        std::shared_ptr<std::list<FILE>> getDependency() { return this->dependency; }
        void setDependencyFile(FILE* file) { this->dependency->push_back(file); }
        T getPathFile() { return this->path; }
    private:
        T path;
        std::shared_ptr<std::list<FILE>> dependency;
    };

    size_t _numFiles;
    std::shared_ptr<std::map<T, FILE>> _files;
    std::unique_ptr<FileMapping::MappingFileDependencies<T>> _mappingFileDependencies;

    void dfs(T node, std::map<T, bool> &visited, std::stack<T> &result);
    std::map<T, bool> fillInitialVisited();
};


#endif //MOTO_DIRMEMORY_H
