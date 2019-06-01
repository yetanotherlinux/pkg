#include "Settings.h"

namespace pkg {

    Settings::Settings(const std::string &appPath, const FileSystem &fileSystem) :
            _sourcesFilePath(fileSystem.CreatePath(appPath, "sources.json")),
            _buildsFilePath(fileSystem.CreatePath(appPath, "builds.json")),
            _packagesFilePath(fileSystem.CreatePath(appPath, "packages.json")),
            _currentAccount(Account::Current()),
            _impersonationAccount("nobody"),
            _ldCommand("ldconfig"),
            _ldCachePath("/etc/ld.so.cache"),
            MetadataUrl("https://raw.githubusercontent.com/yetanotherlinux/packages/master/"),
            StoragePath("/etc/pkg"),
            SourcesPath("/usr/src"),
            BuildPath("/var/tmp/pkg"),
            HostFileName("host.json"),
            Substitutions(
                    {{"cores", "1"}}
            ) {
        fileSystem.CreateDirectory(appPath);
    }

    std::string Settings::GetSourcesFilePath() const {
        return _sourcesFilePath;
    }

    std::string Settings::GetBuildsFilePath() const {
        return _buildsFilePath;
    }

    std::string Settings::GetPackagesFilePath() const {
        return _packagesFilePath;
    }

    Account Settings::GetCurrentAccount() const {
        return _currentAccount;
    }

    Account Settings::GetImpersonationAccount() const {
        return _impersonationAccount;
    }

    std::string Settings::GetLdCommand() const {
        return _ldCommand;
    }

    std::string Settings::GetLdCachePath() const {
        return _ldCachePath;
    }
}
