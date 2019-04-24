#ifndef PKG_ACTIONS_INSTALL_ACTION_H
#define PKG_ACTIONS_INSTALL_ACTION_H

#include "pkg/actions/Action.h"

#include "pkg/actions/BuildAction.h"
#include "pkg/storage/PackageStorage.h"

using pkg::storage::PackageStorage;

namespace pkg::actions {
    class InstallAction : public Action {

    private:
        const std::shared_ptr<BuildAction> _buildAction;
        const Shell _shell;

    public:
        InstallAction(
                std::shared_ptr<PackageStorage> packageStorage,
                std::shared_ptr<BuildAction> buildAction,
                const Shell &shell);

        void Perform(const PackageMetadata &package) const override;
    };
}

#endif
