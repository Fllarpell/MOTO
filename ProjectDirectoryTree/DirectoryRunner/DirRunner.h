//
// Created by dimas on 24.04.2024.
//

#ifndef MOTO_DIRRUNNER_H
#define MOTO_DIRRUNNER_H

#include "../../src/include.h"
#include <tuple>
#include <filesystem>

namespace fs = std::filesystem;

namespace DirRunner {

    typedef struct DirectoryInfo {
        std::string directoryPath;
        std::vector<std::string> directories;
        std::vector<std::string> files;
    } DirectoryInfo;

    class DirRunner {
    public:
        static std::vector<DirectoryInfo>
        walk(const std::string& top, bool topdown=true,
             void(*onerror)(const fs::filesystem_error&)=nullptr, bool followLinks=false);
    };
}



#endif //MOTO_DIRRUNNER_H
