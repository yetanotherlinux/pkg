#include "HostStorage.h"

#include <json/JsonReader.h>
#include <json/JsonWriter.h>

using json::Json;
using json::JsonArray;
using json::JsonNode;
using json::JsonObject;
using json::JsonProperty;
using json::JsonReader;
using json::JsonString;
using json::JsonWriter;

namespace pkg::storage {

    HostStorage::HostStorage(const Settings &settings, const FileSystem &fileSystem) :
            _filePath(fileSystem.CreatePath(std::string(settings.StoragePath), std::string(settings.HostFileName))),
            _fileSystem(fileSystem),
            _packages() {
        fileSystem.CreateDirectory(std::string(settings.StoragePath));
        Json json{GetJson(_fileSystem, _filePath)};
        if (std::shared_ptr<JsonArray> container{std::dynamic_pointer_cast<JsonArray>(json.GetRoot())}; container) {
            for (const std::shared_ptr<JsonNode> &node : container->GetItems()) {
                std::string package{std::dynamic_pointer_cast<JsonString>(node)->GetValue()};
                _packages.push_back(package);
            }
        }
        if (_packages.empty()) {
            _packages.emplace_back(settings.RequiredPackageName);
        }
    }

    std::vector<std::string> HostStorage::GetPackages() const {
        return _packages;
    }

    Json HostStorage::GetJson(const FileSystem &fileSystem, const std::string &path) {
        Json json{};
        if (fileSystem.IsFileExists(path)) {
            fileSystem.Read(path, [&json](std::istream &stream) {
                json = JsonReader(&stream).Read();
            });
        }
        return json;
    }
}
