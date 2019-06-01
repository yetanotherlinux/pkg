#include "FetchAction.h"

#include "pkg/infrastructure/Archive.h"

using pkg::infrastructure::Archive;

namespace pkg::actions {

    FetchAction::FetchAction(
            const std::shared_ptr<SourceStorage> &sourceStorage,
            const FileSystem &fileSystem,
            const WebClient &webClient,
            const Settings &settings,
            const Log &log) :
            Action(sourceStorage, true),
            _fileSystem(fileSystem),
            _webClient(webClient),
            _log(log),
            _sourcesPath(settings.GetSourcesPath()) {
        _fileSystem.CreateDirectory(_sourcesPath);
    }

    std::string FetchAction::GetName() const {
        return "fetch";
    }

    std::string FetchAction::GetPath(const Package &package) const {
        return _fileSystem.CreatePath(_sourcesPath, package.Name);
    }

    void FetchAction::Perform(const PackageMetadata &package) const {
        if (!ShouldBePerformed(package)) {
            return;
        }
        _log.Out() << "Fetching " << package.Name << " " << package.Version << " from " << package.Url << std::endl;

        std::string archivePath{Download(package)};

        std::string extractPath{_fileSystem.CreatePath(_sourcesPath, ".content")};
        std::string contentPath{Extract(archivePath, extractPath)};
        _fileSystem.Remove(archivePath);

        std::string destinationPath{GetPath(package)};
        _fileSystem.Remove(destinationPath);
        _fileSystem.Rename(contentPath, destinationPath);
        _fileSystem.Remove(extractPath);

        PushToStorage(package);
    }

    std::string FetchAction::Download(const PackageMetadata &package) const {
        std::string fileName{"pkg-" + package.Name + "-" + package.Version};
        std::string filePath{_fileSystem.CreatePath(_fileSystem.GetTempDirectoryPath(), fileName)};
        _fileSystem.Remove(filePath);
        _fileSystem.Write(filePath, [&](std::ostream &stream) {
            _webClient.Load(package.Url, &stream);
        });
        return filePath;
    }

    std::string FetchAction::Extract(const std::string &filePath, const std::string &extractPath) const {
        _fileSystem.Remove(extractPath);
        Archive archive{filePath, _fileSystem};
        return archive.Extract(extractPath);
    }
}
