#include "Settings.h"

namespace pkg {

    Settings::Settings() :
            ShCommand("bash"),
            DefaultAction("status"),
            RequiredPackageName("@environment"),
            ImpersonationAccount("nobody"),
            MetadataUrl("https://raw.githubusercontent.com/yetanotherlinux/packages/master/"),
            StoragePath("/etc/pkg"),
            SourcesPath("/usr/src"),
            BuildPath("/var/tmp/pkg"),
            HostFileName("host.json"),
            PackagesFileName("packages.json"),
            BinariesFileName("binaries.json"),
            SourcesFileName("sources.json") {
    }
}
