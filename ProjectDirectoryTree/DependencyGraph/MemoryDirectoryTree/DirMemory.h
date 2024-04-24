
#ifndef MOTO_DIRMEMORY_H
#define MOTO_DIRMEMORY_H

#include "../../../src/include.h"
#include <cstddef>
#include <memory>
#include <list>
#include <stack>
#include <utility>


template <typename T>
class DirMemory {
public:
    explicit DirMemory(int F);
    ~DirMemory() = default;
    void addEdge(T src, T dest);
    std::vector<T> topologicalSort();

private:

    class FILE {
    public:
        explicit FILE(std::string path) : path(std::move(path)) {}
    private:
        std::string path;
        std::shared_ptr<std::list<FILE>> dependency;
    };

    size_t _numFiles;
    std::shared_ptr<std::map<T, std::list<T>>> adjLists;
    std::shared_ptr<std::list<FILE>> files;

    void dfs(T node, std::map<T, bool> &visited, std::stack<T> &result);
    std::map<T, bool> fillInitialVisited();
};


#endif //MOTO_DIRMEMORY_H
