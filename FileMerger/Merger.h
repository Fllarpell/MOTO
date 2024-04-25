//
// Created by dimas on 25.04.2024.
//

#ifndef MOTO_MERGER_H
#define MOTO_MERGER_H
#include "../FileParsing/headerParsing/headerFileParsing.h"
#include "../FileParsing/cppParsing/CppFileParsing.h"
#include <fstream>
#include <vector>
#include <filesystem>

namespace Merger {

    // do it more generic
    template<typename T>
    void mergeProject(std::vector<cppParsing::fileInfo>& main, std::vector<std::string> &class_prototypes, std::vector<std::string> &includes, std::vector<headerParsing::fileInfo> &order, std::map<T, cppParsing::fileInfo>& comp) {
        std::ofstream Merger("output.cpp");


        for (auto & include : includes)
            Merger << include << '\n';


        for (auto & item : order) {
            for (auto & file : item.output)
                Merger << file;
            if (comp.find(item.path) != comp.end())
                for (auto & file : comp.find(item.path)->second.output)
                    Merger << file;
        }

        for (auto & mainFunc : main)
            for (auto & file : mainFunc.output)
                Merger << file;

    }
}


#endif //MOTO_MERGER_H
