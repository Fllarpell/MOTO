

#ifndef MOTO_MAPPINGFILEDEPENDENCIES_H
#define MOTO_MAPPINGFILEDEPENDENCIES_H
#include "../../FileParsing/headerParsing/headerFileParsing.h"
#include "../../FileParsing/cppParsing/CppFileParsing.h"
#include "../DirectoryRunner/DirRunner.h"
#include "../../src/include.h"

namespace FileMapping {
    template <typename T>
    struct directoryArchive {
        std::vector<DirRunner::DirectoryInfo> directories;
        std::map<T, headerParsing::fileInfo> _headerFileInformation;
        std::map<T, cppParsing::fileInfo> _cppFileInformation;
    };

    template <typename T>
    class MappingFileDependencies {
    public:
        directoryArchive<T> getDirectoryArchive(const std::string &top);
    private:
        void getWorkingDirectory(const std::string& top);
        void getHeaderFilesInformation(const std::string& path,
                                       const std::vector<std::string>& files);
        void getCppFilesInformation(const std::string& path,
                                    const std::vector<std::string>& files);

        std::vector<DirRunner::DirectoryInfo> directories;
        std::map<T, headerParsing::fileInfo> _headerFileInformation;
        std::map<T, cppParsing::fileInfo> _cppFileInformation;
    };

    template<typename T>
    directoryArchive<T> MappingFileDependencies<T>::getDirectoryArchive(const std::string &top) {
        getWorkingDirectory(top);
        std::vector<std::string> files;
        for (auto & item : directories) {
            for (auto & file : item.files) {
                files.push_back(file);
            }
        }

        for (auto & item : directories) {
            for (auto & file : item.files) {
                if (fs::path(item.directoryPath + "/" + file).extension() == ".h")
                    getHeaderFilesInformation(item.directoryPath + "/" + file, files);
                else if (fs::path(item.directoryPath + "/" + file).extension() == ".cpp")
                    getCppFilesInformation(item.directoryPath + "/" + file, files);
            }
        }

        directoryArchive<T> directoryArchive;
        directoryArchive.directories = directories;
        directoryArchive._headerFileInformation = _headerFileInformation;
        directoryArchive._cppFileInformation = _cppFileInformation;

        return directoryArchive;
    }

    template<typename T>
    void FileMapping::MappingFileDependencies<T>::getCppFilesInformation(const std::string& path,
                                                                         const std::vector<std::string>& files) {
        _cppFileInformation.insert({ path, cppParsing::fileParser(path, files)});
    }

    template<typename T>
    void FileMapping::MappingFileDependencies<T>::getHeaderFilesInformation(const std::string& path,
                                                                            const std::vector<std::string>& files) {
        _headerFileInformation.insert({ path, headerParsing::fileParser(path, files)});
    }

    template<typename T>
    void FileMapping::MappingFileDependencies<T>::getWorkingDirectory(const std::string &top) {
        this->directories = DirRunner::DirRunner::walk(top);
    }

}



#endif //MOTO_MAPPINGFILEDEPENDENCIES_H
