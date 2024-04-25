

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
        directoryArchive<T> getDirectoryArchive();
    private:
        std::vector<DirRunner::DirectoryInfo> getWorkingDirectory(const std::string& top);
        std::map<T, headerParsing::fileInfo> getHeaderFilesInformation(const std::string& path,
                                                                       const std::vector<std::string>& files);
        std::map<T, headerParsing::fileInfo> getCppFilesInformation(const std::string& path,
                                                                    const std::vector<std::string>& files);

        std::unique_ptr<std::vector<DirRunner::DirectoryInfo>> directories;
        std::unique_ptr<std::map<T, headerParsing::fileInfo>> _headerFileInformation;
        std::unique_ptr<std::map<T, cppParsing::fileInfo>> _cppFileInformation;
    };

}



#endif //MOTO_MAPPINGFILEDEPENDENCIES_H
