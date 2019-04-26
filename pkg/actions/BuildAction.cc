#include "BuildAction.h"

namespace pkg::actions {

    BuildAction::BuildAction(
            const std::shared_ptr<BinaryStorage> &binaryStorage,
            const std::shared_ptr<FetchAction> &fetchAction,
            const FileSystem &fileSystem,
            const Shell &shell,
            const Settings &settings,
            const Log &log) :
            Action(binaryStorage, true),
            _fetchAction(fetchAction),
            _fileSystem(fileSystem),
            _shell(shell),
            _log(log),
            _buildPath(settings.BuildPath) {
        _fileSystem.CreateDirectory(_buildPath);
    }

    std::string BuildAction::GetName() const {
        return "build";
    }

    void BuildAction::Perform(const PackageMetadata &package) const {
        if (!ShouldBePerformed(package)) {
            return;
        }
        _fetchAction->Perform(package);

        std::string rootPath{GetRootPath(package)};
        std::string buildPath{GetPath(package)};
        _fileSystem.Remove(rootPath);
        _fileSystem.CreateDirectory(buildPath);
        _fileSystem.CreateLink(rootPath, _fetchAction->GetPath(package), "src");
        RunCommands(_shell, package.Config, buildPath, true);
        RunCommands(_shell, package.Build, buildPath, true);
        PushToStorage(package);
    }

    std::string BuildAction::GetPath(const PackageMetadata &package) const {
        return _fileSystem.CreatePath(GetRootPath(package), "build");
    }

    std::string BuildAction::GetRootPath(const PackageMetadata &package) const {
        return _fileSystem.CreatePath(_buildPath, package.Name);
    }
}
