#ifndef PKG_SETTINGS_H
#define PKG_SETTINGS_H

#include <map>

#include "pkg/Account.h"

namespace pkg {
    class Settings {

    private:
        const Account _currentAccount;
        const Account _impersonationAccount;

    public:
        const std::string_view ShCommand;
        const std::string_view MetadataUrl;
        const std::string_view StoragePath;
        const std::string_view SourcesPath;
        const std::string_view BuildPath;
        const std::string_view HostFileName;
        const std::string_view PackagesFileName;
        const std::string_view BuildsFileName;
        const std::string_view SourcesFileName;
        const std::string_view LdCommand;
        const std::string_view LdCachePath;
        const std::map<std::string, std::string> Substitutions;

        Settings();

        Account GetCurrentAccount() const;

        Account GetImpersonationAccount() const;
    };
}

#endif
