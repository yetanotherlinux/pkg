#ifndef PKG_INFRASTRUCTURE_FILE_SYSTEM_H
#define PKG_INFRASTRUCTURE_FILE_SYSTEM_H

#include <functional>
#include "pkg/Account.h"

namespace pkg::infrastructure {
    class FileSystem {

    public:
        std::string GetTempDirectoryPath() const;

        std::string CreatePath(const std::string &path, const std::string &relativePath) const;

        bool IsFileExists(const std::string &path) const;

        void CreateDirectory(const std::string &path) const;

        void CreateLink(const std::string &path, const std::string &destination, const std::string &name) const;

        void Read(const std::string &path, const std::function<void(std::istream &stream)> &callback) const;

        void Write(const std::string &path, const std::function<void(std::ostream &stream)> &callback) const;

        void Rename(const std::string &path, const std::string &destination) const;

        void Remove(const std::string &path) const;

        void SetOwner(const std::string &path, const Account &account) const;
    };
}

#endif
