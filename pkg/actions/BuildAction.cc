#include "BuildAction.h"

namespace pkg::actions {

    BuildAction::BuildAction(
            const std::shared_ptr<BuildStorage> &buildStorage,
            const std::shared_ptr<FetchAction> &fetchAction,
            const Substitution &substitution,
            const FileSystem &fileSystem,
            const Shell &shell,
            const Settings &settings,
            const Log &log) :
            CommandAction(buildStorage, substitution, shell, true),
            _fetchAction(fetchAction),
            _buildPath(settings.BuildPath),
            _fileSystem(fileSystem),
            _settings(settings),
            _log(log) {
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
        _fileSystem.SetOwner(buildPath, _settings.GetImpersonationAccount());
        RunCommands(package.Config, buildPath, GetLogPath(package, "config"), _settings.GetImpersonationAccount());
        RunCommands(package.Build, buildPath, GetLogPath(package, "build"), _settings.GetImpersonationAccount());
        _fileSystem.SetOwner(buildPath, _settings.GetCurrentAccount());
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
