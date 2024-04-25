cmake_minimum_required(VERSION 3.27)
project(MOTO)

set(CMAKE_CXX_STANDARD 17)

add_executable(MOTO src/main.cpp
        ProjectDirectoryTree/DirectoryRunner/DirRunner.cpp
        ProjectDirectoryTree/DirectoryRunner/DirRunner.h
        ProjectDirectoryTree/DependencyGraph/MemoryDirectoryTree/DirMemory.cpp
        ProjectDirectoryTree/DependencyGraph/MemoryDirectoryTree/DirMemory.h
        FileParsing/headerParsing/headerFileParsing.cpp
        FileParsing/headerParsing/headerFileParsing.h
        src/include.h
        ProjectDirectoryTree/FileDependencies/MappingFileDependencies.cpp
        ProjectDirectoryTree/FileDependencies/MappingFileDependencies.h
        FileParsing/cppParsing/CppFileParsing.cpp
        FileParsing/cppParsing/CppFileParsing.h
        FileMerger/Merger.cpp
        FileMerger/Merger.h)
