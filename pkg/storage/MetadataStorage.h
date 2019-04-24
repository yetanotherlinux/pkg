#ifndef PKG_STORAGE_METADATA_STORAGE_H
#define PKG_STORAGE_METADATA_STORAGE_H

#include <vector>
#include <json/JsonObject.h>
#include "pkg/PackageMetadata.h"
#include "pkg/Settings.h"
#include "pkg/infrastructure/WebClient.h"

using json::JsonObject;
using pkg::infrastructure::WebClient;

namespace pkg::storage {
    class MetadataStorage {

    private:
        const std::string _url;
        const WebClient _webClient;

    public:
        MetadataStorage(const Settings &settings, const WebClient &webClient);

        PackageMetadata GetPackageMetadata(const std::string &packageName) const;

    private:
        std::vector<std::string> GetCollection(
                const std::shared_ptr<JsonObject> &container, const std::string &name) const;
    };
}

#endif
