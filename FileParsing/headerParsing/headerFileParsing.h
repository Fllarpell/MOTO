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
        std::string path;
    } fileInfo;

    static fileInfo fileParser(const std::string& path,
                           const std::vector<std::string>& files, bool include_namespaces = false, bool comments = true);

    fileInfo fileParser(const std::string& path, const std::vector<std::string>& files, bool include_namespaces, bool comments) {
        std::vector<std::string> output;
        std::vector<std::string> class_prototypes;
        std::vector<std::string> namespaces;
        std::vector<std::string> dependencies_libraries;
        std::vector<std::string> dependencies_files;
        std::vector<std::string> ignoreString {"#pragma once", "#ifndef", "#endif", "#if", "#end", "#define"}; // assume this is populated elsewhere

        std::ifstream reader(path);
        std::string fileLine;
        std::vector<std::string> stack_comments;

        //std::map<std::string, std::vector<int>> index_brackets = {{"{", {}}, {"}", {}}};

        while (std::getline(reader, fileLine)) {
            bool flag = true;

            if (fileLine.find("*/") != std::string::npos) {
                if (!comments) {
                    if (!stack_comments.empty()) {
                        stack_comments.pop_back();
                        continue;
                    }
                }
            }

            if (!stack_comments.empty()) {
                continue;
            }

            if (fileLine.find("/*") != std::string::npos) {
                if (!comments) {
                    if (fileLine.find("*/") != std::string::npos) {
                        fileLine.replace(fileLine.find("/*"), fileLine.find("*/") - fileLine.find("/*") + 2, "\n");
                        output.push_back(fileLine);
                        continue;
                    }
                    stack_comments.emplace_back("long_comment");
                    continue;
                }
            }

            if (fileLine.find("//") != std::string::npos) {
                if (!comments) {
                    if (std::count(fileLine.begin(), fileLine.end(), ';') == 1) {
                        if (fileLine.find(';') < fileLine.find("//"))
                            fileLine.replace(fileLine.find(';'), fileLine.size() - fileLine.find(';') + 1, "");
                        else
                            fileLine.replace(fileLine.find("//"), fileLine.size() - fileLine.find("//"), "");
                    } else if (std::count(fileLine.begin(), fileLine.end(), ';') == 0) {
                        if (fileLine.find("//") == 0)
                            fileLine.replace(0, fileLine.size(), "");
                        else
                            fileLine.replace(fileLine.find("//"), fileLine.size() - fileLine.find("//"), "");
                    } else if (std::count(fileLine.begin(), fileLine.end(), ';') > 1) {
                        // ...
                    }
                }
            }

            for (const std::string& word : ignoreString) {
                if (fileLine.find(word) != std::string::npos) {
                    flag = false;
                    break;
                }
            }



            if (fileLine.find("class") != std::string::npos && fileLine.find(';') != std::string::npos &&
                fileLine.find("class") < fileLine.find("//") && fileLine.find(';') < fileLine.find("//")) {
                class_prototypes.push_back(fileLine);
                flag = true;
            }

            if (include_namespaces) {
                if (fileLine.find("namespace") != std::string::npos) {
                    if (fileLine.find("using") != std::string::npos || fileLine.find('=') != std::string::npos) {
                        // pass
                    } else if (fileLine.find("//") != std::string::npos) {
                        if (fileLine.find("namespace") < fileLine.find("//")) {
                            namespaces.push_back(fileLine.substr(fileLine.find("namespace") + 9).replace(fileLine.find(';'), 1, "\n"));
                            flag = false;
                        }
                    } else {
                        namespaces.push_back(fileLine.substr(fileLine.find("namespace") + 9).replace(fileLine.find(';'), 1, "\n"));
                        flag = false;
                    }
                }
            }

            if (fileLine.find("#include") != std::string::npos) {
                bool library = true;
                if (fileLine.find("//") != std::string::npos) {
                    if (fileLine.find("#include") < fileLine.find("//")) {
                        flag = false;
                        if (fileLine.find('<') != std::string::npos && fileLine.find('>') != std::string::npos)
                            dependencies_libraries.push_back(fileLine);
                        else {
                            for (const std::string& f : files) {
                                if (fileLine.find(f.substr(f.find_last_of('/'), std::string::npos)) != std::string::npos) {
                                    dependencies_files.push_back(f);
                                    library = false;
                                    break;
                                }

                            }
                            if (library)
                                dependencies_libraries.push_back(fileLine);
                        }
                    }
                } else {
                    flag = false;
                    if (fileLine.find('<') != std::string::npos && fileLine.find('>') != std::string::npos) {
                        dependencies_libraries.push_back(fileLine);
                    } else {
                        for (const std::string& f : files) {
                            if (fileLine.find(f.substr(f.find_last_of('/'), std::string::npos)) != std::string::npos) {
                                dependencies_files.push_back(f);
                                library = false;
                                break;
                            }
                        }
                        if (library)
                            dependencies_libraries.push_back(fileLine);
                    }
                }
            }

            if (flag)
                output.push_back(fileLine + "\n");

            /*for (char c : fileLine) {
                if (c == '{')
                    index_brackets["{"].push_back(  output.size());
                else if (c == '}')
                    index_brackets["}"].push_back(output.size());
            }*/
        }

        headerParsing::fileInfo fileInfo;
        fileInfo = (headerParsing::fileInfo) {
                .output = output,
                .class_prototypes = class_prototypes,
                .namespaces = namespaces,
                .dependencies_libraries = dependencies_libraries,
                .dependencies_files = dependencies_files,
                .path = path,
        };

        return fileInfo;
    }
};


#endif //MOTO_HEADERFILEPARSING_H
