#include "StatusAction.h"

#include <iomanip>

namespace pkg::actions {

    StatusAction::StatusAction(
            std::shared_ptr<FetchAction> fetchAction,
            std::shared_ptr<BuildAction> buildAction,
            std::shared_ptr<InstallAction> installAction,
            std::shared_ptr<UpdateAction> updateAction,
            const Log &log) :
            _fetchAction(std::move(fetchAction)),
            _buildAction(std::move(buildAction)),
            _installAction(std::move(installAction)),
            _updateAction(std::move(updateAction)),
            _log(log) {
    }

    bool StatusAction::ShouldBePerformed(const Package &) const {
        return true;
    }

    void StatusAction::Perform(const PackageMetadata &package) const {
        if (!ShouldBePerformed(package)) {
            return;
        }
        _log.Out() << std::left << std::setfill('.') <<
                   std::setw(15) << package.Name + " " <<
                   std::setw(7) << (_fetchAction->ShouldBePerformed(package) ? " fetch " : "") <<
                   std::setw(7) << (_buildAction->ShouldBePerformed(package) ? " build " : "") <<
                   std::setw(9) << (_installAction->ShouldBePerformed(package)
                                    ? " install "
                                    : _updateAction->ShouldBePerformed(package) ? " update  " : "") <<
                   " " << package.Version << std::endl;
    }
}
