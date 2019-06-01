#include "Settings.h"

namespace pkg {

    Settings::Settings() :
            _currentAccount(Account::Current()),
            _impersonationAccount("nobody"),
            _ldCommand("ldconfig"),
            _ldCachePath("/etc/ld.so.cache"),
            MetadataUrl("https://raw.githubusercontent.com/yetanotherlinux/packages/master/"),
            StoragePath("/etc/pkg"),
            SourcesPath("/usr/src"),
            BuildPath("/var/tmp/pkg"),
            HostFileName("host.json"),
            PackagesFileName("packages.json"),
            BuildsFileName("builds.json"),
            SourcesFileName("sources.json"),
            Substitutions(
                    {{"cores", "1"}}
            ) {
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
