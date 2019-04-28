#include "StatusAction.h"

#include <iomanip>

namespace pkg::actions {

    StatusAction::StatusAction(
            const std::shared_ptr<FetchAction> &fetchAction,
            const std::shared_ptr<BuildAction> &buildAction,
            const std::shared_ptr<InstallAction> &installAction,
            const std::shared_ptr<UpdateAction> &updateAction,
            const Log &log) :
            _fetchAction(fetchAction),
            _buildAction(buildAction),
            _installAction(installAction),
            _updateAction(updateAction),
            _fetchActionName(" " + fetchAction->GetName() + " "),
            _buildActionName(" " + buildAction->GetName() + " "),
            _installActionName(" " + installAction->GetName() + " "),
            _updateActionName(" " + updateAction->GetName() + "  "),
            _log(log) {
    }

    std::string StatusAction::GetName() const {
        return "status";
    }

    bool StatusAction::ShouldBePerformed(const Package &package) const {
        return _installAction->ShouldBePerformed(package) || _updateAction->ShouldBePerformed(package);
    }

    void StatusAction::Perform(const PackageMetadata &package, bool isForced) const {
        if (!isForced && !ShouldBePerformed(package)) {
            return;
        }
        _log.Out() << std::left << std::setfill('.') <<
                   std::setw(15) << package.Name + " " <<

                   std::setw(_fetchActionName.size()) << (
                           _fetchAction->ShouldBePerformed(package) ? _fetchActionName : "") <<

                   std::setw(_buildActionName.size()) << (
                           _buildAction->ShouldBePerformed(package) ? _buildActionName : "") <<

                   std::setw(_installActionName.size()) << (
                           _installAction->ShouldBePerformed(package)
                           ? _installActionName
                           : _updateAction->ShouldBePerformed(package) ? _updateActionName : "") <<

                   " " << package.Version << std::endl;
    }
}
