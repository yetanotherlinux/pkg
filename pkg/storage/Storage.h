#ifndef PKG_STORAGE_STORAGE_H
#define PKG_STORAGE_STORAGE_H

#include <vector>
#include <json/Json.h>
#include <json/JsonObject.h>
#include "pkg/Package.h"
#include "pkg/infrastructure/FileSystem.h"

using json::Json;
using json::JsonObject;
using pkg::infrastructure::FileSystem;

namespace pkg::storage {
    class Storage {

    private:
        const std::string _filePath;
        const FileSystem _fileSystem;
        std::vector<Package> _packages;

    public:
        Storage(const std::string &filePath, const FileSystem &fileSystem);

        std::optional<Package> FindPackage(const std::string &packageName) const;

        void Push(const Package &package);

        void Pop(const Package &package);

    private:
        void UpdatePackage(
                const std::string &packageName,
                const std::function<void(
                        std::vector<Package> &,
                        std::shared_ptr<JsonObject>,
                        std::vector<Package>::iterator)> &callback);

        static Json GetJson(const FileSystem &fileSystem, const std::string &path);
    };
}

#endif
