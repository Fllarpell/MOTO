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
    static void fileParser(const std::string& nameOutput, const std::string& path,
                           const std::vector<std::string>& files, bool include_namespaces = false, bool comments = false);
};


#endif //MOTO_HEADERFILEPARSING_H
