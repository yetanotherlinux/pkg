#include "PackageGraph.h"

#include <algorithm>
#include "pkg/Exception.h"

namespace pkg {

    PackageGraph::PackageGraph(const std::shared_ptr<MetadataStorage> &metadataStorage) :
            _metadataStorage(metadataStorage),
            _packages() {
    }

    bool PackageGraph::IsEmpty() const {
        return _packages.empty();
    }

    void PackageGraph::Add(const std::string &packageName) {
        if (Contains(packageName)) {
            return;
        }
        PackageMetadata package{_metadataStorage->GetPackageMetadata(packageName)};
        _packages.emplace_back(package);
        for (const std::string &dependencyName : package.BuildDependencies) {
            Add(dependencyName);
        }
        for (const std::string &dependencyName : package.StartupDependencies) {
            Add(dependencyName);
        }
        for (const std::string &dependencyName : package.RuntimeDependencies) {
            Add(dependencyName);
        }
    }

    bool PackageGraph::Contains(const std::string &packageName) const {
        std::vector<PackageMetadata>::const_iterator package{
                std::find_if(_packages.begin(), _packages.end(), [&packageName](const auto &i) {
                    return i.Name == packageName;
                })
        };
        return package != _packages.end();
    }

    PackageMetadata PackageGraph::ExtractLeaf() {
        std::vector<PackageMetadata>::const_iterator weakDependency{_packages.end()};
        for (auto it{_packages.begin()}; it != _packages.end(); ++it) {
            bool isDepends{IsDepends(it->BuildDependencies) || IsDepends(it->StartupDependencies)};
            if (!isDepends) {
                if (!IsDepends(it->RuntimeDependencies)) {
                    return Extract(it);
                }
                weakDependency = it;
            }
        }
        if (weakDependency != _packages.end()) {
            return Extract(weakDependency);
        }
        for (auto it{_packages.begin()}; it != _packages.end(); ++it) {
            if (it->Name == "gcc") {
                PackageMetadata package{*it};
                _packages.erase(it);
                return package;
            }
        }
        throw Exception("Circular packages dependency detected");
    }

    bool PackageGraph::IsDepends(const std::vector<std::string> &dependencies) const {
        for (auto it{_packages.begin()}; it != _packages.end(); ++it) {
            for (const std::string &dependency : dependencies) {
                std::vector<PackageMetadata>::const_iterator i{
                        std::find_if(_packages.begin(), _packages.end(), [&dependency](const auto &package) {
                            return package.Name == dependency;
                        })
                };
                if (i != _packages.end()) {
                    return true;
                }
            }
        }
        return false;
    }

    PackageMetadata PackageGraph::Extract(std::vector<PackageMetadata>::const_iterator it) {
        PackageMetadata package{*it};
        _packages.erase(it);
        return package;
    }
}
