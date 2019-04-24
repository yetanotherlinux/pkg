#include "UpdateAction.h"

namespace pkg::actions {

    UpdateAction::UpdateAction(
            std::shared_ptr<PackageStorage> packageStorage,
            std::shared_ptr<BuildAction> buildAction,
            std::shared_ptr<InstallAction> installAction) :
            Action(std::move(packageStorage), true),
            _buildAction(std::move(buildAction)),
            _installAction(std::move(installAction)) {
    }

    void UpdateAction::Perform(const PackageMetadata &package) const {
        if (!ShouldBePerformed(package)) {
            return;
        }
        _buildAction->Perform(package);
        PopFromStorage(package);
        _installAction->Perform(package);
    }
}
