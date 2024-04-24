
#include "DirMemory.h"

template<typename T>
DirMemory<T>::DirMemory(int files) {
    _numFiles = files;
    adjLists = std::make_shared<std::map<T, std::list<T>>>();
}

template<typename T>
void DirMemory<T>::addEdge(T src, T dest) {
    if (adjLists->find(src) == adjLists->end()) {
        std::list<T> list;
        list.push_back(dest);
        adjLists->insert({ src, list });

        return;
    }
    adjLists->find(src)->second.push_back(dest);
}

template<typename T>
std::vector<T> DirMemory<T>::topologicalSort() {
    size_t n = _numFiles;
    std::map<T, bool> visited = fillInitialVisited();
    std::stack<T> result;

    for (const auto &vertex : *adjLists)
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
    if (adjLists->find(node) != adjLists->end())
        for (T neighbor : adjLists->find(node)->second)
            if (!visited.find(neighbor)->second)
                dfs(neighbor, visited, result);
    result.push(node);
}

template<typename T>
std::map<T, bool> DirMemory<T>::fillInitialVisited() {
    std::map<T, bool> visited;
    for (const auto &mapIterator : *adjLists)
        visited[mapIterator.first] = false;
    return visited;
}