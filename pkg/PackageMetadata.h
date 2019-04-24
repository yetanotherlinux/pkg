#ifndef PKG_PACKAGE_METADATA_H
#define PKG_PACKAGE_METADATA_H

#include "pkg/Package.h"

#include <vector>

namespace pkg {
    struct PackageMetadata : public Package {

        std::string Url;
        std::vector<std::string> Config;
        std::vector<std::string> Build;
        std::vector<std::string> Install;
        std::vector<std::string> BuildDependencies;
        std::vector<std::string> StartupDependencies;
        std::vector<std::string> RuntimeDependencies;

        PackageMetadata(
                std::string name,
                std::string version,
                std::string url,
                std::vector<std::string> config,
                std::vector<std::string> build,
                std::vector<std::string> install,
                std::vector<std::string> buildDependencies,
                std::vector<std::string> startupDependencies,
                std::vector<std::string> runtimeDependencies);
    };
}

#endif
