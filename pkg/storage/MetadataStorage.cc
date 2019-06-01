#include "MetadataStorage.h"

#include <sstream>
#include <json/JsonReader.h>

using json::Json;
using json::JsonArray;
using json::JsonProperty;
using json::JsonReader;
using json::JsonString;

namespace pkg::storage {

    MetadataStorage::MetadataStorage(const Settings &settings, const WebClient &webClient) :
            _url(settings.GetMetadataUrl()),
            _webClient(webClient) {
    }

    PackageMetadata MetadataStorage::GetPackageMetadata(const std::string &packageName) const {
        std::stringstream stream{};
        _webClient.Load(_url + packageName + ".json", &stream);
        Json json{JsonReader(&stream).Read()};
        std::shared_ptr<JsonObject> container{std::dynamic_pointer_cast<JsonObject>(json.GetRoot())};
        std::string version{std::dynamic_pointer_cast<JsonString>(container->FindProperty("version"))->GetValue()};
        std::string url{std::dynamic_pointer_cast<JsonString>(container->FindProperty("url"))->GetValue()};
        std::shared_ptr<JsonObject> dependencies{
                std::dynamic_pointer_cast<JsonObject>(container->FindProperty("dependencies"))
        };

        return PackageMetadata(
                packageName,
                version,
                url,
                GetCollection(container, "prepare"),
                GetCollection(container, "build"),
                GetCollection(container, "install"),
                GetCollection(dependencies, "build"),
                GetCollection(dependencies, "startup"),
                GetCollection(dependencies, "runtime"));
    }

    std::vector<std::string> MetadataStorage::GetCollection(
            const std::shared_ptr<JsonObject> &container, const std::string &name) const {
        std::vector<std::string> dependencies{};
        for (const auto &node : std::dynamic_pointer_cast<JsonArray>(container->FindProperty(name))->GetItems()) {
            std::string packageName{std::dynamic_pointer_cast<JsonString>(node)->GetValue()};
            dependencies.push_back(packageName);
        }
        return dependencies;
    }
}
