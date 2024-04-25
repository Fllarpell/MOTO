
#include "MappingFileDependencies.h"

template<typename T>
FileMapping::directoryArchive<T> FileMapping::MappingFileDependencies<T>::getDirectoryArchive() {
    return directoryArchive<T>();
}

template<typename T>
std::map<T, headerParsing::fileInfo>
FileMapping::MappingFileDependencies<T>::getCppFilesInformation(const std::string& path,
                                                   const std::vector<std::string>& files) {
    return std::make_unique<std::map<T, cppParsing::fileInfo>>(cppParsing::fileParser(path, files));
}

template<typename T>
std::map<T, headerParsing::fileInfo>
FileMapping::MappingFileDependencies<T>::getHeaderFilesInformation(const std::string& path,
                                                      const std::vector<std::string>& files) {
    return std::make_unique<std::map<T, headerParsing::fileInfo>>(headerParsing::fileParser(path, files));
}

template<typename T>
std::vector<DirRunner::DirectoryInfo>
FileMapping::MappingFileDependencies<T>::getWorkingDirectory(const std::string &top) {
    std::make_unique<std::vector<DirRunner::DirectoryInfo>>(DirRunner::DirRunner::walk(top));
}