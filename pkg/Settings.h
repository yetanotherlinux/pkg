#ifndef PKG_SETTINGS_H
#define PKG_SETTINGS_H

#include <string>

namespace pkg {
    class Settings {

    public:
        const std::string_view ShCommand;
        const std::string_view DefaultAction;
        const std::string_view RequiredPackageName;
        const std::string_view ImpersonationAccount;
        const std::string_view MetadataUrl;
        const std::string_view StoragePath;
        const std::string_view SourcesPath;
        const std::string_view BuildPath;
        const std::string_view HostFileName;
        const std::string_view PackagesFileName;
        const std::string_view BinariesFileName;
        const std::string_view SourcesFileName;
        const std::string_view LdCommand;
        const std::string_view LdCachePath;

        Settings();
    };
}

#endif
