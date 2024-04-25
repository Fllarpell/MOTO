
#include "DirMemory.h"

template<typename T>
DirMemory<T>::DirMemory(int numFiles) {
    _numFiles = numFiles;
    _files = std::make_shared<std::map<std::string, FILE>>();
}

template<typename T>
void DirMemory<T>::addFileVertex(T path) {
    FILE* file(path);
    _files->insert({ path, file });
}

template<typename T>
void DirMemory<T>::addFileEdge(T src, T dest) {
    FILE* fileTo(dest);
    _files->find(src)->second.setDependencyFile(fileTo);
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

    return sorted;
}

template<typename T>
void DirMemory<T>::dfs(T node, std::map<T, bool> &visited, std::stack<T> &result) {
    visited[node] = true;
    if (_files->find(node) != _files->end())
        for (FILE* neighbor : _files->find(node)->second.getDependency())
            if (!visited.find(neighbor->getPathFile())->second)
                dfs(neighbor, visited, result);
    result.push(node);
}

template<typename T>
std::map<T, bool> DirMemory<T>::fillInitialVisited() {
    std::map<T, bool> visited;
    for (const auto &mapIterator : *_files)
        visited[mapIterator.first] = false;
    return visited;
}