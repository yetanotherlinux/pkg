#include "InstallAction.h"

namespace pkg::actions {

    InstallAction::InstallAction(
            const std::shared_ptr<PackageStorage> &packageStorage,
            const std::shared_ptr<BuildAction> &buildAction,
            const Shell &shell) :
            Action(packageStorage, false),
            _buildAction(buildAction),
            _shell(shell) {
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
    }
}
