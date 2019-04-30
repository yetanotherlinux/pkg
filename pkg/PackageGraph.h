#ifndef PKG_PACKAGE_GRAPH_H
#define PKG_PACKAGE_GRAPH_H

#include <memory>
#include "pkg/storage/MetadataStorage.h"

using pkg::storage::MetadataStorage;

namespace pkg {
    class PackageGraph {

    private:
        const std::shared_ptr<MetadataStorage> _metadataStorage;
        std::vector<PackageMetadata> _packages;

    public:
        PackageGraph(const std::shared_ptr<MetadataStorage> &metadataStorage);

        bool IsEmpty() const;

        PackageMetadata ExtractLeaf();

        void Add(const std::string &packageName);

    private:
        bool Contains(const std::string &packageName) const;

        bool IsDepends(const std::vector<std::string> &dependencies) const;

        PackageMetadata Extract(const std::vector<PackageMetadata>::const_iterator &it);

    };
}

#endif
