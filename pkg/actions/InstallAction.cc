#include "InstallAction.h"

namespace pkg::actions {

    InstallAction::InstallAction(
            std::shared_ptr<PackageStorage> packageStorage,
            std::shared_ptr<BuildAction> buildAction,
            const Shell &shell) :
            Action(std::move(packageStorage), false),
            _buildAction(std::move(buildAction)),
            _shell(shell) {
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
