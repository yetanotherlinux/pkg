#ifndef PKG_STORAGE_HOST_STORAGE_H
#define PKG_STORAGE_HOST_STORAGE_H

#include <vector>
#include <json/Json.h>
#include "pkg/Settings.h"
#include "pkg/infrastructure/FileSystem.h"

using json::Json;
using pkg::infrastructure::FileSystem;

namespace pkg::storage {
    class HostStorage {

    private:
        const std::string _filePath;
        const FileSystem _fileSystem;
        std::vector<std::string> _packages;

    public:
        HostStorage(const Settings &settings, const FileSystem &fileSystem);

        std::vector<std::string> GetPackages() const;

    private:
        static Json GetJson(const FileSystem &fileSystem, const std::string &path);
    };
}

#endif
