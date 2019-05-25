#include "InstallAction.h"

namespace pkg::actions {

    InstallAction::InstallAction(
            const std::shared_ptr<PackageStorage> &packageStorage,
            const std::shared_ptr<BuildAction> &buildAction,
            const Substitution &substitution,
            const FileSystem &fileSystem,
            const Shell &shell,
            const Settings &settings) :
            CommandAction(packageStorage, substitution, shell, false),
            _buildAction(buildAction),
            _fileSystem(fileSystem),
            _settings(settings) {
    }

    std::string InstallAction::GetName() const {
        return "install";
    }

    void InstallAction::Perform(const PackageMetadata &package) const {
        if (!ShouldBePerformed(package)) {
            return;
        }
        _buildAction->Perform(package);

        std::string buildPath{_buildAction->GetPath(package)};
        std::string logPath{_buildAction->GetLogPath(package, "install")};
        RunCommands(package.Install, buildPath, logPath);
        PushToStorage(package);
        ResetLdCache();
    }

    void InstallAction::ResetLdCache() const {
        _fileSystem.Remove(std::string(_settings.LdCachePath));
        RunCommand(std::string(_settings.LdCommand));
    }
}
