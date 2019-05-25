#include "BuildAction.h"

namespace pkg::actions {

    BuildAction::BuildAction(
            const std::shared_ptr<BuildStorage> &buildStorage,
            const std::shared_ptr<FetchAction> &fetchAction,
            const Substitution &substitution,
            const Account &account,
            const FileSystem &fileSystem,
            const Shell &shell,
            const Settings &settings,
            const Log &log) :
            CommandAction(buildStorage, substitution, shell, true),
            _fetchAction(fetchAction),
            _account(account),
            _fileSystem(fileSystem),
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

        _log.Out() << "Building " << package.Name << " " << package.Version << std::endl;

        std::string rootPath{GetRootPath(package)};
        std::string buildPath{GetPath(package)};
        _fileSystem.Remove(rootPath);
        _fileSystem.CreateDirectory(buildPath);
        _fileSystem.CreateLink(rootPath, _fetchAction->GetPath(package), "src");
        _fileSystem.SetOwner(buildPath, _account);
        RunCommands(package.Config, buildPath, GetLogPath(package, "config"), _account);
        RunCommands(package.Build, buildPath, GetLogPath(package, "build"), _account);
        _fileSystem.SetOwner(buildPath, {0, 0});
        PushToStorage(package);
    }

    std::string BuildAction::GetPath(const PackageMetadata &package) const {
        return _fileSystem.CreatePath(GetRootPath(package), "build");
    }

    std::string BuildAction::GetLogPath(const PackageMetadata &package, const std::string &logName) const {
        return _fileSystem.CreatePath(GetRootPath(package), logName + ".log");
    }

    std::string BuildAction::GetRootPath(const PackageMetadata &package) const {
        return _fileSystem.CreatePath(_buildPath, package.Name);
    }
}
