#include "UpdateAction.h"

namespace pkg::actions {

    UpdateAction::UpdateAction(
            const std::shared_ptr<PackageStorage> &packageStorage,
            const std::shared_ptr<BuildAction> &buildAction,
            const std::shared_ptr<InstallAction> &installAction) :
            Action(packageStorage, true),
            _buildAction(buildAction),
            _installAction(installAction) {
    }

    std::string UpdateAction::GetName() const {
        return "update";
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
