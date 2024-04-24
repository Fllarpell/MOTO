//
// Created by dimas on 24.04.2024.
//

#include "DirRunner.h"

std::vector<std::tuple<std::string, std::vector<std::string>, std::vector<std::string>>>
DirRunner::walk(const std::string& top, bool topdown=true, void(*onerror)(const fs::filesystem_error&)=nullptr, bool followLinks=false) {
    static std::vector<std::tuple<std::string, std::vector<std::string>, std::vector<std::string>>> result;
    auto islink = [](const fs::path& p) { return fs::is_symlink(p); };
    auto isdir = [](const fs::path& p) { return fs::is_directory(p); };

    try {
        std::vector<fs::directory_entry> entries;
        for (auto& entry : fs::directory_iterator(top)) {
            entries.push_back(entry);
        }

        std::vector<std::string> dirs, nonDirs;

        for (auto& entry : entries) {
            if (isdir(entry.path())) {
                dirs.push_back(entry.path().filename().generic_string());
            } else {
                nonDirs.push_back(entry.path().filename().generic_string());
            }
        }

        if (topdown)
            result.emplace_back(top, dirs, nonDirs);

        for (auto& dir : dirs) {
            fs::path new_path = top + "/" + dir;

            if ((followLinks || !islink(new_path)) && dir != "cmake-build-debug") {
                walk(new_path.string(), topdown, onerror, followLinks);
            }
        }

        if (!topdown)
            result.emplace_back(top, dirs, nonDirs);

        return result;

    } catch (const fs::filesystem_error& err) {
        if (onerror != nullptr) {
            onerror(err);
        }
    }
}