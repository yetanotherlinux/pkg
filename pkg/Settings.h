#ifndef PKG_SETTINGS_H
#define PKG_SETTINGS_H

#include <map>

#include "pkg/infrastructure/Account.h"
#include "pkg/infrastructure/FileSystem.h"

using pkg::infrastructure::Account;
using pkg::infrastructure::FileSystem;

namespace pkg {
    class Settings {

    private:
        const std::string _sourcesPath;
        const std::string _buildsPath;
        const std::string _sourcesFilePath;
        const std::string _buildsFilePath;
        const std::string _packagesFilePath;
        const std::string _hostFilePath;
        const Account _currentAccount;
        const Account _impersonationAccount;
        const std::string _metadataUrl;
        const std::map<std::string, std::string> _substitutions;
        const std::string _ldCommand;
        const std::string _ldCachePath;

    public:
        Settings(const std::string &appPath, const std::string &arch, const FileSystem &fileSystem);

        std::string GetSourcesPath() const;

        std::string GetBuildsPath() const;

        std::string GetSourcesFilePath() const;

        std::string GetBuildsFilePath() const;

        std::string GetPackagesFilePath() const;

        std::string GetHostFilePath() const;

        std::string GetMetadataUrl() const;

        Account GetCurrentAccount() const;

        Account GetImpersonationAccount() const;

        std::string GetLdCommand() const;

        std::string GetLdCachePath() const;

        std::map<std::string, std::string> GetSubstitutions() const;
    };
}

#endif
