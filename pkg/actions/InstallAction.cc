#include "InstallAction.h"

namespace pkg::actions {

    InstallAction::InstallAction(
            const std::shared_ptr<PackageStorage> &packageStorage,
            const std::shared_ptr<BuildAction> &buildAction,
            const FileSystem &fileSystem,
            const Shell &shell,
            const Settings &settings) :
            Action(packageStorage, false),
            _buildAction(buildAction),
            _fileSystem(fileSystem),
            _shell(shell),
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
        RunCommands(_shell, package.Install, buildPath);
        PushToStorage(package);
        ResetLdCache();
    }

    void InstallAction::ResetLdCache() const {
        _fileSystem.Remove(std::string(_settings.LdCachePath));
        _shell.Run(std::string(_settings.LdCommand));
    }
}
