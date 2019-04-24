#ifndef PKG_ACTIONS_UPDATE_ACTION_H
#define PKG_ACTIONS_UPDATE_ACTION_H

#include "pkg/actions/Action.h"

#include "pkg/actions/BuildAction.h"
#include "pkg/actions/InstallAction.h"
#include "pkg/storage/PackageStorage.h"

using pkg::storage::PackageStorage;

namespace pkg::actions {
    class UpdateAction : public Action {

    private:
        const std::shared_ptr<BuildAction> _buildAction;
        const std::shared_ptr<InstallAction> _installAction;

    public:
        UpdateAction(
                std::shared_ptr<PackageStorage> packageStorage,
                std::shared_ptr<BuildAction> buildAction,
                std::shared_ptr<InstallAction> installAction);

        void Perform(const PackageMetadata &package) const override;
    };
}

#endif
