#include "Storage.h"

#include <json/JsonReader.h>
#include <json/JsonWriter.h>

using json::Json;
using json::JsonProperty;
using json::JsonReader;
using json::JsonString;
using json::JsonWriter;

namespace pkg::storage {

    Storage::Storage(const Settings &settings, const std::string_view &fileName, const FileSystem &fileSystem) :
            _filePath(std::string(settings.StoragePath) + "/" + std::string(fileName)),
            _fileSystem(fileSystem),
            _packages() {
        fileSystem.CreateDirectory(std::string(settings.StoragePath));
        Json json{GetJson(_fileSystem, _filePath)};
        std::shared_ptr<JsonObject> container{std::dynamic_pointer_cast<JsonObject>(json.GetRoot())};
        for (const std::shared_ptr<JsonProperty> &property : container->GetProperties()) {
            std::string packageName{property->GetName()};
            std::string packageVersion{std::dynamic_pointer_cast<JsonString>(property->GetValue())->GetValue()};
            Package package{packageName, packageVersion};
            _packages.push_back(package);
        }
    }

    std::optional<Package> Storage::FindPackage(const std::string &packageName) const {
        for (const Package &package : _packages) {
            if (package.Name == packageName) {
                return package;
            }
        }
        return std::nullopt;
    }

    std::vector<Package> Storage::GetPackages() const {
        return _packages;
    }

    void Storage::Push(const Package &package) {
        UpdatePackage(
                package.Name, [&package](
                        std::vector<Package> &packages,
                        std::shared_ptr<JsonObject> container,
                        std::vector<Package>::iterator it) {
                    auto version{std::make_shared<JsonString>(package.Version)};
                    if (it == packages.end()) {
                        packages.push_back(package);
                        container->AddProperty(package.Name, version);
                    } else if (it->Version != package.Version) {
                        *it = package;
                        container->SetProperty(package.Name, version);
                    }
                });
    }

    void Storage::Pop(const Package &package) {
        UpdatePackage(
                package.Name, [&package](
                        std::vector<Package> &packages,
                        std::shared_ptr<JsonObject> container,
                        std::vector<Package>::iterator it) {
                    if (it != packages.end()) {
                        packages.erase(it);
                        container->RemoveProperty(package.Name);
                    }
                });
    }

    Json Storage::GetJson(const FileSystem &fileSystem, const std::string &path) {
        Json json{};
        if (fileSystem.IsFileExists(path)) {
            fileSystem.Read(path, [&json](std::istream &stream) {
                json = JsonReader(&stream).Read();
            });
        }
        return json;
    }

    void Storage::UpdatePackage(
            const std::string &packageName,
            const std::function<void(
                    std::vector<Package> &, std::shared_ptr<JsonObject>, std::vector<Package>::iterator)> &callback) {
        std::vector<Package>::iterator it{
                std::find_if(_packages.begin(), _packages.end(), [&packageName](const auto &p) {
                    return p.Name == packageName;
                })
        };
        Json json{GetJson(_fileSystem, _filePath)};
        auto container{std::dynamic_pointer_cast<JsonObject>(json.GetRoot())};
        callback(_packages, container, it);
        _fileSystem.Write(_filePath, [&json](std::ostream &stream) {
            JsonWriter(&stream).Write(json);
        });
    }
}
