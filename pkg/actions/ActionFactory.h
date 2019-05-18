#ifndef PKG_ACTIONS_ACTION_FACTORY_H
#define PKG_ACTIONS_ACTION_FACTORY_H

#include <memory>
#include <vector>
#include "pkg/Log.h"
#include "pkg/actions/StatusAction.h"
#include "pkg/infrastructure/Shell.h"
#include "pkg/infrastructure/WebClient.h"
#include "pkg/storage/BuildStorage.h"
#include "pkg/storage/PackageStorage.h"
#include "pkg/storage/SourceStorage.h"

using pkg::actions::IAction;
using pkg::infrastructure::Shell;
using pkg::infrastructure::WebClient;
using pkg::storage::BuildStorage;
using pkg::storage::PackageStorage;
using pkg::storage::SourceStorage;

namespace pkg::actions {
    class ActionFactory {

    private:
        const std::shared_ptr<FetchAction> _fetchAction;
        const std::shared_ptr<BuildAction> _buildAction;
        const std::shared_ptr<InstallAction> _installAction;
        const std::shared_ptr<UpdateAction> _updateAction;
        const std::shared_ptr<StatusAction> _statusAction;

    public:
        ActionFactory(
                const std::shared_ptr<SourceStorage> &sourceStorage,
                const std::shared_ptr<BuildStorage> &buildStorage,
                const std::shared_ptr<PackageStorage> &packageStorage,
                const Account &impersonationAccount,
                const FileSystem &fileSystem,
                const WebClient &webClient,
                const Shell &shell,
                const Settings &settings,
                const Log &log);

        std::vector<std::string> GetActions() const;

        std::shared_ptr<IAction> CreateAction(const std::string &name) const;
    };
}

#endif
