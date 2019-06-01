#include "Settings.h"

namespace pkg {

    Settings::Settings() :
            _currentAccount(Account::Current()),
            _impersonationAccount("nobody"),
            ShCommand("bash"),
            MetadataUrl("https://raw.githubusercontent.com/yetanotherlinux/packages/master/"),
            StoragePath("/etc/pkg"),
            SourcesPath("/usr/src"),
            BuildPath("/var/tmp/pkg"),
            HostFileName("host.json"),
            PackagesFileName("packages.json"),
            BuildsFileName("builds.json"),
            SourcesFileName("sources.json"),
            LdCommand("ldconfig"),
            LdCachePath("/etc/ld.so.cache"),
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
}
