#ifndef PKG_ACTIONS_STATUS_ACTION_H
#define PKG_ACTIONS_STATUS_ACTION_H

#include "pkg/actions/IAction.h"

#include "pkg/Log.h"
#include "pkg/actions/BuildAction.h"
#include "pkg/actions/FetchAction.h"
#include "pkg/actions/InstallAction.h"
#include "pkg/actions/UpdateAction.h"
#include "pkg/storage/PackageStorage.h"

using pkg::storage::PackageStorage;

namespace pkg::actions {
    class StatusAction : public IAction {

    private:
        const std::shared_ptr<FetchAction> _fetchAction;
        const std::shared_ptr<BuildAction> _buildAction;
        const std::shared_ptr<InstallAction> _installAction;
        const std::shared_ptr<UpdateAction> _updateAction;
        const Log _log;

    public:
        StatusAction(
                std::shared_ptr<FetchAction> fetchAction,
                std::shared_ptr<BuildAction> buildAction,
                std::shared_ptr<InstallAction> installAction,
                std::shared_ptr<UpdateAction> updateAction,
                const Log &log);

        bool ShouldBePerformed(const Package &package) const override;

        void Perform(const PackageMetadata &package) const override;
    };
}

#endif
