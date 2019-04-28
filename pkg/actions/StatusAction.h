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
        const std::string _fetchActionName;
        const std::string _buildActionName;
        const std::string _installActionName;
        const std::string _updateActionName;
        const Log _log;

    public:
        StatusAction(
                const std::shared_ptr<FetchAction> &fetchAction,
                const std::shared_ptr<BuildAction> &buildAction,
                const std::shared_ptr<InstallAction> &installAction,
                const std::shared_ptr<UpdateAction> &updateAction,
                const Log &log);

        std::string GetName() const override;

        bool ShouldBePerformed(const Package &package) const override;

        void Perform(const PackageMetadata &package, bool isForced) const override;
    };
}

#endif
