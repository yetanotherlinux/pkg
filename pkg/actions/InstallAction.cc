#include "InstallAction.h"

namespace pkg::actions {

    InstallAction::InstallAction(
            const std::shared_ptr<PackageStorage> &packageStorage,
            const std::shared_ptr<BuildAction> &buildAction,
            const Substitution &substitution,
            const FileSystem &fileSystem,
            const Settings &settings,
            const Log &log) :
            CommandAction(packageStorage, substitution, false),
            _buildAction(buildAction),
            _fileSystem(fileSystem),
            _settings(settings),
            _log(log) {
    }

    std::string InstallAction::GetName() const {
        return "install";
    }

    void InstallAction::Perform(const PackageMetadata &package) const {
        if (!ShouldBePerformed(package)) {
            return;
        }
        _buildAction->Perform(package);

        _log.Out() << "Installing " << package.Name << " " << package.Version << std::endl;

        std::string buildPath{_buildAction->GetPath(package)};
        std::string logPath{_buildAction->GetLogPath(package, "install")};
        Shell shell{buildPath};
        RunCommands(shell, package.Install, logPath);
        PushToStorage(package);
        ResetLdCache();
    }

    void InstallAction::ResetLdCache() const {
        _fileSystem.Remove(_settings.GetLdCachePath());
        RunCommand(Shell(), _settings.GetLdCommand());
    }
}
