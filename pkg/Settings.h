#ifndef PKG_SETTINGS_H
#define PKG_SETTINGS_H

#include <map>

#include "pkg/Account.h"
#include "pkg/infrastructure/FileSystem.h"

using pkg::infrastructure::FileSystem;

namespace pkg {
    class Settings {

    private:
        const std::string _sourcesFilePath;
        const std::string _buildsFilePath;
        const std::string _packagesFilePath;
        const std::string _hostFilePath;
        const Account _currentAccount;
        const Account _impersonationAccount;
        const std::string _ldCommand;
        const std::string _ldCachePath;

    public:
        const std::string_view MetadataUrl;
        const std::string_view SourcesPath;
        const std::string_view BuildPath;
        const std::map<std::string, std::string> Substitutions;

        Settings(const std::string &appPath, const FileSystem &fileSystem);

        std::string GetSourcesFilePath() const;

        std::string GetBuildsFilePath() const;

        std::string GetPackagesFilePath() const;

        std::string GetHostFilePath() const;

        Account GetCurrentAccount() const;

        Account GetImpersonationAccount() const;

        std::string GetLdCommand() const;

        std::string GetLdCachePath() const;
    };
}

#endif
