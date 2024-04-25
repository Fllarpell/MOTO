
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
    DirMemory() : _files(std::make_shared<std::map<std::string, FILE>>()) {};
    ~DirMemory() = default;
    void run(const std::string &top)  {

        _mappingFileDependencies = std::make_shared<FileMapping::MappingFileDependencies<T>>();

        FileMapping::directoryArchive<T> archive = _mappingFileDependencies->getDirectoryArchive(top);

        for (auto & item : archive.directories) {
            for (auto & file : item.files) {
                if (fs::path(item.directoryPath + "/" + file).extension() == ".h" || fs::path(item.directoryPath + "/" + file).extension() == ".cpp")
                    addFileVertex(item.directoryPath + "/" + file);

            }
        }
        _numFiles = _files->size();

        for (auto & item : archive._headerFileInformation) {
            for (auto & file : item.second.dependencies_files) {
                addFileEdge(item.first, item.second.path);
            }
        }
        for (auto & item : archive._cppFileInformation) {
            for (auto & file : item.second.dependencies_files) {
                addFileEdge(item.first, item.second.path);
            }
        }

        topologicalSort();

    }

private:

    class FILE {
    public:
        explicit FILE(T path) : path(std::move(path)) { dependency = std::make_shared<std::list<FILE>>(); }
        ~FILE() = default;

        std::shared_ptr<std::list<FILE>> getDependency() { return this->dependency; }
        void setDependencyFile(FILE file) { this->dependency->push_back(file); }
        T getPathFile() { return this->path; }
    private:
        T path;
        std::shared_ptr<std::list<FILE>> dependency;
    };

    size_t _numFiles;
    std::shared_ptr<std::map<T, FILE>> _files;
    std::shared_ptr<FileMapping::MappingFileDependencies<T>> _mappingFileDependencies;

    void addFileVertex(T path);
    void addFileEdge(T src, T dest);
    std::vector<T> topologicalSort();
    std::shared_ptr<std::list<FILE>> getDependency(T path) { return _files->find(path)->second->getDependency(); }
    void dfs(T node, std::map<T, bool> &visited, std::stack<T> &result);
    std::map<T, bool> fillInitialVisited();
};


template<typename T>
void DirMemory<T>::addFileVertex(T path) {
    FILE file(path);
    _files->insert({ path, file });
}

template<typename T>
void DirMemory<T>::addFileEdge(T src, T dest) {

    _files->find(src)->second.setDependencyFile(_files->find(dest)->second);
}

template<typename T>
std::vector<T> DirMemory<T>::topologicalSort() {
    size_t n = _numFiles;
    std::map<T, bool> visited = fillInitialVisited();
    std::stack<T> result;

    for (const auto &vertex : *_files)
        if (!visited.find(vertex.first)->second)
            dfs(vertex.first, visited, result);

    std::vector<T> sorted;
    while (!result.empty()) {
        sorted.push_back(result.top());
        result.pop();
    }

    std::reverse(sorted.begin(), sorted.end());
    for (const std::string& string : sorted)
        std::cout << string << "\n";

    return sorted;
}

template<typename T>
void DirMemory<T>::dfs(T node, std::map<T, bool> &visited, std::stack<T> &result) {
    visited[node] = true;
    if (_files->find(node) != _files->end())
        for (FILE neighbor : *_files->find(node)->second.getDependency())
            if (!visited.find(neighbor.getPathFile())->second)
                dfs(neighbor.getPathFile(), visited, result);
    result.push(node);
}

template<typename T>
std::map<T, bool> DirMemory<T>::fillInitialVisited() {
    std::map<T, bool> visited;
    for (const auto &mapIterator : *_files)
        visited[mapIterator.first] = false;
    return visited;
}



#endif //MOTO_DIRMEMORY_H
