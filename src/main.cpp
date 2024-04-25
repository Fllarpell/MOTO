#include "../ProjectDirectoryTree/DependencyGraph/MemoryDirectoryTree/DirMemory.h"

int main(int argc, char*argv[]) {
    DirMemory<std::string> dirMemory = DirMemory<std::string>();

    dirMemory.run("C:\\Users\\dimas\\CLionProjects\\simplified_bank_system");

    return 0;
}
