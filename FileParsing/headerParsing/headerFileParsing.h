//
// Created by dimas on 24.04.2024.
//

#ifndef MOTO_HEADERFILEPARSING_H
#define MOTO_HEADERFILEPARSING_H

#include "../../src/include.h"
#include <fstream>
#include <algorithm>
#include <cstdio>

namespace headerParsing {
    typedef struct fileInfo {
        std::vector<std::string> output;
        std::vector<std::string> class_prototypes;
        std::vector<std::string> namespaces;
        std::vector<std::string> dependencies_libraries;
        std::vector<std::string> dependencies_files;
    } fileInfo;

    static fileInfo fileParser(const std::string& path,
                           const std::vector<std::string>& files, bool include_namespaces = false, bool comments = false);
};


#endif //MOTO_HEADERFILEPARSING_H
