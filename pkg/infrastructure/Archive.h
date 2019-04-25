#ifndef PKG_INFRASTRUCTURE_ARCHIVE_H
#define PKG_INFRASTRUCTURE_ARCHIVE_H

#include "pkg/infrastructure/FileSystem.h"

using pkg::infrastructure::FileSystem;

namespace pkg::infrastructure {
    class Archive {

    private:
        const std::string _path;
        const FileSystem _fileSystem;

    public:
        Archive(std::string path, const FileSystem &fileSystem);

        std::string Extract(const std::string &path) const;
    };
}

#endif
