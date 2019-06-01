#include "Settings.h"

namespace pkg {

    Settings::Settings(const std::string &appPath, const FileSystem &fileSystem) :
            _sourcesPath("/usr/src"),
            _buildsPath("/var/tmp/pkg"),
            _sourcesFilePath(fileSystem.CreatePath(appPath, "sources.json")),
            _buildsFilePath(fileSystem.CreatePath(appPath, "builds.json")),
            _packagesFilePath(fileSystem.CreatePath(appPath, "packages.json")),
            _hostFilePath(fileSystem.CreatePath(appPath, "host.json")),
            _currentAccount(Account::Current()),
            _impersonationAccount("nobody"),
            _substitutions({{"cores", "1"}}),
            _ldCommand("ldconfig"),
            _ldCachePath("/etc/ld.so.cache"),
            MetadataUrl("https://raw.githubusercontent.com/yetanotherlinux/packages/master/") {
        fileSystem.CreateDirectory(appPath);
    }

    std::string Settings::GetSourcesPath() const {
        return _sourcesPath;
    }

    std::string Settings::GetBuildsPath() const {
        return _buildsPath;
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

    std::string Settings::GetHostFilePath() const {
        return _hostFilePath;
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

    std::map<std::string, std::string> Settings::GetSubstitutions() const {
        return _substitutions;
    }
}
