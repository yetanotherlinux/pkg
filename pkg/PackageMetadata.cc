#include "PackageMetadata.h"

namespace pkg {

    PackageMetadata::PackageMetadata(
            std::string name,
            std::string version,
            std::string url,
            std::vector<std::string> config,
            std::vector<std::string> build,
            std::vector<std::string> install,
            std::vector<std::string> buildDependencies,
            std::vector<std::string> startupDependencies,
            std::vector<std::string> runtimeDependencies) :
            Package(std::move(name), std::move(version)),
            Url(std::move(url)),
            Config(std::move(config)),
            Build(std::move(build)),
            Install(std::move(install)),
            BuildDependencies(std::move(buildDependencies)),
            StartupDependencies(std::move(startupDependencies)),
            RuntimeDependencies(std::move(runtimeDependencies)) {
    }
}